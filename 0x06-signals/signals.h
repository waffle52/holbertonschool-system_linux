#ifndef _SIGNALS_H_
#define _SIGNALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
int handle_signal(void);
void handle(int signum);
void (*current_handler_signal(void))(int);
int handle_sigaction(void);
void (*current_handler_sigaction(void))(int);
int trace_signal_sender(void);
int pid_exist(pid_t pid);

#endif
