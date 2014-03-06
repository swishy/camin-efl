AUTOMAKE_OPTIONS = 1.4 foreign
ACLOCAL_AMFLAGS = -I m4
MAINTAINERCLEANFILES = Makefile.in aclocal.m4 config.h.in configure depcomp install-sh missing ltmain.sh config.guess config.sub
.SILENT: *.o

INCLUDES = -I$(top_srcdir)/include

lib_LTLIBRARIES = libamin.la

libamin_la_SOURCES = \
src/lib/amin.c src/lib/xml_sax_base.c \
src/lib/elt.c src/lib/machine/machine_spec.c \
src/lib/machine/spec/document.c \
src/lib/machine/amin_machine_dispatcher.c \
src/lib/machine/filter/xinclude.c

libamin_la_LIBADD =  @LIBURIPARSER_LIBS@ @EINA_LIBS@ @ECORE_LIBS@ @EO_LIBS@ @LIBXML2_LIBS@
libamin_la_CFLAGS = @LIBURIPARSER_CFLAGS@ @EINA_CFLAGS@ @ECORE_CFLAGS@ @EO_CFLAGS@ @LIBXML2_CFLAGS@
libamin_la_LDFLAGS = -version-info @version_info@

bin_PROGRAMS = camin cainit

cainit_SOURCES = src/bin/cainit.c
cainit_LDADD = /usr/local/lib/libuv.a	@EINA_LIBS@ @ECORE_LIBS@ @EO_LIBS@ @LIBXML2_LIBS@
cainit_CFLAGS = -luv -lpthread @EINA_CFLAGS@ @ECORE_CFLAGS@ @EO_CFLAGS@ @LIBXML2_CFLAGS@

camin_SOURCES = src/bin/camin.c
camin_LDADD = @LIBURIPARSER_LIBS@ @EINA_LIBS@ @ECORE_LIBS@ @EO_LIBS@ @LIBXML2_LIBS@ libamin.la
camin_CFLAGS = @LIBURIPARSER_CFLAGS@ @EINA_CFLAGS@ @ECORE_CFLAGS@ @EO_CFLAGS@ @LIBXML2_CFLAGS@
