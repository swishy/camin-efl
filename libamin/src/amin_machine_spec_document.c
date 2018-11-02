#define EFL_BETA_API_SUPPORT
#include <Eo.h>
#include <common.h>
#include "xml_sax_base.eo.h"
#include "amin_elt.eo.h"
#include "amin_machine_spec_document.eo.h"

static const char FILTER_TAG[] = "filter";
static const char BUNDLE_TAG[] = "bundle";
static const char GENERATOR_TAG[] = "generator";
static const char HANDLER_TAG[] = "handler";
static const char LOG_TAG[] = "log";
static const char MACHINE_NAME_TAG[] = "name";

static const char ELEMENT_TAG[] = "element";
static const char NAMESPACE_TAG[] = "namespace";
static const char NAME_TAG[] = "name";
static const char POSITION_TAG[] = "position";
static const char DOWNLOAD_TAG[] = "download";
static const char VERSION_TAG[] = "version";
static const char FILTER_PARAMS_TAG[] = "filter_param";

typedef struct
{
    const char *localname;
    char *element;
    Eo *mparent;
    char *log;
    char *filter_param;
    char *download;
    char *module;
    char *version;
    char *generator;
    char *handler_name;
    char *handler_out;
    const char *element_name;
    const char *name;
    const char *machine_name;
    const char *position;
    const char *name_space;
    Eina_Hash *filters;
} Spec_Data;

static void
_filter_entry_free_cb(void *data)
{
    free(data);
}

EOLIAN static void
_amin_machine_spec_document_xml_sax_base_document_start(Eo *obj, Spec_Data *pd, void *user_data)
{
    const Efl_Class *current_class = efl_class_get ( obj );
    LOGF ( "Class is : %s %s", efl_class_name_get ( current_class ), __func__ );
    // Setup Eina_Hash to collect filters found during parsing.
    pd->filters = eina_hash_string_superfast_new(_filter_entry_free_cb);
}

EOLIAN static void
_amin_machine_spec_document_xml_sax_base_element_start(Eo *obj, Spec_Data *pd, void *data)
{

}

EOLIAN static void
_amin_machine_spec_document_xml_sax_base_element_char(Eo *obj, Spec_Data *pd, void *data, const char *string, int string_len)
{

}

EOLIAN static void
_amin_machine_spec_document_xml_sax_base_element_end(Eo *obj, Spec_Data *pd)
{

}

EOLIAN static void
_amin_machine_spec_document_xml_sax_base_document_end(Eo *obj, Spec_Data *pd, void *data)
{

}

#include "amin_machine_spec_document.eo.c"