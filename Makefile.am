AUTOMAKE_OPTIONS = 1.4 foreign
MAINTAINERCLEANFILES = Makefile.in aclocal.m4 config.h.in configure depcomp install-sh missing ltmain.sh config.guess config.sub

INCLUDES = -I$(top_srcdir)/include

lib_LIBRARIES = libamin.a
libamin_a_SOURCES = lib/machine.c
libamin_a_CFLAGS = -lexpat

lib_LTLIBRARIES = libamin.la
libamin_la_SOURCES = lib/machine.c
libamin_la_CFLAGS = -lexpat

bin_PROGRAMS = camin cainit

cainit_SOURCES = bin/ainit.c
cainit_LDADD = /usr/lib/libuv.a	
cainit_CFLAGS = -luv -lpthread

camin_SOURCES = bin/amin.c
camin_LDADD = libamin.la	
camin_CFLAGS = -lpthread 