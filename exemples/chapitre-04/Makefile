

CFLAGS=-Wall -g

CROSS_COMPILE?=

CC=$(CROSS_COMPILE)gcc

.PHONY: all
all: verification-preemption

verification-preemption: verification-preemption.c
	${CC} ${CFLAGS} verification-preemption.c -o verification-preemption

clean: 
	rm -f verification-preemption


