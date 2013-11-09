AUTOMAKE_OPTIONS = 1.4 foreign
MAINTAINERCLEANFILES = Makefile.in aclocal.m4 config.h.in configure depcomp install-sh missing

INCLUDES = -I$(top_srcdir)/include

lib_LIBRARIES = libamin.a
libamin_a_SOURCES = lib/machine.c
libamin_CFLAGS = -lexpat

bin_PROGRAMS = amin ainit

ainit_SOURCES = bin/ainit.c
ainit_LDADD = /usr/lib/libuv.a	
ainit_CFLAGS = -luv -lpthread

amin_SOURCES = bin/amin.c
amin_LDADD = /usr/lib/libuv.a	
amin_CFLAGS = -lpthread 