#!/bin/zsh

ROOT=..
PLATFORM=$(shell $(ROOT)/SystemType.sh)
include $(ROOT)/Make.defines.myMacOS

LIBMISC = libapue.a
OBJS = error.o errlog.o unit2.o unit3.o unit8.o unit10.o unit11.o unit13.o unit14.o unit15.o

all:	$(LIBMISC)

$(LIBMISC):	$(OBJS)
	$(AR) rv $(LIBMISC) $?
	$(RANLIB) $(LIBMISC)

clean:
	rm -f *.o a.out core temp.* $(LIBMISC)

include $(ROOT)/Make.libapue.inc
