#!/usr/bin/env python3


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

