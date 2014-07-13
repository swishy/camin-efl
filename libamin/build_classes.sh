set -e

PREFIX="/usr/local"
INC_EO=$PREFIX"/share/eolian/include/eo-1"

######  C  #################################################################
# clean out old generated files
rm -f src/*.eo.h src/*.eo.c

# generate template binding code from the .eo file
eolian_gen -I $INC_EO -I classes/ --gc --eo -o src/amin.eo.c classes/amin.eo
eolian_gen -I $INC_EO -I classes/ --gh --eo -o include/amin.eo.h classes/amin.eo
eolian_gen -I $INC_EO -I classes/ --gi --eo -o src/amin.c classes/amin.eo

eolian_gen -I $INC_EO -I classes/ --gc --eo -o src/xml_sax_base.eo.c classes/xml_sax_base.eo
eolian_gen -I $INC_EO -I classes/ --gh --eo -o include/xml_sax_base.eo.h classes/xml_sax_base.eo
eolian_gen -I $INC_EO -I classes/ --gi --eo -o src/xml_sax_base.c classes/xml_sax_base.eo

eolian_gen -I $INC_EO -I classes/ --gc --eo -o src/amin_elt.eo.c classes/amin_elt.eo
eolian_gen -I $INC_EO -I classes/ --gh --eo -o include/amin_elt.eo.h classes/amin_elt.eo
eolian_gen -I $INC_EO -I classes/ --gi --eo -o src/amin_elt.c classes/amin_elt.eo

exit 0
