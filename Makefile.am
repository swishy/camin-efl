AUTOMAKE_OPTIONS = 1.4 foreign
ACLOCAL_AMFLAGS = -I m4
MAINTAINERCLEANFILES = Makefile.in aclocal.m4 config.h.in configure depcomp install-sh missing ltmain.sh config.guess config.sub
.SILENT: *.o

INCLUDES = -I$(top_srcdir)/include

lib_LTLIBRARIES = libamin.la
libamin_la_SOURCES = lib/machine.c lib/amin_command_interface.c lib/commands/amin_mkdir_command.c
libamin_la_LIBADD = @EINA_LIBS@ @ECORE_LIBS@ @EO_LIBS@
libamin_la_CFLAGS = -lexpat @EINA_CFLAGS@ @ECORE_CFLAGS@ @EO_CFLAGS@
libamin_la_LDFLAGS = -version-info @version_info@ 

bin_PROGRAMS = camin cainit

cainit_SOURCES = bin/ainit.c
cainit_LDADD = /usr/lib/libuv.a	
cainit_CFLAGS = -luv -lpthread

camin_SOURCES = bin/amin.c
camin_LDADD = @EINA_LIBS@ @ECORE_LIBS@ @EO_LIBS@ libamin.la	
camin_CFLAGS = @EINA_CFLAGS@ @ECORE_CFLAGS@ @EO_CFLAGS@