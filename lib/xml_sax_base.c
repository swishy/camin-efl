#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <libxml/SAX.h>
#include "Eo.h"
#include "common.h"
#include "xml_sax_base.h"

EAPI Eo_Op XML_SAX_BASE_BASE_ID = 0;

typedef struct
{
   char input;
} Private_Data;


#define MY_CLASS XML_SAX_BASE

static void
_parse(Eo *obj, void *class_data, va_list *list)
{
  LOG("XML SAX BASE called.");
}

static void
_class_constructor(Eo_Class *klass)
{
  const Eo_Op_Func_Description func_desc[] = {
    EO_OP_FUNC(XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_PARSE), _parse),
    EO_OP_FUNC_SENTINEL
  };
  
  eo_class_funcs_set(klass, func_desc);
}

static const Eo_Op_Description op_desc[] = {
     EO_OP_DESCRIPTION(XML_SAX_BASE_SUB_ID_PARSE, "Starts processing an XML document."),
     EO_OP_DESCRIPTION_SENTINEL
};

static const Eo_Class_Description class_desc = {
     EO_VERSION,
     "XML Sax Base",
     EO_CLASS_TYPE_REGULAR,
     EO_CLASS_DESCRIPTION_OPS(&XML_SAX_BASE_BASE_ID, op_desc, XML_SAX_BASE_SUB_ID_LAST),
     NULL,
     sizeof(Private_Data),
     _class_constructor,
     NULL
};

EO_DEFINE_CLASS(xml_sax_base_class_get, &class_desc, EO_BASE_CLASS, NULL);
