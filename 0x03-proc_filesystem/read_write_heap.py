#!/usr/bin/env python3
"""
Locates and replaces the first occurrence of a string in the heap
of a process

Usage: ./read_write_heap.py PID search_string replace_by_string
Where:
- PID is the pid of the target process
- search_string is the ASCII string you are looking to overwrite
- replace_by_string is the ASCII string you want to replace
  search_string with
"""

import sys


def print_usage():
    print("Usage: {} pid search write".format(sys.argv[0]))
    sys.exit(1)


# check usage
if len(sys.argv) != 4:
    print_usage()

# get the pid from argv
pid = int(sys.argv[1])
if pid <= 0:
    print_usage()
search_string = str(sys.argv[2])
if search_string == "":
    print_usage()
write_string = str(sys.argv[3])
if write_string == "":
    print_usage()

# open the maps and mem files of the process
maps_file = "/proc/{}/maps".format(pid)
print("[*] maps: {}".format(maps_file))
mem_file = "/proc/{}/mem".format(pid)
print("[*] mem: {}".format(mem_file))

# try opening the maps file
try:
    maps = open('/proc/{}/maps'.format(pid), 'r')
except IOError as e:
    print("[ERROR] Can not open file {}:".format(maps_filename))
    print("\tI/O error({}): {}".format(e.errno, e.strerror))
    sys.exit(1)

for line in maps:
    word = line.split(' ')
    # check if we found the heap
    if word[-1][:-1] != "[heap]":
        continue
    print("[*] Found [heap]:")

    # parse the line
    addr = word[0]
    perm = word[1]
    offset = word[2]
    device = word[3]
    inode = word[4]
    pathname = word[-1][:-1]
    print("\tpathname = {}".format(pathname))
    print("\taddresses = {}".format(addr))
    print("\tpermisions = {}".format(perm))
    print("\toffset = {}".format(offset))
    print("\tinode = {}".format(inode))

    # check if there is read and write permission
    if perm[0] != 'r' or perm[1] != 'w':
        print("[*] {} does not have read/write permission".format(pathname))
        maps.close()
        sys.exit(0)

    # get start and end of the heap in the virtal memory
    addr = addr.split("-")
    if len(addr) != 2:
        print("[*] Wrong addr format")
        maps.close()
        sys.exit(1)
    addr_start = int(addr[0], 16)
    addr_end = int(addr[1], 16)
    print("\tAddr start [{:x}] | end [{:x}]".format(addr_start, addr_end))

    # open and read mem
    try:
        mem_file = open(mem_file, 'rb+')
    except IOError as e:
        print("[ERROR] Can not open file {}:".format(mem_file))
        print("\tI/O error({}): {}".format(e.errno, e.strerror))
        maps.close()
        sys.exit(1)
    # read heap
    mem_file.seek(addr_start)
    heap = mem_file.read(addr_end - addr_start)

    # find string
    try:
        i = heap.index(bytes(search_string, "ASCII"))
    except Exception:
        print("Can't find '{}'".format(search_string))
        maps.close()
        mem_file.close()
        exit(0)
    print("[*] Found '{}' at {:x}".format(search_string, i))

    # write the new string in memory
    print("[*] Writing '{}' at {:x}".format(write_string, addr_start + i))
    mem_file.seek(addr_start + i)
    mem_file.write(bytes(write_string, "ASCII"))

    # close files
    maps.close()
    mem_file.close()
