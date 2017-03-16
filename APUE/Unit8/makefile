#!/bin/zsh
ROOT=..
PLATFORM=$(shell $(ROOT)/SystemType.sh)
include $(ROOT)/Make.defines.myMacOS

PROGS= echoall exec exit fork tiwce_fork vfork competition system tsys printuids acct nice time
all: $(PROGS)
%: %.c $(LIBMYAPUE)
	$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

include $(ROOT)/Make.defines.myMacOS
