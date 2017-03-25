#!/bin/zsh
DIRS=lib Unit1 Unit3 Unit4  Unit6 Unit7 Unit8 Unit9 Unit10 Unit11 \
 Unit13 Unit14 Unit15 Unit12 

all:
	for i in $(DIRS); do \
		(cd $$i && echo "making $$i" && $(MAKE) ) || exit 1; \
	done

clean:
	for i in $(DIRS); do \
		(cd $$i && echo "cleaning $$i" && $(MAKE) clean) || exit 1; \
	done
