set -e

######  C  #################################################################
# clean out old generated files
rm -f src/*.eo.h src/*.eo.c

# generate template binding code from the .eo file
eolian_gen -gchi amin.eo
eolian_gen -gchi amin_elt.eo
eolian_gen -gchi amin_machine_spec_data.eo
eolian_gen -gchi xml_sax_base.eo

exit 0
