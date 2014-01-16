#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <pcre.h>
#include "Eo.h"
#include "common.h"
#include "elt.h"

int DEPTH;

EAPI Eo_Op AMIN_ELT_BASE_ID = 0;

typedef struct
{
   xmlSAXHandler parser;
   char input;
   Eina_List *attrs;
   Eina_List *filters;
   char command;
   char param;
   char target;
   char flag;
   char name;
   char element;
   char doctype;
   char docname;
   char text;
   Eo *filter;
} Private_Data;

#define MY_CLASS AMIN_ELT

// Wrappers to allow expat delegation to the current ELT subclass instance.
static void
_libxml2_document_start(void *user_data){
    LOG("Document start");
    HandlerData *data = (HandlerData*)user_data;
    Eo *self = (Eo*)data->current_filter;
    eo_do(self, document_start(user_data));
} 

static void
_libxml2_document_end(void *user_data) {
  LOG("Document end");
  HandlerData *data = (HandlerData*)user_data;
  Eo *self = data->current_filter;
  eo_do(self, document_end(user_data));
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
    xmlParserCtxtPtr context = (xmlParserCtxtPtr)ctx;
    Eo *self = context->userData;
    
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
    eo_do(self, document_start(user_data));
} 

static void
_libxml2_char(
  void *user_data, 
  const xmlChar *string, 
  int string_len) {
   HandlerData *data = (HandlerData*)user_data;
   Eo *self = data->current_filter;
   eo_do(self, char(data, string, string_len));
}

static void
_libxml2_end( 
  void* ctx,
  const xmlChar* localname,
  const xmlChar* prefix,
  const xmlChar* URI) {
  DEPTH--;
  
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

static void 
_document_start(Eo *obj EINA_UNUSED, void *class_data, va_list *list) {
  
  LOG("Amin machine spec doc start called");
  
  
}



static void 
_start(Eo *obj EINA_UNUSED, void *class_data, va_list *list) {
  int i;
  
  ElementData *data = va_arg(*list, ElementData*);

  
  LOGF("%s %s\n", eo_class_name_get(MY_CLASS), __func__);

  for (i = 0; i < DEPTH; i++)
    LOG("  ");

  LOGF("ELEMENT: %s", data->localname);

  for (i = 0; data->attributes[i]; i += 2) {
    LOGF("ATTRIBUTE %i %s='%s'", i, data->attributes[i], data->attributes[i + 1]);
  }

  DEPTH++;
}  /* End of start handler */

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
  DEPTH--;
  
  void *data = va_arg(*list, void*);
  const char *element = va_arg(*list, const char*);
  
  // TODO move this to a statement which checks end tag name = filter name
  
  Eo *filter = (Eo*)data;
  
  Eo *parent;
  eo_do(filter, eo_parent_get(&parent));
  
  Private_Data *pd = class_data;
  
  LOG("Delegating parser handling back to parent");
  XML_SetUserData(pd->parser, parent);
}

static void 
_document_end(Eo *obj EINA_UNUSED, void *class_data, va_list *list) {
  LOG("Document end");
}

static void 
_fix_text(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
  LOG("fix text called");
}

static void
_amin_command(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
  LOG("amin_command called");
}

// Trys to shell out and execute command if no amin module exists to handle it.
static void
_white_wash(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
  LOG("white_wash called");
}

static void
_filter_constructor(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
   // Get parser from args.
   xmlSAXHandler parser;
   parser = va_arg(*list, xmlSAXHandler);
   
   // Set parent
   // TODO check if this is required.
   Eo *parent = va_arg(*list, Eo *);
   eo_do(obj, eo_parent_set(parent));
   
   Private_Data *pd = class_data;
   
   // Assign local reference.
   pd->parser = parser;
   
   LOG("Setting document handlers again.");
   parser.startDocument = _libxml2_document_start;
   parser.endDocument = _libxml2_document_end;
   LOG("Setting element handlers again.");
   parser.startElementNs = _libxml2_start;
   parser.endElementNs = _libxml2_end;
   LOG("Setting char handler");
   parser.characters = _libxml2_char;
   
   // Call base constructor.
   eo_do_super(obj, MY_CLASS, eo_constructor());
}

static void
_constructor(Eo *obj, void *_pd EINA_UNUSED, va_list *list EINA_UNUSED)
{
   eo_error_set(obj);
   LOG_ERROR("Please use filter_constructor when creating class '%s'", eo_class_name_get(MY_CLASS));
}

static void
_class_constructor(Eo_Class *klass)
{
   const Eo_Op_Func_Description func_desc[] = {
        EO_OP_FUNC(EO_BASE_ID(EO_BASE_SUB_ID_CONSTRUCTOR), _constructor),
        EO_OP_FUNC(AMIN_ELT_ID(AMIN_ELT_SUB_ID_AMIN_COMMAND), _amin_command),
        EO_OP_FUNC(AMIN_ELT_ID(AMIN_ELT_SUB_ID_WHITE_WASH), _white_wash),
        EO_OP_FUNC(AMIN_ELT_ID(AMIN_ELT_SUB_ID_FILTER_CONSTRUCTOR), _filter_constructor),
        EO_OP_FUNC(AMIN_ELT_ID(AMIN_ELT_SUB_ID_DOCUMENT_START), _document_start),
        EO_OP_FUNC(AMIN_ELT_ID(AMIN_ELT_SUB_ID_START), _start),
        EO_OP_FUNC(AMIN_ELT_ID(AMIN_ELT_SUB_ID_CHAR), _char),
        EO_OP_FUNC(AMIN_ELT_ID(AMIN_ELT_SUB_ID_END), _end),
        EO_OP_FUNC(AMIN_ELT_ID(AMIN_ELT_SUB_ID_DOCUMENT_END), _document_end),
        EO_OP_FUNC_SENTINEL
   };

   eo_class_funcs_set(klass, func_desc);
}

static const Eo_Op_Description op_desc[] = {
     EO_OP_DESCRIPTION(AMIN_ELT_SUB_ID_AMIN_COMMAND, "Starts processing an Amin command."),
     EO_OP_DESCRIPTION(AMIN_ELT_SUB_ID_WHITE_WASH, "Trys to shell out and execute command if no amin module exists to handle it."),
     EO_OP_DESCRIPTION(AMIN_ELT_SUB_ID_FILTER_CONSTRUCTOR, "Constructor function to use for filter instances."),
     EO_OP_DESCRIPTION(AMIN_ELT_SUB_ID_DOCUMENT_START, "Called when XML namespace element is hit."),
     EO_OP_DESCRIPTION(AMIN_ELT_SUB_ID_START, "Called when XML start element is hit."),
     EO_OP_DESCRIPTION(AMIN_ELT_SUB_ID_CHAR, "Called when character data is found within XML element."),
     EO_OP_DESCRIPTION(AMIN_ELT_SUB_ID_END, "Called when XML end element is hit."),
     EO_OP_DESCRIPTION(AMIN_ELT_SUB_ID_DOCUMENT_END, "Called when XML document end is hit."),
     EO_OP_DESCRIPTION_SENTINEL
};

static const Eo_Class_Description class_desc = {
     EO_VERSION,
     "Amin Elt",
     EO_CLASS_TYPE_REGULAR,
     EO_CLASS_DESCRIPTION_OPS(&AMIN_ELT_BASE_ID, op_desc, AMIN_ELT_SUB_ID_LAST),
     NULL,
     sizeof(Private_Data),
     _class_constructor,
     NULL
};

EO_DEFINE_CLASS(amin_elt_class_get, &class_desc, EO_BASE_CLASS, NULL);