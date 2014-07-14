set -e

PREFIX="/usr"
INC_EO=$PREFIX"/share/eolian/include/eo-1"

######  C  #################################################################
# clean out old generated files
# rm -f src/*.eo.h src/*.eo.c

# generate template binding code from the .eo file
eolian_gen -I $INC_EO -I stage/ --gc --eo -o stage/amin.eo.c stage/amin.eo
eolian_gen -I $INC_EO -I stage/ --gh --eo -o stage/amin.eo.h stage/amin.eo
eolian_gen -I $INC_EO -I stage/ --gi --eo -o stage/amin.c stage/amin.eo

eolian_gen -I $INC_EO -I stage/ --gc --eo -o stage/xml_sax_base.eo.c stage/xml_sax_base.eo
eolian_gen -I $INC_EO -I stage/ --gh --eo -o stage/xml_sax_base.eo.h stage/xml_sax_base.eo
eolian_gen -I $INC_EO -I stage/ --gi --eo -o stage/xml_sax_base.c stage/xml_sax_base.eo

eolian_gen -I $INC_EO -I stage/ --gc --eo -o stage/amin_elt.eo.c stage/amin_elt.eo
eolian_gen -I $INC_EO -I stage/ --gh --eo -o stage/amin_elt.eo.h stage/amin_elt.eo
eolian_gen -I $INC_EO -I stage/ --gi --eo -o stage/amin_elt.c stage/amin_elt.eo

exit 0
