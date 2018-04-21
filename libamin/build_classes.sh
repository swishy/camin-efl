set -e

PREFIX="/usr/local"
INC_EO=$PREFIX"/share/eolian/include/eo-1"

######  C  #################################################################
# clean out old generated files
rm -f src/*.eo.h src/*.eo.c

# generate template binding code from the .eo file
eolian_gen -I $INC_EO -I src/eo/ --gc --eo -o src/amin.eo.c src/eo/amin.eo
eolian_gen -I $INC_EO -I src/eo/ --gh --eo -o src/amin.eo.h src/eo/amin.eo
eolian_gen -I $INC_EO -I src/eo/ --gi --eo -o src/amin.c src/eo/amin.eo

eolian_gen -I $INC_EO -I src/eo/-gc --eo -o src/xml_sax_base.eo.c src/eo/xml_sax_base.eo
eolian_gen -I $INC_EO -I src/eo/ --gh --eo -o src/xml_sax_base.eo.h src/eo/xml_sax_base.eo
eolian_gen -I $INC_EO -I src/eo/ --gi --eo -o src/xml_sax_base.c src/eo/xml_sax_base.eo

eolian_gen -I $INC_EO -I src/eo/ --gc --eo -o src/amin_elt.eo.c src/eo/amin_elt.eo
eolian_gen -I $INC_EO -I src/eo/ --gh --eo -o src/amin_elt.eo.h src/eo/amin_elt.eo
eolian_gen -I $INC_EO -I src/eo/ --gi --eo -o src/amin_elt.c src/eo/amin_elt.eo

eolian_gen -I $INC_EO -I src/eo/ --gc --eo -o src/amin_machine_spec.eo.c src/eo/amin_machine_spec.eo
eolian_gen -I $INC_EO -I src/eo/ --gh --eo -o src/amin_machine_spec.eo.h src/eo/amin_machine_spec.eo
eolian_gen -I $INC_EO -I src/eo/ --gi --eo -o src/amin_machine_spec.c src/eo/amin_machine_spec.eo

#eolian_gen -I $INC_EO -I src/eo/ --gc --eo -o src/amin_machine_spec_document.eo.c src/eo/amin_machine_spec_document.eo
#eolian_gen -I $INC_EO -I src/eo/ --gh --eo -o src/amin_machine_spec_document.eo.h src/eo/amin_machine_spec_document.eo
#eolian_gen -I $INC_EO -I src/eo/ --gi --eo -o src/amin_machine_spec_document.c src/eo/amin_machine_spec_document.eo

#eolian_gen -I $INC_EO -I src/eo/ --gc --eo -o src/amin_machine_spec_data.eo.c src/eo/amin_machine_spec_data.eo
#eolian_gen -I $INC_EO -I src/eo/ --gh --eo -o src/amin_machine_spec_data.eo.h src/eo/amin_machine_spec_data.eo
#eolian_gen -I $INC_EO -I src/eo/ --gi --eo -o src/amin_machine_spec_data.c src/eo/amin_machine_spec_data.eo

exit 0
