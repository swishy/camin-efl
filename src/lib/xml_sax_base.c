#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <libxml/SAX.h>
#include "Eo.h"
#include "common.h"
#include "xml_sax_base.h"

EAPI Eo_Op XML_SAX_BASE_BASE_ID = 0;

#define MY_CLASS XML_SAX_BASE

// LIBXML Wrappers
static void
_libxml2_set_document_locator(void * ctx, xmlSAXLocatorPtr loc)
{
   LOG("_libxml2_set_document_locator");
   
   LOGF("locator systemid: %s", loc->getSystemId(&ctx));
   
   // Here we grab current filter and private data for such, if a handler exists we
   // use the handler callback if defined.
   Eo *filter = (Eo*)ctx;
   const Eo_Class *current_class = eo_class_get(filter);
   
   Xml_Base_Data *data = eo_data_ref(filter, XML_SAX_BASE);
   
   Eo *handler = data->handler;
   
   if (handler != NULL)
   {
     eo_do(handler, set_document_locator(ctx, loc));
   } else {
     eo_do(filter, set_document_locator(ctx, loc));
   }
}

static void
_libxml2_document_start(void *user_data)
{
   Eo *filter = (Eo*)user_data;
   const Eo_Class *current_class = eo_class_get(filter);
   
   Xml_Base_Data *data = eo_data_ref(filter, XML_SAX_BASE);
   
   Eo *handler = data->handler;
   
   if (handler != NULL)
   {
     eo_do(handler, document_start(user_data));
   } else {
     eo_do(filter, document_start(user_data));
   }
}

static void
_libxml2_document_end(void *user_data)
{
   Eo *filter = (Eo*)user_data;
   const Eo_Class *current_class = eo_class_get(filter);
   
   Xml_Base_Data *data = eo_data_ref(filter, XML_SAX_BASE);
   
   Eo *handler = data->handler;
   
   if (handler != NULL)
   {
     eo_do(handler, document_end(user_data));
   } else {
     eo_do(filter, document_end(user_data));
   }
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
   // Here we grab current filter and private data for such, if a handler exists we
   // use the handler callback if defined.
   Eo *filter = (Eo*)ctx;
   const Eo_Class *current_class = eo_class_get(filter);
   
   Xml_Base_Data *data = eo_data_ref(filter, XML_SAX_BASE);
   
   Eo *handler = data->handler;

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
   if (handler != NULL)
   {
     eo_do(handler, start(&element_data));
   } else {
     eo_do(filter, start(&element_data));
   }
}

void
_libxml2_char(
	      void *user_data,
	      const xmlChar *string,
	      int string_len)
{
   // Here we grab current filter and private data for such, if a handler exists we
   // use the handler callback if defined.
   Eo *filter = (Eo*)user_data;
   const Eo_Class *current_class = eo_class_get(filter);
   const char *class_name = eo_class_name_get(current_class); 
   
   LOGF("Current handler class is: %s", class_name);
   
   Xml_Base_Data *data = eo_data_scope_get(filter, XML_SAX_BASE);
   
   Eo *handler = data->handler;
   
   if (handler != NULL)
   {
     eo_do(handler, char(data, string, string_len));
   } else {
     eo_do(filter, char(data, string, string_len));
   }
}

void
_libxml2_end(
	     void* ctx,
	     const xmlChar* localname,
	     const xmlChar* prefix,
	     const xmlChar* URI)
{
   // Here we grab current filter and private data for such, if a handler exists we
   // use the handler callback if defined.
   Eo *filter = (Eo*)ctx;
   const Eo_Class *current_class = eo_class_get(filter);
   
   Xml_Base_Data *data = eo_data_ref(filter, XML_SAX_BASE);
   
   Eo *handler = data->handler;

   // TODO move this to a statement which checks end tag name = filter name
   //
   ElementData element_data;
   element_data.ctx = ctx;
   element_data.localname = localname;
   element_data.prefix = prefix;
   element_data.URI = URI;
   
   // Fire in the hole!
   if (handler != NULL)
   {
     eo_do(handler, end(&element_data));
   } else {
     eo_do(filter, end(&element_data));
   }
}

// EFL Functions
//
static void
_parse_string(Eo *obj, void *class_data, va_list *list)
{
  
   Xml_Base_Data *data = class_data;
   // Create a parser instance for this request.
   // TODO this currently is here as having one setup in the constructor
   // results in function references being lost in transit...
   xmlSAXHandler parser;
   memset(&parser, 0, sizeof(xmlSAXHandler));
   parser.initialized = XML_SAX2_MAGIC;

   // Grab XML string from args
   char *xmlString = va_arg(*list, char*);
   data->result = va_arg(*list, void*);

   parser.startDocument = _libxml2_document_start;
   parser.endDocument = _libxml2_document_end;
   parser.startElementNs = _libxml2_start;
   parser.endElementNs = _libxml2_end;
   parser.characters = _libxml2_char;
   parser.setDocumentLocator = _libxml2_set_document_locator;

   if (xmlSAXUserParseMemory(&parser, obj, xmlString, strlen(xmlString)) < 0 )
{
   LOG("Issue parsing XML document");
};
}

static void
_set_document_locator(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
   LOG("XML SAX BASE _set_document_locator called");
}

static void
_document_start(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{

   LOG("XML SAX BASE doc start called");
}

static void
_start(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
   int i;

   ElementData *element = va_arg(*list, ElementData*);

   LOGF("%s %s\n", eo_class_name_get(MY_CLASS), __func__);

   LOGF("ELEMENT: %s", element->localname);

   if (element->nb_attributes > 0)
     {
	for (i = 0; element->attributes[i]; i++)
{
   LOGF("ATTRIBUTE %i %s", i, element->attributes[i]);
    }
  }
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
_end(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{

   LOG("Element End");
   ElementData *element = va_arg(*list, ElementData*);
   LOGF("End element name: %s", element->localname);
}

static void
_document_end(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
   LOG("Document end");
}

static void
_handler_constructor(Eo *obj, void *class_data, va_list *list)
{
   // Get handler from args
   Eo *handler = va_arg(*list, Eo*);
   
   // Assign the current handler.
   Xml_Base_Data  *pd = eo_data_scope_get(obj, XML_SAX_BASE);
   pd->handler = handler;
   
   // Call base constructor.
   eo_do_super(obj, MY_CLASS, eo_constructor());
}

static void
_class_constructor(Eo_Class *klass)
{
   const Eo_Op_Func_Description func_desc[] =
{
   EO_OP_FUNC(XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_HANDLER_CONSTRUCTOR), _handler_constructor),
   EO_OP_FUNC(XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_PARSE_STRING), _parse_string),
   EO_OP_FUNC(XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_SET_DOCUMENT_LOCATOR), _set_document_locator),
   EO_OP_FUNC(XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_DOCUMENT_START), _document_start),
   EO_OP_FUNC(XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_START), _start),
   EO_OP_FUNC(XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_CHAR), _char),
   EO_OP_FUNC(XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_END), _end),
   EO_OP_FUNC(XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_DOCUMENT_END), _document_end),
   EO_OP_FUNC_SENTINEL
};

   eo_class_funcs_set(klass, func_desc);
}

static const Eo_Op_Description op_desc[] =
{
   EO_OP_DESCRIPTION(XML_SAX_BASE_SUB_ID_HANDLER_CONSTRUCTOR, "Custom constructor that allows setting of handler."),
   EO_OP_DESCRIPTION(XML_SAX_BASE_SUB_ID_PARSE_STRING, "Starts processing an XML document."),
   EO_OP_DESCRIPTION(XML_SAX_BASE_SUB_ID_SET_DOCUMENT_LOCATOR, "Recieves the document locator on startup"),
   EO_OP_DESCRIPTION(XML_SAX_BASE_SUB_ID_DOCUMENT_START, "Called when parser starts processing document"),
   EO_OP_DESCRIPTION(XML_SAX_BASE_SUB_ID_START, "Called when start tage hit during parsing"),
   EO_OP_DESCRIPTION(XML_SAX_BASE_SUB_ID_CHAR, "Called when char data found between elements"),
   EO_OP_DESCRIPTION(XML_SAX_BASE_SUB_ID_END, "Called when end tag is hit during parsing"),
   EO_OP_DESCRIPTION(XML_SAX_BASE_SUB_ID_DOCUMENT_END, "Called when end of document is reached during parsing"),
   EO_OP_DESCRIPTION_SENTINEL
};

static const Eo_Class_Description class_desc =
{
   EO_VERSION,
   "XML Sax Base",
   EO_CLASS_TYPE_REGULAR,
   EO_CLASS_DESCRIPTION_OPS(&XML_SAX_BASE_BASE_ID, op_desc, XML_SAX_BASE_SUB_ID_LAST),
   NULL,
   sizeof(Xml_Base_Data),
   _class_constructor,
   NULL
};

EO_DEFINE_CLASS(xml_sax_base_class_get, &class_desc, EO_BASE_CLASS, NULL);
