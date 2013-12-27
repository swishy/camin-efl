#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <expat.h>
#include "Eo.h"
#include "common.h"
#include "amin.h"
#include "elt.h"
#include "dispatcher.h"

int DEPTH;

EAPI Eo_Op AMIN_MACHINE_DISPATCHER_BASE_ID = 0;

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

#define MY_CLASS AMIN_MACHINE_DISPATCHER_CLASS

static void 
_start(Eo *obj EINA_UNUSED, void *class_data, va_list *list) {
  int i;
  
  void *data = va_arg(*list, void*);
  const char *element = va_arg(*list, const char*);
  const char **attributes = va_arg(*list, const char**);
  
  LOGF("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
  
  LOG("Im not the start you are looking for....");
  
  // TODO Get ref to current class data to access filter.
  //eo_do(pd->filter, start(data, el, attr));

  for (i = 0; i < DEPTH; i++)
    LOG("  ");

  LOGF("%s", element);

  for (i = 0; attributes[i]; i += 2) {
    LOGF(" %s='%s'", attributes[i], attributes[i + 1]);
  }

  DEPTH++;
} 

static void
_parse_uri(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
  LOG("parse uri");
}
static void
_parse_string(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
  // Get access to parser from private data
    Private_Data *pd = class_data;
   
    // Set local callbacks
    XML_Parser parser = pd->parser;
    
    // Get document passed in
    char *document = va_arg(*list, char*);
    pd->input = document;
    
    LOGF("Document is: %s", document);
  
  
}

static void
_class_constructor(Eo_Class *klass)
{
  const Eo_Op_Func_Description func_desc[] = {
    EO_OP_FUNC(AMIN_ELT_ID(AMIN_ELT_SUB_ID_START), _start),
    EO_OP_FUNC(AMIN_MACHINE_DISPATCHER_ID(AMIN_MACHINE_DISPATCHER_SUB_ID_PARSE_URI), _parse_uri),
    EO_OP_FUNC(AMIN_MACHINE_DISPATCHER_ID(AMIN_MACHINE_DISPATCHER_SUB_ID_PARSE_STRING), _parse_string),
    EO_OP_FUNC_SENTINEL
  };
  
  eo_class_funcs_set(klass, func_desc);
}

static const Eo_Op_Description op_desc[] = {
     EO_OP_DESCRIPTION(AMIN_MACHINE_DISPATCHER_SUB_ID_PARSE_URI, "Starts processing an Amin document."),
     EO_OP_DESCRIPTION(AMIN_MACHINE_DISPATCHER_SUB_ID_PARSE_STRING, "Starts processing an Amin document."),
     EO_OP_DESCRIPTION_SENTINEL
};

static const Eo_Class_Description class_desc = {
     EO_VERSION,
     "Amin Machine Dispatcher",
     EO_CLASS_TYPE_REGULAR,
     EO_CLASS_DESCRIPTION_OPS(&AMIN_MACHINE_DISPATCHER_BASE_ID, op_desc, AMIN_MACHINE_DISPATCHER_SUB_ID_LAST),
     NULL,
     sizeof(Private_Data),
     _class_constructor,
     NULL
};

EO_DEFINE_CLASS(amin_machine_dispatcher_class_get, &class_desc, AMIN_ELT_CLASS, EO_BASE_CLASS, NULL);