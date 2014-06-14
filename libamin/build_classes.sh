set -e

PREFIX="/usr/local"
INC_EO=$PREFIX"/share/eolian/include/eo-1"

######  C  #################################################################
# clean out old generated files
rm -f src/*.eo.h src/*.eo.c

# generate template binding code from the .eo file
eolian_gen -I $INC_EO -I classes/ --gc --eo -o src/xml_sax_base.eo.c classes/xml_sax_base.eo
eolian_gen -I $INC_EO -I classes/ --gh --eo -o include/xml_sax_base.eo.h classes/xml_sax_base.eo
eolian_gen -I $INC_EO -I classes/ --gi --eo -o src/xml_sax_base.c classes/xml_sax_base.eo

eolian_gen -I $INC_EO -I classes/ --gc --eo -o src/amin_elt.eo.c classes/amin_elt.eo
eolian_gen -I $INC_EO -I classes/ --gh --eo -o include/amin_elt.eo.h classes/amin_elt.eo
eolian_gen -I $INC_EO -I classes/ --gi --eo -o src/amin_elt.c classes/amin_elt.eo

# now actually compile the core c class code into an object file
gcc -I include/ -c src/xml_sax_base.c -o src/xml_sax_base.o `pkg-config --cflags eo eina ecore libxml-2.0`
# now actually compile the test app with its tst class implementation
#gcc tst.o main.c -o tst `pkg-config --cflags --libs eo eina libxml-2.0`





exit 0