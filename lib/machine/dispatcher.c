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
   char input;
   XML_Parser parser;
} Private_Data;

#define MY_CLASS AMIN_MACHINE_DISPATCHER_CLASS

static void 
_start(void *data, const char *el, const char **attr) {
  int i;
  
  LOGF("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
  
  // TODO Get ref to current class data to access filter.
  //eo_do(pd->filter, start(data, el, attr));

  for (i = 0; i < DEPTH; i++)
    LOG("  ");

  LOGF("%s", el);

  for (i = 0; attr[i]; i += 2) {
    LOGF(" %s='%s'", attr[i], attr[i + 1]);
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
    
    LOGF("Document is: %s", document);
  
  
}

static void
_class_constructor(Eo_Class *klass)
{
  const Eo_Op_Func_Description func_desc[] = {
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