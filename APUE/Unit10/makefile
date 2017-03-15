#!/bin/zsh
ROOT=..
PLATFORM=$(shell $(ROOT)/SystemType.sh)
include $(ROOT)/Make.defines.myMacOS

PROG= catch.out my_alarm.out sigcld.out sleep.out read.out sigpending.out sigjmp.out sigsuspend.out sigsuspend_wait.out system_ed.out
all: $(PROG)
%: %.c $(LIBMYAPUE)
	$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

include $(ROOT)/Make.defines.myMacOS
