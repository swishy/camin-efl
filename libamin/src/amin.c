#define EFL_BETA_API_SUPPORT
#include <Eo.h>
#include <common.h>
#include "xml_sax_base.eo.h"
#include "amin.eo.h"
#include "amin_machine_spec.eo.h"
#include "amin_machine_spec_document.eo.h"
#include "uriparser/Uri.h"

typedef struct
{

} Amin_Data;

EOLIAN static Efl_Object *
_amin_parse(const Eo *obj, Amin_Data *pd, const char *profile)
{
    UriParserStateA state;
    UriUriA machine_spec_uri;
    state.uri = &machine_spec_uri;
    Eo *machine_spec;

    if ( uriParseUriA ( &state, profile ) != URI_SUCCESS )
    {
        /* Failure */
        uriFreeUriMembersA ( &machine_spec_uri );
        machine_spec = efl_add(AMIN_MACHINE_SPEC_CLASS, NULL);
    } else {
        machine_spec = efl_add(AMIN_MACHINE_SPEC_CLASS, NULL); // TODO ADD set_uri function to class.
    }

    // OLD Xinclude logic
    // Eo *xinclude_filter = eo_add_custom(AMIN_XINCLUDE, NULL, set_handler_constructor(machine_spec));

    Eo *xml_base = efl_add(XML_SAX_BASE_CLASS, NULL, machine_spec);

    const Efl_Class *xml_base_class = efl_class_get(xml_base);
    LOGF("obj-type:'%s'\n", efl_class_name_get(xml_base_class));

    LOG("Kicking parser into action....");

    // TODO Move to struct once declared at completeion of machine_spec.
    Amin_Machine_Spec_Document *spec;

}

#include "amin.eo.c"
