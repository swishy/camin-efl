#include <Eo.h>
#include "xml_sax_base.eo.h"
#include "amin_elt.eo.h"
#include "amin_machine_spec.eo.h"
#include "amin_machine_spec_document.eo.h"

typedef struct
{
    Amin_Machine_Spec_Document *machine_spec;
    Eina_Hash *filters;
} Spec_Data;

EOLIAN static void
_amin_machine_spec_xml_sax_base_document_start(Eo *obj, Spec_Data *pd, void *user_data)
{
    pd->machine_spec = efl_add(AMIN_MACHINE_SPEC_DOCUMENT_CLASS, NULL);
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
