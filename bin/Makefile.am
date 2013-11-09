AUTOMAKE_OPTIONS = 1.4 foreign
MAINTAINERCLEANFILES = Makefile.in aclocal.m4 config.h.in configure depcomp install-sh missing

INCLUDES = -I$(top_srcdir)

bin_PROGRAMS = amin ainit

ainit_SOURCES = ainit.c
ainit_LDADD = /usr/lib/libuv.a	
ainit_CFLAGS = -luv -lpthread

amin_SOURCES = amin.c
amin_LDADD = /usr/lib/libuv.a	
amin_CFLAGS = -lpthread 