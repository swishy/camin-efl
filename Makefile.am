AUTOMAKE_OPTIONS = 1.4 foreign
ACLOCAL_AMFLAGS = -I m4
MAINTAINERCLEANFILES = Makefile.in aclocal.m4 config.h.in configure depcomp install-sh missing ltmain.sh config.guess config.sub
.SILENT: *.o

INCLUDES = -I$(top_srcdir)/include

lib_LTLIBRARIES = libamin.la
libamin_la_SOURCES = lib/amin.c lib/xml_sax_base.c lib/elt.c lib/machine/machine_spec.c lib/machine/spec/document.c lib/machine/amin_machine_dispatcher.c lib/machine/filter/amin_machine_filter_dispatcher.c 
libamin_la_LIBADD = @EINA_LIBS@ @ECORE_LIBS@ @EO_LIBS@ @LIBXML2_LIBS@
libamin_la_CFLAGS = -lexpat @EINA_CFLAGS@ @ECORE_CFLAGS@ @EO_CFLAGS@ @LIBXML2_CFLAGS@
libamin_la_LDFLAGS = -version-info @version_info@ 

bin_PROGRAMS = camin cainit

cainit_SOURCES = bin/cainit.c
cainit_LDADD = /usr/lib/libuv.a	@EINA_LIBS@ @ECORE_LIBS@ @EO_LIBS@ @LIBXML2_LIBS@
cainit_CFLAGS = -luv -lpthread @EINA_CFLAGS@ @ECORE_CFLAGS@ @EO_CFLAGS@ @LIBXML2_CFLAGS@

camin_SOURCES = bin/camin.c
camin_LDADD = @EINA_LIBS@ @ECORE_LIBS@ @EO_LIBS@ @LIBXML2_LIBS@ libamin.la	
camin_CFLAGS = @EINA_CFLAGS@ @ECORE_CFLAGS@ @EO_CFLAGS@ @LIBXML2_CFLAGS@