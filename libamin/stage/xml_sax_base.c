#include <Eo.h>
#include <libxml/SAX.h>
#include "common.h"
#include "xml_sax_base_types.h"
#include "xml_sax_base.eo.h"

typedef struct
{
    Eo *content_handler;
    Eo *document_handler;
    Eo *handler;
    Eo *result;
}
Xml_Base_Data;

// LIBXML Wrappers
static void
_libxml2_set_document_locator(void * ctx, xmlSAXLocatorPtr loc)
{
    Eo *filter = (Eo*)ctx;
    eo_do(filter, xml_sax_base_set_document_locator(ctx, loc));
}

static void
_libxml2_document_start(void *user_data)
{
    Eo *filter = (Eo*)user_data;
    eo_do(filter, xml_sax_base_document_start(user_data));
}

static void
_libxml2_document_end(void *user_data)
{
    Eo *filter = (Eo*)user_data;
    eo_do(filter, xml_sax_base_document_end(user_data));
}

static void
_libxml2_start(
        void *ctx,
        const xmlChar *localname,
        const xmlChar *prefix,
        const xmlChar *URI,
        int nb_namespaces,
        const xmlChar **namespaces,
        int nb_attributes,
        int nb_defaulted,
        const xmlChar **attributes )
{
    // Here we grab current filter
    Eo *filter = (Eo*)ctx;

    // Populate struct to pass around
    ElementData element_data;
    element_data.ctx = ctx;
    element_data.localname = localname;
    element_data.prefix = prefix;
    element_data.URI = URI;
    element_data.nb_namespaces = nb_namespaces;
    element_data.namespaces = namespaces;
    element_data.nb_attributes = nb_attributes;
    element_data.nb_defaulted = nb_defaulted;
    element_data.attributes = attributes;

    // Fire in the hole!
    eo_do(filter, xml_sax_base_element_start(&element_data));
}

void
_libxml2_char(
        void *user_data,
        const xmlChar *string,
        int string_len)
{
    // Pass on through to the other side...
    Eo *filter = (Eo*)user_data;
    eo_do(filter, xml_sax_base_element_char(user_data, string, string_len));
}

void
_libxml2_end(
        void* ctx,
        const xmlChar* localname,
        const xmlChar* prefix,
        const xmlChar* URI)
{
    // Here we grab current filter and private data for such
    Eo *filter = (Eo*)ctx;

    ElementData element_data;
    element_data.ctx = ctx;
    element_data.localname = localname;
    element_data.prefix = prefix;
    element_data.URI = URI;

    // Fire in the hole!
    eo_do(filter, xml_sax_base_element_end(&element_data));
}

EOLIAN static void
_xml_sax_base_handler_set(Eo *obj, Xml_Base_Data *pd, Eo *handler)
{

}

EOLIAN static Eo *
_xml_sax_base_handler_get(Eo *obj, Xml_Base_Data *pd)
{

}

EOLIAN static void
_xml_sax_base_content_handler_set(Eo *obj, Xml_Base_Data *pd, Eo *handler)
{

}

EOLIAN static Eo *
_xml_sax_base_content_handler_get(Eo *obj, Xml_Base_Data *pd)
{

}

EOLIAN static void
_xml_sax_base_document_handler_set(Eo *obj, Xml_Base_Data *pd, Eo *handler)
{

}

EOLIAN static Eo *
_xml_sax_base_document_handler_get(Eo *obj, Xml_Base_Data *pd)
{

}

EOLIAN static Eo *
_xml_sax_base_parse_string(Eo *obj, Xml_Base_Data *pd, char *document)
{
    Xml_Base_Data *data = pd;
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
    parser.setDocumentLocator = _libxml2_set_document_locator;

    if (xmlSAXUserParseMemory(&parser, obj, document, strlen(document)) < 0 )
    {
        LOG("Issue parsing XML document");
    };

    return data->result;
}

EOLIAN static void
_xml_sax_base_set_document_locator(Eo *obj, Xml_Base_Data *pd, void *ctx, xmlSAXLocatorPtr loc)
{

}

EOLIAN static void
_xml_sax_base_document_start(Eo *obj, Xml_Base_Data *pd, void *user_data)
{
    LOG("Document start called!");

}

EOLIAN static void
_xml_sax_base_start(Eo *obj, Xml_Base_Data *pd, ElementData *elementData)
{

}

EOLIAN static void
_xml_sax_base_char(Eo *obj, Xml_Base_Data *pd, void *data, const xmlChar *string, int string_len)
{

}

EOLIAN static void
_xml_sax_base_end(Eo *obj, Xml_Base_Data *pd, ElementData *data)
{

}

EOLIAN static void
_xml_sax_base_document_end(Eo *obj, Xml_Base_Data *pd, void *data)
{

}

EOLIAN static void
_xml_sax_base_constructor(Eo *obj, Xml_Base_Data *pd, Eo *handler)
{

}

EOLIAN static void
_xml_sax_base_class_constructor(Eo_Class *klass)
{

}

EOLIAN static void
_xml_sax_base_element_start(Eo *obj, Xml_Base_Data *pd, ElementData *elementData)
{

}

EOLIAN static void
_xml_sax_base_element_char(Eo *obj, Xml_Base_Data *pd, void *data, const xmlChar *string, int string_len)
{

}

EOLIAN static void
_xml_sax_base_element_end(Eo *obj, Xml_Base_Data *pd, ElementData *data)
{

}

#include "xml_sax_base.eo.c"

