#include <Eo.h>
#include "common.h"
#include "xml_sax_base.eo.h"
#include "amin_elt.eo.h"
#include "amin_machine_spec.eo.h"
#include "amin_machine_spec_document.eo.h"

typedef struct
{
    Amin_Machine_Spec_Document *machine_spec;
    Eina_Hash *filters;
} Spec_Data;

static void
_filter_entry_free_cb(void *data)
{
    free(data);
}

EOLIAN static void
_amin_machine_spec_xml_sax_base_document_start(Eo *obj, Spec_Data *pd, void *user_data)
{
    LOG("Initialising Amin Machine specification");

    // Reset the filters.
    pd->filters = eina_hash_pointer_new(_filter_entry_free_cb);

    // Reference machine spec xml
    // TODO Deal with URL etc.



    // Setup the parser.
    Amin_Machine_Spec_Document *handler = efl_add_ref(AMIN_MACHINE_SPEC_DOCUMENT_CLASS, NULL);
    Xml_Sax_Base *parser = efl_add_ref(XML_SAX_BASE_CLASS, NULL);
    xml_sax_base_handler_set(parser, handler);


}

EOLIAN static void
_amin_machine_spec_xml_sax_base_element_start(Eo *obj, Spec_Data *pd, Element *data)
{

}

EOLIAN static void
_amin_machine_spec_xml_sax_base_document_end(Eo *obj, Spec_Data *pd, void *data)
{

}

#include "amin_machine_spec.eo.c"
