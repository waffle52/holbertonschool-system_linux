# 0x03-proc_filesystem
Write a script that finds a string in the heap of a running process, and replaces it.

    Usage: read_write_heap.py pid search_string replace_string
        where pid is the pid of the running process
        and strings are ASCII
    The script should look only in the heap of the process
    Output: you can print whatever you think is interesting
    On usage error, print an error message on stdout and exit with status code 1
Write a blog post about the /proc filesystem and the /proc/maps and /proc/mem files.

Try to explain how to parse the /proc/maps file in order to read the virtual memory.

Your posts should have examples and at least one picture, at the top. Publish your blog post on Medium or LinkedIn, and share it at least on Twitter and LinkedIn.