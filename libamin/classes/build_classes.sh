set -e

PREFIX="/usr/local"
INC_EO=$PREFIX"/share/eolian/include/eo-1"

######  C  #################################################################
# clean out old generated files
rm -f *.eo.h *.eo.c

# generate template binding code from the .eo file
eolian_gen -I $INC_EO --gc --eo -o xml_sax_base.eo.c xml_sax_base.eo
eolian_gen -I $INC_EO --gh --eo -o xml_sax_base.eo.h xml_sax_base.eo
eolian_gen -I $INC_EO --gi --eo -o xml_sax_base.c xml_sax_base.eo

# now actually compile the core c class code into an object file
gcc -c xml_sax_base.c -o xml_sax_base.o `pkg-config --cflags eo eina ecore libxml-2.0`
# now actually compile the test app with its tst class implementation
#gcc tst.o main.c -o tst `pkg-config --cflags --libs eo eina libxml-2.0`





exit 0