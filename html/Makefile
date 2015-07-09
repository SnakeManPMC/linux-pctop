#
# Makefile --- pctop (c) PMC 1993 - 2015
#

CC	= gcc
LIBDIR  = 
MAINDIR = 

CFLAGS = -I$(MAINDIR) -I$(LIBDIR) 

LIBS	= 

all:		asc2html

clean:          rm asc2html

asc2html:	asc2html.c
	        $(CC) $(CFLAGS) -o $@ $<
