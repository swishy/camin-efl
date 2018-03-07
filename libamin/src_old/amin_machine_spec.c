#define EFL_BETA_API_SUPPORT
#include <Eo.h>
#include "amin_machine_spec.eo.h"

typedef struct
{
    Eina_Hash *filters;
    Eo *spec;
} Spec_Data;

static Eina_Bool
_machine_spec_foreach_cb(const Eina_Hash *modules, const void *key,
        void *data, void *fdata)
{
    const char *name = key;
    printf("%s\n", name);

    Filter_Data *filter = (Filter_Data*)data;
    printf("%s\n", filter->module);


    // Return EINA_FALSE to stop this callback from being called
    return EINA_TRUE;
}

EOLIAN static void
_amin_machine_spec_xml_sax_base_document_start(Eo *obj, Spec_Data *pd, void *user_data)
{
    FILE *machine_spec;
    long size;
    char *machine_spec_buffer;

    pd->filters = NULL;

    LOGF("%s %s\n", eo_class_name_get(EO_CLASS), __func__);

    // Get size of machine_spec and read in.
    // TODO implement error handling
    if ((machine_spec = fopen("/etc/amin/machine_spec.xml", "rb")))
    {
        fseek(machine_spec, 0, SEEK_END);
        size = ftell(machine_spec);
        fseek(machine_spec, 0, SEEK_SET);
    } else {
        perror("Error");
    }

    if ((machine_spec_buffer = malloc(size)))
    {
        fread(machine_spec_buffer, 1, size, machine_spec);
    }

    // Set up filter chain.
    Eo *machine_spec_document = eo_add(AMIN_MACHINE_SPEC_DOCUMENT_CLASS, NULL);

    // TODO fix xinclude
    // Eo *xinclude_filter = eo_add_custom(AMIN_XINCLUDE, NULL, set_handler_constructor(machine_spec_document));

    Eo *xml_base = eo_add(XML_SAX_BASE_CLASS, NULL);
    eo_do(xml_base, xml_sax_base_handler_set(machine_spec_document));

    LOG("Kicking parser into action in machine_spec....");

    // Start Machine Spec parsing and assign results to local var.
    pd->spec = eo_do(xml_base, xml_sax_base_parse_string(machine_spec_buffer));

    LOG("Calling foreach in machine_spec document_start");
    eina_hash_foreach(eo_do(pd->spec, amin_machine_spec_document_filters_get()), _machine_spec_foreach_cb, NULL);
}

EOLIAN static void
_amin_machine_spec_xml_sax_base_element_start(Eo *obj, Spec_Data *pd, ElementData *elementData)
{
    const Eo_Class *current_class = eo_class_get ( obj );
    LOGF ( "Class is : %s %s", eo_class_name_get ( current_class ), __func__ );
}

EOLIAN static void
_amin_machine_spec_xml_sax_base_document_end(Eo *obj, Spec_Data *pd, void *data)
{
    const Eo_Class *current_class = eo_class_get ( obj );
    LOGF ( "Class is : %s %s", eo_class_name_get ( current_class ), __func__ );

    // TODO need to implement pattern to tidy this crud up.

    Eo *parent = eo_do(obj, eo_parent_get());

    Xml_Base_Data *xd = eo_data_scope_get(parent, XML_SAX_BASE_CLASS);

    Eo *spec = eo_add(AMIN_MACHINE_SPEC_DATA_CLASS, NULL);
    eo_do(spec, amin_machine_spec_data_filters_set(pd->filters));

    if(!xd) eo_error_set(obj);

    xd->result = spec;
}

#include "amin_machine_spec.eo.c"
