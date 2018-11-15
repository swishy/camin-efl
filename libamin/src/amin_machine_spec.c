#include <Eo.h>
#include <Efl_Core.h>
#include "common.h"
#include "filter_data.eot.h"
#include "xml_sax_base.eo.h"
#include "amin_elt.eo.h"
#include "amin_machine_spec.eo.h"
#include "amin_machine_spec_document.eo.h"

static const char *MACHINE_SPEC_PATH = "/etc/amin/machine_spec.xml";

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
    EINA_LOG_INFO("Initialising Amin Machine specification");

    // Reset the filters.
    pd->filters = eina_hash_pointer_new(_filter_entry_free_cb);

    // Reference machine spec xml
    // TODO Deal with URL etc.

    // TODO handle URI

    // Attempt to read from /etc
    EINA_RW_SLICE_DECLARE(content, 2048);
    Efl_Io_File *file;
    file = efl_new(EFL_IO_FILE_CLASS,
                   efl_file_set(efl_added, MACHINE_SPEC_PATH, NULL), // mandatory
                   efl_io_closer_close_on_invalidate_set(efl_added, EINA_TRUE));

    if (!file) {
        file = efl_new(EFL_IO_FILE_CLASS,
                       efl_file_set(efl_added, "libamin/src/machine_spec.xml", NULL), // mandatory
                       efl_io_closer_close_on_invalidate_set(efl_added, EINA_TRUE));
    }

    if (!file) {
        EINA_LOG_WARN("Unable to open machine spec!");
        // TODO error nicely.
        efl_exit(-1);
    }

    EINA_LOG_INFO("Opened Amin machine spec for reading\n");

    if (efl_io_reader_read(file, &content) != EINA_ERROR_NO_ERROR)
        fprintf(stderr, "  Failed to read test file\n");
    else
    {
        char *machine_spec_xml = eina_rw_slice_strdup(content);

        // Setup the parser.
        Amin_Machine_Spec_Document *handler = efl_add_ref(AMIN_MACHINE_SPEC_DOCUMENT_CLASS, NULL);
        Xml_Sax_Base *parser = efl_add_ref(XML_SAX_BASE_CLASS, NULL);
        xml_sax_base_handler_set(parser, handler);
        xml_sax_base_parse_string(parser, machine_spec_xml);


        free(machine_spec_xml);
    }

    efl_unref(file);
}

EOLIAN static void
_amin_machine_spec_xml_sax_base_element_start(Eo *obj, Spec_Data *pd, Element *data)
{
    EINA_LOG_DBG(element_localname_get(data));
}

EOLIAN static void
_amin_machine_spec_xml_sax_base_document_end(Eo *obj, Spec_Data *pd, void *data)
{

}

#include "amin_machine_spec.eo.c"
