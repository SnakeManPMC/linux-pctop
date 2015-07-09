#
# Makefile --- pctop remote
#

CC	= gcc
LIBDIR  = /upload1/code/include
MAINDIR = /upload1/code/include

CFLAGS = -I$(MAINDIR) -I$(LIBDIR) 

LIBS	= 

all:		gftpdremote

clean:          rm gftpdremote

gftpdremote:	gftpdremote.c
	        $(CC) $(CFLAGS) -o $@ $<
