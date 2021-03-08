CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89 -g

SRC = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRC))
LIBS = $(patsubst %.c, %.o, common.c)
0 = $(patsubst %.c, %.o, $(wildcard 0-* .c)) $(LIBS)
1 = $(patsubst %.c, %.o, $(wildcard 1-*.c)) $(LIBS)


SRC2 = 2-hreadelf.c 2-print_info2.c 2-print_info3.c 2-print_info4.c 2-print_info5.c 2-print_info.c 1-print_header2.c 1-print_header3.c 1-print_header.c
2 = $(SRC2:.c=.o)


100 = $(patsubst %.c, %.o, $(wildcard *.c)) $(LIBS)

.PHONY: 0-hreadelf 1-hreadelf 2-hreadelf 100-hreadelf clean

0-hreadelf: $(0)
	$(CC) $(CFLAGS) $(0) -o 0-hreadelf

1-hreadelf: $(1)
	$(CC) $(CFLAGS) $(1) -o 1-hreadelf

2-hreadelf: $(2)
	$(CC) $(CFLAGS) $(2) -o 2-hreadelf

100-hreadelf: $(100)
	$(CC) $(CFLAGS) $(100) -o 100-hreadelf

clean:
	rm -f *.o
	rm -f *~
	rm -f $(OBJS) *-hreadelf
