#!/bin/zsh
ROOT=..
PLATFORM=$(shell $(ROOT)/SystemType.sh)
include $(ROOT)/Make.defines.myMacOS

PROGS= catch my_alarm sigcld sleep read sigpending sigjmp sigsuspend sigsuspend_wait system_ed
all: $(PROGS)
%: %.c $(LIBMYAPUE)
	$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

include $(ROOT)/Make.defines.myMacOS
