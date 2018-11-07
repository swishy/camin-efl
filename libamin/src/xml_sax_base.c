#define EFL_BETA_API_SUPPORT
#include <Eo.h>
#include <libxml/SAX.h>
#include "common.h"
#include "xml_sax_base.eo.h"

typedef struct
{
    Eo *content_handler;
    Eo *document_handler;
    Eo *handler;
    Eo *result;
} Xml_Base_Data;

// ERROR LOGGING

static void
_warning(void *user_data, const char *msg, ...) {
    LOGF("%s", msg);
}

static void
_error(void *user_data, const char *msg, ...) {
    LOGF("%s", msg);
}

static void
_fatalError(void *user_data, const char *msg, ...) {
    LOGF("%s", msg);
}


// LIBXML Wrappers
static void
_libxml2_set_document_locator(void * ctx, xmlSAXLocatorPtr loc)
{
    Eo *filter = (Eo*)ctx;
    xml_sax_base_set_document_locator(filter, ctx, loc);
}

static void
_libxml2_document_start(void *user_data)
{
    LOG("libxml2 doc start callback hit");
    Eo *filter = (Eo*)user_data;
    xml_sax_base_document_start(filter, user_data);
}

static void
_libxml2_document_end(void *user_data)
{
    Eo *filter = (Eo*)user_data;
    xml_sax_base_document_end(filter, user_data);
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

    LOG("libxml2 start el callback");

    // Populate struct to pass around
    Element_Data *element_data;
    element_data->localname = (const char*)localname;
    element_data->ctx = ctx;
    element_data->prefix = (const char*)prefix;
    element_data->URI = (const char*)URI;
    element_data->attributes = (const char *) attributes;
    element_data->nb_namespaces = nb_namespaces;
    element_data->nb_attributes = nb_attributes;
    element_data->nb_defaulted = nb_defaulted;

    // Fire in the hole!
    xml_sax_base_element_start(filter, element_data);
}

static void
_libxml2_char(
        void *user_data,
        const xmlChar *string,
        int string_len)
{
    // Pass on through to the other side...
    Eo *filter = (Eo*)user_data;
    xml_sax_base_element_char(filter, user_data, (const char *) string, string_len);
}

static void
_libxml2_end(
        void* ctx,
        const xmlChar* localname,
        const xmlChar* prefix,
        const xmlChar* URI)
{
    // Here we grab current filter and private data for such
    Eo *filter = (Eo*)ctx;

    Element_Data *element_data;
    element_data->localname = (const char*)localname;
    element_data->ctx = ctx;
    element_data->prefix = (const char*)prefix;
    element_data->URI = (const char*)URI;

    // Fire in the hole!
    xml_sax_base_element_end(filter, element_data);
}

EOLIAN static void
_xml_sax_base_handler_set(Eo *obj, Xml_Base_Data *pd, Efl_Object *handler)
{
    pd->handler = handler;
    efl_parent_set(handler, obj);
}

EOLIAN static Efl_Object *
_xml_sax_base_handler_get(const Eo *obj, Xml_Base_Data *pd)
{
    return pd->handler;
}

EOLIAN static void
_xml_sax_base_content_handler_set(Eo *obj, Xml_Base_Data *pd, Efl_Object *handler)
{
    pd->content_handler = handler;
    efl_parent_set(handler, obj);
}

EOLIAN static Efl_Object *
_xml_sax_base_content_handler_get(const Eo *obj, Xml_Base_Data *pd)
{
    return pd->content_handler;
}

EOLIAN static void
_xml_sax_base_document_handler_set(Eo *obj, Xml_Base_Data *pd, Efl_Object *handler)
{
    pd->document_handler = handler;
    efl_parent_set(handler, obj);
}

EOLIAN static Efl_Object *
_xml_sax_base_document_handler_get(const Eo *obj, Xml_Base_Data *pd)
{
    return pd->document_handler;
}

EOLIAN static Efl_Object *
_xml_sax_base_parse_string(Eo *obj, Xml_Base_Data *pd, char document)
{
    LOG("xsb parse string");
    const Efl_Class *current_class = efl_class_get(obj);
    LOGF("obj-type referenced:'%s'\n", efl_class_name_get(current_class));
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

    if (xmlSAXUserParseMemory(&parser, obj, &document, (int) strlen(&document)) < 0 )
    {
        LOG("Issue parsing XML document");
    };

    // Make sure we cleanup the current parser.
    xmlCleanupParser();

    return NULL; //pd->result;
}

EOLIAN static void
_xml_sax_base_set_document_locator(Eo *obj, Xml_Base_Data *pd, void *ctx, void *loc)
{
    LOG("xsb set doc locator");

    Eo *handler = pd->handler;

    if (handler)
    {
        xml_sax_base_set_document_locator(handler, ctx, loc);
    } else if(EO_CLASS != XML_SAX_BASE_CLASS) {
        xml_sax_base_set_document_locator(handler, ctx, loc);
    } else {
        // Do nothing for the moment
    }

}

EOLIAN static void
_xml_sax_base_document_start(Eo *obj, Xml_Base_Data *pd, void *user_data)
{
    const Efl_Class *current_class = efl_class_get(obj);
    LOGF("Document Start called in:'%s'\n", efl_class_name_get(current_class));

    Eo *handler = pd->handler;

    if (handler)
    {
        xml_sax_base_document_start(handler, user_data);
    } else if (EO_CLASS != XML_SAX_BASE_CLASS) {
        xml_sax_base_document_start(obj, user_data);
    } else {
        // Do nothing for the moment
    }
}

EOLIAN static void
_xml_sax_base_element_start(Eo *obj, Xml_Base_Data *pd, Element_Data *data)
{
    const Efl_Class *current_class = efl_class_get(obj);
    LOGF("Element Start called in:'%s'\n", efl_class_name_get(current_class));

    Eo *handler = pd->handler;

    if (handler)
    {
        xml_sax_base_element_start(handler, data);
    } else if(EO_CLASS != XML_SAX_BASE_CLASS) {
        xml_sax_base_element_start(obj, data);
    } else {
        // Do nothing for the moment
    }
}

EOLIAN static void
_xml_sax_base_element_char(Eo *obj, Xml_Base_Data *pd, void *data, const char *string, int string_len)
{
    const Efl_Class *current_class = efl_class_get(obj);
    LOGF("Element Char called in:'%s'\n", efl_class_name_get(current_class));

    Eo *handler = pd->handler;

    if (handler)
    {
        xml_sax_base_element_char(handler, data, string, string_len);
    } else if(EO_CLASS != XML_SAX_BASE_CLASS) {
        xml_sax_base_element_char(obj, data, string, string_len);
    } else {
        // Do nothing for the moment
    }
}

EOLIAN static void
_xml_sax_base_element_end(Eo *obj, Xml_Base_Data *pd, Element_Data *data)
{
    const Efl_Class *current_class = efl_class_get(obj);
    LOGF("Element End called in:'%s'\n", efl_class_name_get(current_class));

    Eo *handler = pd->handler;

    if (handler)
    {
        xml_sax_base_element_end(handler, data);
    } else if(EO_CLASS != XML_SAX_BASE_CLASS) {
        xml_sax_base_element_end(obj, data);
    } else {
        // Do nothing for the moment
    }
}

EOLIAN static void
_xml_sax_base_document_end(Eo *obj, Xml_Base_Data *pd, void *data)
{
    const Efl_Class *current_class = efl_class_get(obj);
    LOGF("Document End called in:'%s'\n", efl_class_name_get(current_class));

    Eo *handler = pd->handler;

    if (handler)
    {
        xml_sax_base_document_end(handler, data);
    } else if(EO_CLASS != XML_SAX_BASE_CLASS) {
        xml_sax_base_document_end(obj, data);
    } else {
        // Do nothing for the moment
    }
}

#include "xml_sax_base.eo.c"
