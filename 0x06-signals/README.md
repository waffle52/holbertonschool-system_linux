# 0x06-signals
# 0-handle_signal.c
Write a function that set a handler for the signal SIGINT

    Prototype: int handle_signal(void);
    Your function must return 0 on success, or -1 on error
    The program should print Gotcha! [<signum>] followed by a new line, every time Control-C is pressed (See example below)
        where <signum> must be replaced with the signal number that was caught
    sigaction(2) is not allowed

# 1-current_handler_signal.c
Write a function that retrieves the current handler of the signal SIGINT

    Prototype: void (*current_handler_signal(void))(int);
    Your function returns a pointer to the current handler of SIGINT, or NULL on failure
    You are not allowed to use sigaction(2)
    The handler must be unchanged after calling your function

# 2-handle_sigaction.c
Write a function that set a handler for the signal SIGINT

    Prototype: int handle_sigaction(void);
    Your function must return 0 on success, or -1 on error
    The program should print Gotcha! [<signum>] followed by a new line, every time Control-C is pressed (See example below)
        where <signum> must be replaced with the signal number that was caught
    signal(2) is not allowed

# 3-current_handler_sigaction.c
Write a function that retrieves the current handler of the signal SIGINT

    Prototype: void (*current_handler_sigaction(void))(int);
    Your function returns a pointer to the current handler of SIGINT, or NULL on failure
    You have to use the function sigaction (signal is not allowed)
    The handler must be unchanged after calling your function

# 4-trace_signal_sender.c
Write a function that defines a handler for the signal SIGQUIT (Control-\ in a shell)

    Prototype: int trace_signal_sender(void);
    The handler must print SIGQUIT sent by <pid> each time a SIGQUIT (and only a SIGQUIT) is caught
        Where <pid> must be replaced by the PID of the process that sent the signal
    Your function must return 0 on success, or -1 on error

# 5-signal_describe.c
Write a program that prints a description of a given signal

    Usage: ./describe <signum>
        Where <signum> is the signal number to be described
        If the number of arguments is not correct, your program must print Usage: %s <signum> (where %s is argv[0]), followed by a new line, and exit with EXIT_FAILURE
    You’re not allowed to have more than 1 function in your file
    You’re not allowed to have more than 12 lines in your function
    You can assume that if a parameter is given, it will be a number

# 6-suspend.c
Write a program that sets a handler for the signal SIGINT, and exits right after the signal is received and handled

    Your program does not take any argument
    Your program should suspend indefinitely until a signal is received
    When a SIGINT is received, you must print Caught %d (where %d must be replaced by the signal number), followed by a new line
    After the first SIGINT is received, your program must:
        Print Signal received, followed by a new line
        Exit with EXIT_SUCCESS
    You are not allowed to use the functions exit, sleep or _exit
    You are not allowed to use any kind of loop (while, for, do/while)

# 7-signal_send.c
Write a program that sends the signal SIGINT to a process, given its PID

    Usage: signal_send <pid>
        Where <pid> is the PID of the process to send a signal to
        If the number of arguments is not correct, your program must print Usage: %s <pid> (where %s is argv[0]), followed by a new line, and exit with EXIT_FAILURE
        <pid> won’t be 0
    Your program must return EXIT_SUCCESS on success, or EXIT_FAILURE
    You’re not allowed to have more than 1 function in your file

# 8-signal_send.sh
Write a sh script that sends the signal SIGQUIT to a process, given its PID

    Usage: signal_send.sh <pid>
        Where <pid> is the PID of the process to send a signal to
        If the number of arguments is not correct, your program must print Usage: %s <pid> (where %s is argv[0]), followed by a new line, and exit with 1

# 9-handle_signal.sh
Write a sh script that set a handler for the signals SIGABRT, SIGIO and SIGTERM

    The script must print Nope followed by a new line, each time a SIGABRT, SIGIO or SIGTERM is caught
    Your script must contain a shebang
    You’re not allowed to have more than 2 lines in your script
    You’re not allowed to have more than 1 instruction per line

# 10-pid_exist.c
Write a function that tests if a process exists, given its PID

    Prototype: int pid_exist(pid_t pid);
    Your function must return 1 if the process with the PID pid exists, or 0 otherwise
    You’re not allowed to have more than 1 function in your file
    You’re not allowed to have more than 1 line in your function
    You’re not allowed to include more than 2 headers in your file
    You’re not allowed to include your header file signals.h
    You’re not allowed to use the function getpgid
