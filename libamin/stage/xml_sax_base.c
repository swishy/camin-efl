#define EFL_BETA_API_SUPPORT
#include <Eo.h>
#include <libxml/SAX.h>
#include "common.h"
#include "xml_sax_base_types.h"
#include "xml_sax_base.eo.h"

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
    eo_do(filter, xml_sax_base_set_document_locator(ctx, loc));
}

static void
_libxml2_document_start(void *user_data)
{
    LOG("libxml2 doc start callback hit");
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

    LOG("libxml2 start el callback");

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

static void
_libxml2_char(
        void *user_data,
        const xmlChar *string,
        int string_len)
{
    // Pass on through to the other side...
    Eo *filter = (Eo*)user_data;
    eo_do(filter, xml_sax_base_element_char(user_data, string, string_len));
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
    pd->handler = handler;
    eo_do(handler, eo_parent_set(obj));
}

EOLIAN static Eo *
_xml_sax_base_handler_get(Eo *obj, Xml_Base_Data *pd)
{
    return pd->handler;
}

EOLIAN static void
_xml_sax_base_content_handler_set(Eo *obj, Xml_Base_Data *pd, Eo *handler)
{
    pd->content_handler = handler;
}

EOLIAN static Eo *
_xml_sax_base_content_handler_get(Eo *obj, Xml_Base_Data *pd)
{
    return pd->content_handler;
}

EOLIAN static void
_xml_sax_base_document_handler_set(Eo *obj, Xml_Base_Data *pd, Eo *handler)
{
    pd->document_handler = handler;
}

EOLIAN static Eo *
_xml_sax_base_document_handler_get(Eo *obj, Xml_Base_Data *pd)
{
    return pd->document_handler;
}

EOLIAN static Eo *
_xml_sax_base_parse_string(Eo *obj, Xml_Base_Data *pd, char *document)
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
_xml_sax_base_set_document_locator(Eo *obj, Xml_Base_Data *pd, void *ctx, xmlSAXLocatorPtr loc)
{
    LOG("xsb set doc locator");

    Eo *handler = pd->handler;

    if (handler)
    {
        eo_do(handler, xml_sax_base_set_document_locator(ctx, loc));
    } else if(EO_CLASS != XML_SAX_BASE_CLASS) {
        eo_do(obj, xml_sax_base_set_document_locator(ctx, loc));
    } else {
        // Do nothing for the moment
    }
}

EOLIAN static void
_xml_sax_base_document_start(Eo *obj, Xml_Base_Data *pd, void *user_data)
{
    const Eo_Class *current_class = eo_class_get ( obj );
    LOGF ( "Class is : %s %s", eo_class_name_get ( current_class ), __func__ );

    Eo *handler = pd->handler;

    if (handler)
    {
        eo_do(handler, xml_sax_base_document_start(user_data));
    } else if (EO_CLASS != XML_SAX_BASE_CLASS) {
        eo_do(obj, xml_sax_base_document_start(user_data));
    } else {
        // Do nothing for the moment
    }

}

EOLIAN static void
_xml_sax_base_document_end(Eo *obj, Xml_Base_Data *pd, void *data)
{
    const Eo_Class *current_class = eo_class_get ( obj );
    LOGF ( "Class is : %s %s", eo_class_name_get ( current_class ), __func__ );

    Eo *handler = pd->handler;

    if (handler != NULL)
    {
        eo_do(handler, xml_sax_base_document_end(data));
    } else if(EO_CLASS != XML_SAX_BASE_CLASS) {
        eo_do(obj, xml_sax_base_document_end(data));
    } else {
        // Do nothing for the moment
    }
}

EOLIAN static void
_xml_sax_base_element_start(Eo *obj, Xml_Base_Data *pd, ElementData *elementData)
{
    const Eo_Class *current_class = eo_class_get ( obj );
    LOGF ( "Class is : %s %s", eo_class_name_get ( current_class ), __func__ );

    Eo *handler = pd->handler;

    if (handler)
    {
        eo_do(handler, xml_sax_base_element_start(elementData));
    } else if(EO_CLASS != XML_SAX_BASE_CLASS) {
        eo_do(obj, xml_sax_base_element_start(elementData));
    } else {
        // Do nothing for the moment
    }
}

EOLIAN static void
_xml_sax_base_element_char(Eo *obj, Xml_Base_Data *pd, void *data, const xmlChar *string, int string_len)
{
    Eo *handler = pd->handler;

    if (handler)
    {
        eo_do(handler, xml_sax_base_element_char(data, string, string_len));
    } else if(EO_CLASS != XML_SAX_BASE_CLASS) {
        eo_do(obj, xml_sax_base_element_char(data, string, string_len));
    } else {
        // Do nothing for the moment
    }
}

EOLIAN static void
_xml_sax_base_element_end(Eo *obj, Xml_Base_Data *pd, ElementData *data)
{
    const Eo_Class *current_class = eo_class_get ( obj );
    LOGF ( "Class is : %s %s", eo_class_name_get ( current_class ), __func__ );

    Eo *handler = pd->handler;

    if (handler != NULL)
    {
        eo_do(handler, xml_sax_base_element_end(data));
    } else if(EO_CLASS != XML_SAX_BASE_CLASS) {
        eo_do(obj, xml_sax_base_element_end(data));
    } else {
        // Do nothing for the moment
    }
}

#include "xml_sax_base.eo.c"

