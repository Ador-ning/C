#!/bin/zsh
ROOT=..
PLATFORM=$(shell $(ROOT)/SystemType.sh)
include $(ROOT)/Make.defines.myMacOS

PROG= catch my_alarm sigcld sleep read
all: $(PROG)
%: %.c $(LIBMYAPUE)
	$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

include $(ROOT)/Make.defines.myMacOS
