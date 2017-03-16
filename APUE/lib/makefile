#!/bin/zsh

ROOT=..
PLATFORM=$(shell $(ROOT)/SystemType.sh)
include $(ROOT)/Make.defines.myMacOS

LIBMISC = libapue.a
OBJS = error.o unit2.o unit3.o unit8.o unit10.o

###############
all:	$(LIBMISC)
#sleep.o
###############
$(LIBMISC):	$(OBJS)
	$(AR) rv $(LIBMISC) $?
	$(RANLIB) $(LIBMISC)


clean:
	rm -f *.o a.out core temp.* $(LIBMISC)

include $(ROOT)/Make.libapue.inc
