# Generated automatically from Makefile.in by configure. 
# # Makefile for dip.	-*- Indented-Text -*-
# Copyright (C) 2009 Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# 19.12.09, Yang Zhang, NUIST, Nanjing, CHN.

#### Start of system configuration section. ####
DIR		= /home/jedi/DDD

CC		= gcc
LD		= ld
FL		= flawfinder

# For gcc
CDBG		= -g -rdynamic
CADD		= -funroll-loops -finline-functions -O3 -Winline
CFLAGS		= -I include/ -c -Wall -lm -pedantic $(CADD)

# For ld
LDFLAGS		= -dynamic-linker /lib/ld-linux.so.2 /usr/lib/crt1.o \
		  /usr/lib/crti.o -lc /usr/lib/crtn.o

# For flawfinder
FLFLAGS		= -DQ
FLOUT		= flaw.out

MAIN		= dip
OBJ		= main.o  lib/io.o  lib/sharpening.o  lib/smoothing.o \
		  lib/geometry.o  /lib/libc.so.6  /lib/libm.so.6

srcdir = .
VPATH = .

INCLUDE		= include/proto.h  include/const.h  include/type.h

INSTALL		= /usr/bin/install -c
INSTALL_PROGRAM = $(INSTALL)
INSTALL_DATA	= $(INSTALL) -m 644

DEFS		= 
LIBS		= 

prefix		= /usr/local
exec_prefix	= $(prefix)
bindir		= $(exec_prefix)/bin
datadir		= $(prefix)/lib
libdir		= $(prefix)/lib
infodir		= $(prefix)/info

# Where to install the manual pages.
mandir		= $(prefix)/man/man1
# Extension (not including `.') for the installed manual page filenames.
manext		= 1
#### End of system configuration section. ####


# to avoid trouble on systems where the SHELL variable might be inherited 
# from the environment. (This is never a problem with GNU make.)
SHELL		=	/bin/sh

.PHONY: all image bd clean fl

all:	$(MAIN)

LOADLIBES	= $(LIBS)

DISTFILES	= COPYING ChangeLog Makefile.in README configure configure.in main.c

DISTNAME	= dip-1.1

fl:
	$(FL) $(FLFLAGS) $(DIR) > $(FLOUT)
bd:
	gcc -g -rdynamic -I include/ -lm main.c lib/io.c lib/sharpening.c \
		lib/smoothing.c lib/geometry.c


$(MAIN):	  $(OBJ)
	# It must b $(OBJ), not $<, 
	# $< just presents only 1 obj-file, namely the 1st in var-OBJ, main.o
	$(LD) $(LDFLAGS) -o $@ $(OBJ)

main.o:		  main.c	   $(INCLUDE);	   
	# Just for inline-function
	$(CC) $(CFLAGS) -O3 -finline-functions -o $@ $<

lib/io.o:	  lib/io.c	   $(INCLUDE);	   
	$(CC) $(CFLAGS) -o $@ $<

lib/sharpening.o: lib/sharpening.c $(INCLUDE);	   
	$(CC) $(CFLAGS) -o $@ $<

lib/smoothing.o:  lib/smoothing.c  $(INCLUDE);	   
	$(CC) $(CFLAGS) -o $@ $<

lib/geometry.o:	  lib/geometry.c   $(INCLUDE);	   
	$(CC) $(CFLAGS) -o $@ $<


### targets required by GNU Coding standards ###

# Makefile: Makefile.in config.status
# 	./config.status

# config.status: configure
# 	$(srcdir)/configure --srcdir=$(srcdir) --no-create

configure: configure.in
	cd $(srcdir); autoconf

TAGS:
	cd $(srcdir); etags

clean:
	rm *.o lib/*.o dip

mostlyclean: clean

distclean: clean
	rm -f Makefile config.status

realclean: distclean
	rm -f TAGS

dist: $(DISTFILES)
	rm -rf $(DISTNAME)
	mkdir $(DISTNAME)
	ln $(DISTFILES) $(DISTNAME)
	tar --gzip -chf $(DISTNAME).tar.z $(DISTNAME)
	rm -rf $(DISTNAME)

install: all 
	$(INSTALL_PROGRAM) dip $(bindir)/dip

uninstall: force
	-cd $(bindir); rm -f dip

### Actual dip-specific targets ###

check: dip
	ls -1 * | ./dip

#dip.info: dip.texi
#	cd $(srcdir); makeinfo dip.texi

#dip.dvi: dip.texi
#	cd $(srcdir); texi2dvi dip.texi

# Prevent GNU make v3 from overflowing arg limit on SysV.
.NOEXPORT:
