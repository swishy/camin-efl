#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <expat.h>
#include "Eo.h"
#include "common.h"
#include "amin.h"
#include "elt.h"
#include "machine_spec.h"
#include "document.h"

int DEPTH;

EAPI Eo_Op AMIN_MACHINE_SPEC_BASE_ID = 0;

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

#define MY_CLASS AMIN_MACHINE_SPEC_CLASS

static void 
_start(Eo *obj EINA_UNUSED, void *class_data, va_list *list) {
  int i;
  
  void *data = va_arg(*list, void*);
  const char *element = va_arg(*list, const char*);
  const char **attributes = va_arg(*list, const char**);
  
  Private_Data *pd = class_data;
  
  pd->filters = NULL;
  
  LOGF("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
  
  LOG("MachineSpec start....");
  
  // Create a parser instance for this request.
  XML_Parser document_parser = XML_ParserCreate(NULL);
  if (! document_parser) {
    LOG("Camin could not allocate memory for parser");
    ecore_shutdown();
  }
  
  // TODO place holder till we have /etc/amin/machine_spec.xml etc loaded.
  const char *spec = "<machine xmlns:amin=\"http://projectamin.org/ns/\"></machine>";
  
  Eo *document = eo_add_custom(AMIN_MACHINE_SPEC_DOCUMENT_CLASS, NULL, filter_constructor(document_parser));
  const Eo_Class *document_class = eo_class_get(document);
  LOGF("obj-type:'%s'\n", eo_class_name_get(document_class));
  
  // Let Expat do its thing, the local event callbacks are assigned to the parser instance
    // as they are dynamically loaded up the stack. Here we just kick it off.
    if(XML_Parse(document_parser, spec, strlen(spec), XML_TRUE) == XML_STATUS_ERROR)
    {
	LOGF("Error: %s\n", XML_ErrorString(XML_GetErrorCode(document_parser)));
    }
  
} 

static void
_class_constructor(Eo_Class *klass)
{
  const Eo_Op_Func_Description func_desc[] = {
    EO_OP_FUNC(AMIN_ELT_ID(AMIN_ELT_SUB_ID_START), _start),
    EO_OP_FUNC_SENTINEL
  };
  
  eo_class_funcs_set(klass, func_desc);
}

static const Eo_Op_Description op_desc[] = {
     EO_OP_DESCRIPTION_SENTINEL
};

static const Eo_Class_Description class_desc = {
     EO_VERSION,
     "Amin Machine Spec",
     EO_CLASS_TYPE_REGULAR,
     EO_CLASS_DESCRIPTION_OPS(&AMIN_MACHINE_SPEC_BASE_ID, op_desc, AMIN_MACHINE_SPEC_SUB_ID_LAST),
     NULL,
     sizeof(Private_Data),
     _class_constructor,
     NULL
};

EO_DEFINE_CLASS(amin_machine_spec_class_get, &class_desc, AMIN_ELT_CLASS, EO_BASE_CLASS, NULL);