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
   Eo *Handler;
   xmlSAXHandler parser;
} Private_Data;


#define MY_CLASS XML_SAX_BASE

// LIBXML Wrappers

static void
_libxml2_document_start(void *user_data){
    LOG("Document start");
} 

static void
_libxml2_document_end(void *user_data) {
  LOG("Document end");
  Eo *self = (Eo*)user_data;
  eo_do(self, document_end(self));
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
  const xmlChar **attributes ){
    LOG("_libxml2_start");
    
    // Get the current filter from the libxml2 context
    Eo *self = (Eo*)ctx;
    
    // Populate struct to pass around
    ElementData *data;
    data->ctx = ctx;
    data->localname = localname;
    data->prefix = prefix;
    data->URI = URI;
    data->nb_namespaces = nb_namespaces;
    data->namespaces = namespaces;
    data->nb_attributes = nb_attributes;
    data->nb_defaulted = nb_defaulted;
    data->attributes = attributes;
    
    // Fire in the hole! 
    eo_do(self, start(data));
} 

void
_libxml2_char(
  void *user_data, 
  const xmlChar *string, 
  int string_len) {
   HandlerData *data = (HandlerData*)user_data;
   Eo *self = data->current_filter;
   eo_do(self, char(data, string, string_len));
}

void
_libxml2_end( 
  void* ctx,
  const xmlChar* localname,
  const xmlChar* prefix,
  const xmlChar* URI) {
  
  // TODO move this to a statement which checks end tag name = filter name
  
  ElementData *data;
  data->ctx = ctx;
  data->localname = localname;
  data->prefix = prefix;
  data->URI = URI;
  
  // Get the current filter from the libxml2 context
  xmlParserCtxtPtr context = (xmlParserCtxtPtr)ctx;
  Eo *self = context->userData;
  eo_do(self, end(data));
}

// EFL Functions

static void
_parse_string(Eo *obj, void *class_data, va_list *list)
{
  // Create a parser instance for this request.
   xmlSAXHandler parser;
   memset(&parser, 0, sizeof(xmlSAXHandler));
   parser.initialized = XML_SAX2_MAGIC;

   // Grab XML string from args
  char *xmlString = va_arg(*list, char*);
   
   LOG("Setting document handlers.");
   parser.startDocument = _libxml2_document_start;
   //parser.endDocument = _libxml2_document_end;
   //LOG("Setting element handlers again.");
   parser.startElementNs = _libxml2_start;
   
   if (xmlSAXUserParseMemory(&parser, obj, xmlString, strlen(xmlString)) < 0 ) {
    LOG("Issue parsing XML document");
  };
   
  /**LOG("XML SAX BASE parse string called.");
  Private_Data *pd = class_data;
  
  // Grab XML string from args
  char *xmlString = va_arg(*list, char*);
  
  xmlSAXHandler handler = (xmlSAXHandler)pd->parser;
  
  LOG("start parsing");
  if (xmlSAXUserParseMemory(&handler, obj, xmlString, strlen(xmlString)) < 0 ) {
    LOG("Issue parsing XML document");
  };
  
  LOG("XML SAX BASE parse completed.");*/
}

static void 
_document_start(Eo *obj EINA_UNUSED, void *class_data, va_list *list) {
  
  LOG("XML SAX BASE doc start called");  
}

static void 
_start(Eo *obj EINA_UNUSED, void *class_data, va_list *list) {
  int i;
  
  ElementData *element = va_arg(*list, ElementData*);
  
  LOGF("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
  
  LOG("Before call to elementdata");

  LOGF("ELEMENT: %s", element->localname);

  /**for (i = 0; data->attributes[i]; i += 2) {
    LOGF("ATTRIBUTE %i %s='%s'", i, data->attributes[i], data->attributes[i + 1]);
  }*/
}

static void
_char(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
  void *data = va_arg(*list, void*);
  const xmlChar *string = va_arg(*list, const xmlChar*);
  int length = va_arg(*list, int);

    // ref important bytes passed in if they arent whitespace.
    if (length > 0 && !isspace(*string))
    {
      LOGF("char data in tag: %i.%s", length, string);
    }    
}

static void 
_end(Eo *obj EINA_UNUSED, void *class_data, va_list *list) {

  LOG("Element End");
}

static void 
_document_end(Eo *obj EINA_UNUSED, void *class_data, va_list *list) {
  LOG("Document end");
}

static void
_constructor(Eo *obj, void *_pd, va_list *list EINA_UNUSED)
{
   LOG("XML SAX BASE CONSTRUCTOR");
  
   // Create a parser instance for this request.
   xmlSAXHandler parser;
   memset(&parser, 0, sizeof(xmlSAXHandler));
   parser.initialized = XML_SAX2_MAGIC;

   Private_Data *pd = _pd;
   
   // Assign local reference.
   pd->parser = parser;
   
   LOG("Setting document handlers.");
   //parser.startDocument = _libxml2_document_start;
   //parser.endDocument = _libxml2_document_end;
   //LOG("Setting element handlers again.");
   parser.startElementNs = _libxml2_start;
   //parser.endElementNs = _libxml2_end;
   //LOG("Setting char handler");
   //parser.characters = _libxml2_char;
   
   // Call base constructor.
   eo_do_super(obj, MY_CLASS, eo_constructor());
}

static void
_class_constructor(Eo_Class *klass)
{
  const Eo_Op_Func_Description func_desc[] = {
    EO_OP_FUNC(EO_BASE_ID(EO_BASE_SUB_ID_CONSTRUCTOR), _constructor),
    EO_OP_FUNC(XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_PARSE_STRING), _parse_string),
    EO_OP_FUNC(XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_DOCUMENT_START), _document_start),
    EO_OP_FUNC(XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_START), _start),
    EO_OP_FUNC(XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_CHAR), _char),
    EO_OP_FUNC(XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_END), _end),
    EO_OP_FUNC(XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_DOCUMENT_END), _document_end),
    EO_OP_FUNC_SENTINEL
  };
  
  eo_class_funcs_set(klass, func_desc);
}

static const Eo_Op_Description op_desc[] = {
     EO_OP_DESCRIPTION(XML_SAX_BASE_SUB_ID_PARSE_STRING, "Starts processing an XML document."),
     EO_OP_DESCRIPTION(XML_SAX_BASE_SUB_ID_DOCUMENT_START, "Called when parser starts processing document"),
     EO_OP_DESCRIPTION(XML_SAX_BASE_SUB_ID_START, "Called when start tage hit during parsing"),
     EO_OP_DESCRIPTION(XML_SAX_BASE_SUB_ID_CHAR, "Called when char data found between elements"),
     EO_OP_DESCRIPTION(XML_SAX_BASE_SUB_ID_END, "Called when end tag is hit during parsing"),
     EO_OP_DESCRIPTION(XML_SAX_BASE_SUB_ID_DOCUMENT_END, "Called when end of document is reached during parsing"),
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
