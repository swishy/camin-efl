#define EFL_BETA_API_SUPPORT
#include <Eo.h>
#include "common.h"
#include <libxml/SAX.h>
#include "uriparser/Uri.h"
#include "xml_sax_base_types.h"
#include <xml_sax_base.eo.h>
#include "amin.eo.h"
#include "amin_machine_spec.eo.h"

typedef struct
{

} Amin_Data;

static Eina_Bool
_machine_spec_foreach_cb(const Eina_Hash *modules, const void *key,
        void *data, void *fdata)
{
    const char *name = key;
    printf("%s\n", name);
    //Filter_Data *filter = (Filter_Data*)data;
    //LOGF("Lets see if theres a position... %s", filter->position);
    // Return EINA_FALSE to stop this callback from being called
    return EINA_TRUE;
}

EOLIAN static Eo *
_amin_parse(Eo *obj, Amin_Data *pd, char *profile)
{
    // TODO wrap into function.
    // Check if the profile is a URI
    UriParserStateA state;
    UriUriA machine_spec_uri;
    state.uri = &machine_spec_uri;
    Eo *machine_spec;

    if ( uriParseUriA ( &state, profile ) != URI_SUCCESS )
    {
        /* Failure */
        uriFreeUriMembersA ( &machine_spec_uri );
        machine_spec = eo_add(AMIN_MACHINE_SPEC_CLASS, NULL);
    } else {
        machine_spec = eo_add(AMIN_MACHINE_SPEC_CLASS, NULL); // TODO ADD set_uri function to class.
    }

    // Eo *xinclude_filter = eo_add_custom(AMIN_XINCLUDE, NULL, set_handler_constructor(machine_spec));

    // Eo *xml_base = eo_add_custom(XML_SAX_BASE_CLASS, NULL, set_handler_constructor(machine_spec));
    Eo *xml_base = eo_add(XML_SAX_BASE_CLASS, NULL);
    eo_do(xml_base, xml_sax_base_handler_set(machine_spec));

    const Eo_Class *xml_base_class = eo_class_get(xml_base);
    LOGF("obj-type:'%s'\n", eo_class_name_get(xml_base_class));

    LOG("Kicking parser into action....");

    // TODO Move to struct once declared at completeion of machine_spec.
    // Machine_Spec_Document *spec;
    Eo *result = eo_do(xml_base, xml_sax_base_parse_string(profile));

    //eina_hash_foreach(spec->filters, _machine_spec_foreach_cb, NULL);



    /**LOG("Loading AMIN machine spec");
    Eo *amin_machine_spec = eo_add_custom(AMIN_MACHINE_SPEC, NULL, filter_constructor(machine_parser, obj));
    const Eo_Class *machine_class = eo_class_get(amin_machine_spec);
    LOGF("obj-type:'%s'\n", eo_class_name_get(machine_class));
    */
    /**HandlerData handlerData;
    handlerData.current_filter = amin_machine_spec;
    handlerData.saxHandler = machine_parser;

    LOG("start parsing");
    if (xmlSAXUserParseMemory(&machine_parser, &handlerData, profile, strlen(profile)) < 0 ) {
    LOG("Issue parsing XML document");
    };
    */
}

#include "amin.eo.c"
