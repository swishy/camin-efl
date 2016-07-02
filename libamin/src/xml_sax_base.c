#define EFL_BETA_API_SUPPORT
#include <Eo.h>
#include "xml_sax_base.eo.h"

typedef struct
{

} Xml_Base_Data;

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

}

EOLIAN static void
_xml_sax_base_set_document_locator(Eo *obj, Xml_Base_Data *pd, void *ctx, xmlSAXLocatorPtr loc)
{

}

EOLIAN static void
_xml_sax_base_document_start(Eo *obj, Xml_Base_Data *pd, void *user_data)
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

EOLIAN static void
_xml_sax_base_document_end(Eo *obj, Xml_Base_Data *pd, void *data)
{

}

#include "xml_sax_base.eo.c"
