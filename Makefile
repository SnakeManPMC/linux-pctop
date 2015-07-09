#
# Makefile --- pctop (c) PMC 1993 - 2015
#

CC	= gcc
LIBDIR  = /code/include
MAINDIR = /code/include

CFLAGS = -I$(MAINDIR) -I$(LIBDIR) 

LIBS	= 

all:		pctop log test

clean:          rm pctop log test

pctop:		pctop.c 
	        $(CC) $(CFLAGS) -o $@ $<

log:		log.c 
	        $(CC) $(CFLAGS) -o $@ $<

test:		test.c 
	        $(CC) $(CFLAGS) -o $@ $<
