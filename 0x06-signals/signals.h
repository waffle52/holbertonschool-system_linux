#ifndef _SIGNALS_H_
#define _SIGNALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int handle_signal(void);
void handle(int signum);
void (*current_handler_signal(void))(int);
void print_hello(int signum);
void set_print_hello(void);
int handle_sigaction(void);
void empty_handle(int signum);
void (*current_handler_sigaction(void))(int);
int trace_signal_sender(void);
int pid_exist(pid_t pid);
void all_in_one(void);
int sigset_init(sigset_t *set, int *signals);
int signals_block(int *signals);
int signals_unblock(int *signals);
int handle_pending(void (*handler)(int));

#endif
