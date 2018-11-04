#define EFL_BETA_API_SUPPORT
#include <Eo.h>
#include <libxml/SAX.h>
#include "common.h"
#include "xml_sax_base.eo.h"

typedef struct
{

} Xml_Base_Data;

EOLIAN static void
_xml_sax_base_handler_set(Eo *obj, Xml_Base_Data *pd, Efl_Object *handler)
{

}

EOLIAN static Efl_Object *
_xml_sax_base_handler_get(const Eo *obj, Xml_Base_Data *pd)
{

}

EOLIAN static void
_xml_sax_base_content_handler_set(Eo *obj, Xml_Base_Data *pd, Efl_Object *handler)
{

}

EOLIAN static Efl_Object *
_xml_sax_base_content_handler_get(const Eo *obj, Xml_Base_Data *pd)
{

}

EOLIAN static void
_xml_sax_base_document_handler_set(Eo *obj, Xml_Base_Data *pd, Efl_Object *handler)
{

}

EOLIAN static Efl_Object *
_xml_sax_base_document_handler_get(const Eo *obj, Xml_Base_Data *pd)
{

}

EOLIAN static Efl_Object *
_xml_sax_base_parse_string(Eo *obj, Xml_Base_Data *pd, char document)
{

}

EOLIAN static void
_xml_sax_base_set_document_locator(Eo *obj, Xml_Base_Data *pd, void *ctx, void *loc)
{
    LOG("xsb parse string");

    // Create a parser instance for this request.
    // TODO this currently is here as having one setup in the constructor
    // results in function references being lost in transit...
    xmlSAXHandler parser;
    memset(&parser, 0, sizeof(xmlSAXHandler));
    parser.initialized = XML_SAX2_MAGIC;

    // Setup parser callbacks and start parsing
    parser.startDocument = _libxml2_document_start;
    parser.endDocument = _libxml2_document_end;
    parser.startElementNs = _libxml2_start;
    parser.endElementNs = _libxml2_end;
    parser.characters = _libxml2_char;
    // TODO fix get location issues in XInclude filter.

    // TODO Work out why this goes to town and kills the parser....
    // parser.setDocumentLocator = _libxml2_set_document_locator;

    // Just in for debugging at the moment.
    parser.error = _error;
    parser.warning = _warning;
    parser.fatalError = _fatalError;

    if (xmlSAXUserParseMemory(&parser, obj, document, strlen(document)) < 0 )
    {
        LOG("Issue parsing XML document");
    };

    // Make sure we cleanup the current parser.
    xmlCleanupParser();

    return pd->result;

}

EOLIAN static void
_xml_sax_base_document_start(Eo *obj, Xml_Base_Data *pd, void *user_data)
{

}

EOLIAN static void
_xml_sax_base_element_start(Eo *obj, Xml_Base_Data *pd, void *data)
{

}

EOLIAN static void
_xml_sax_base_element_char(Eo *obj, Xml_Base_Data *pd, void *data, const char *string, int string_len)
{

}

EOLIAN static void
_xml_sax_base_element_end(Eo *obj, Xml_Base_Data *pd)
{

}

EOLIAN static void
_xml_sax_base_document_end(Eo *obj, Xml_Base_Data *pd, void *data)
{

}

#include "xml_sax_base.eo.c"
