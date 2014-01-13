#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <expat.h>
#include <pcre.h>
#include "Eo.h"
#include "common.h"
#include "elt.h"

int DEPTH;

EAPI Eo_Op AMIN_ELT_BASE_ID = 0;

typedef struct
{
   XML_Parser parser;
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
void
_expat_namespace_start(void *data, const char *prefix, const char *uri) {
  printf("Name space start, uri: %s\n", uri);
  Eo *self = (Eo*)data;
  eo_do(self, namespace_start(data, prefix, uri));
} 

void
_expat_namespace_end(void *data, const char *prefix) {
  printf("Namespace end, uri: %s\n", prefix);
  Eo *self = (Eo*)data;
  eo_do(self, namespace_end(data, prefix));
}

static void
_expat_start(void *data, const char *el, const char **attr) {
  
  Eo *self = (Eo*)data;
  eo_do(self, start(data, el, attr));
}

static void
_expat_char(void *data, const XML_Char *string, int string_len)
{
   Eo *self = (Eo*)data;
   eo_do(self, char(data, string, string_len));
}

static void
_expat_end(void *data, const char *el) {
  DEPTH--;
  
  // TODO move this to a statement which checks end tag name = filter name
  
  Eo *self = (Eo*)data;
  eo_do(self, end(data, el));
}

static void 
_namespace_start(Eo *obj EINA_UNUSED, void *class_data, va_list *list) {
  
}

static void 
_start(Eo *obj EINA_UNUSED, void *class_data, va_list *list) {
  int i;
  
  void *data = va_arg(*list, void*);
  const char *element = va_arg(*list, const char*);
  const char **attributes = va_arg(*list, const char**);
  
  LOGF("%s %s\n", eo_class_name_get(MY_CLASS), __func__);

  for (i = 0; i < DEPTH; i++)
    LOG("  ");

  LOGF("ELEMENT: %s", element);

  for (i = 0; attributes[i]; i += 2) {
    LOGF("ATTRIBUTE %i %s='%s'", i, attributes[i], attributes[i + 1]);
  }

  DEPTH++;
}  /* End of start handler */

static void
_char(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
  void *data = va_arg(*list, void*);
  const XML_Char *string = va_arg(*list, const XML_Char*);
  int length = va_arg(*list, int);

    // ref important bytes passed in if they arent whitespace.
    if (length > 0 && !isspace(*string))
    {
      LOGF("char data in tag: %.*s", length, string);
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
_namespace_end(Eo *obj EINA_UNUSED, void *class_data, va_list *list) {
  
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
   XML_Parser parser;
   parser = va_arg(*list, XML_Parser);
   
   // Set parent
   // TODO check if this is required.
   Eo *parent = va_arg(*list, Eo *);
   eo_do(obj, eo_parent_set(parent));
   
   Private_Data *pd = class_data;
   
   // Assign local reference.
   pd->parser = parser;
   LOG("Assigning current instance as expat userdata");
   XML_SetUserData(parser, obj); 
   LOG("Setting element handlers again.");
   XML_SetElementHandler(parser, _expat_start, _expat_end);
   LOG("Setting char handler");
   XML_SetCharacterDataHandler (parser, _expat_char);
   LOG("Setting namespace handlers");
   XML_SetNamespaceDeclHandler(parser, _expat_namespace_start, _expat_namespace_end);
   
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
        EO_OP_FUNC(AMIN_ELT_ID(AMIN_ELT_SUB_ID_NAMESPACE_START), _namespace_start),
        EO_OP_FUNC(AMIN_ELT_ID(AMIN_ELT_SUB_ID_START), _start),
        EO_OP_FUNC(AMIN_ELT_ID(AMIN_ELT_SUB_ID_CHAR), _char),
        EO_OP_FUNC(AMIN_ELT_ID(AMIN_ELT_SUB_ID_END), _end),
        EO_OP_FUNC(AMIN_ELT_ID(AMIN_ELT_SUB_ID_NAMESPACE_END), _namespace_end),
        EO_OP_FUNC_SENTINEL
   };

   eo_class_funcs_set(klass, func_desc);
}

static const Eo_Op_Description op_desc[] = {
     EO_OP_DESCRIPTION(AMIN_ELT_SUB_ID_AMIN_COMMAND, "Starts processing an Amin command."),
     EO_OP_DESCRIPTION(AMIN_ELT_SUB_ID_WHITE_WASH, "Trys to shell out and execute command if no amin module exists to handle it."),
     EO_OP_DESCRIPTION(AMIN_ELT_SUB_ID_FILTER_CONSTRUCTOR, "Constructor function to use for filter instances."),
     EO_OP_DESCRIPTION(AMIN_ELT_SUB_ID_NAMESPACE_START, "Called when XML namespace element is hit."),
     EO_OP_DESCRIPTION(AMIN_ELT_SUB_ID_START, "Called when XML start element is hit."),
     EO_OP_DESCRIPTION(AMIN_ELT_SUB_ID_CHAR, "Called when character data is found within XML element."),
     EO_OP_DESCRIPTION(AMIN_ELT_SUB_ID_END, "Called when XML end element is hit."),
     EO_OP_DESCRIPTION(AMIN_ELT_SUB_ID_NAMESPACE_END, "Called when XML document end is hit."),
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