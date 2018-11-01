#!/usr/bin/env bash
set -e

######  C  #################################################################
# clean out old generated files
rm -f src/*.eo.h src/*.eo.c

# generate template binding code from the .eo file
eolian_gen -gchi -I . xml_sax_base.eo
eolian_gen -gchi -I . amin.eo
eolian_gen -gchi -I . amin_elt.eo
eolian_gen -gchi -I . amin_machine_spec.eo
eolian_gen -gchi -I . amin_machine_spec_data.eo


exit 0