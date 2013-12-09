#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <expat.h>
#include "Eo.h"
#include "common.h"
#include "amin.h"
#include "amin_elt.h"

int DEPTH;

EAPI Eo_Op AMIN_BASE_ID = 0;

typedef struct
{
   char input;
} Private_Data;

#define MY_CLASS AMIN_CLASS

_parse_uri(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
  LOG("PARSE_URI Not currently implemented");
}

static void
_parse_string(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
  // TODO check if URI!

  // Document is only thing passed to us so pop if off the list.
  char *document;
  document = va_arg(*list, char*);
  
  // Create a parser instance for this request.
  XML_Parser parser = XML_ParserCreate(NULL);
  if (! parser) {
    LOG("Camin could not allocate memory for parser");
    ecore_shutdown();
  }
  
  // Load up initial filter instance to start parsing document. 
  LOG("Creating Amin ELT Instance");
  Eo *amin_elt = eo_add_custom(AMIN_ELT_CLASS, NULL, filter_constructor(parser));
  const Eo_Class *klass = eo_class_get(amin_elt);
  LOGF("obj-type:'%s'\n", eo_class_name_get(klass));
  
  // Let Expat do its thing, the local event callbacks are assigned to the parser instance
  // as they are dynamically loaded up the stack. Here we just kick it off, callbacks are assigned
  // in the ELT instance at this point.
  if(XML_Parse(parser, document, strlen(document), XML_TRUE) == XML_STATUS_ERROR)
  {
    printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));
  }
  
  XML_ParserFree(parser);
}

static void
_class_constructor(Eo_Class *klass)
{
  const Eo_Op_Func_Description func_desc[] = {
    EO_OP_FUNC(AMIN_ID(AMIN_SUB_ID_PARSE_URI), _parse_uri),
    EO_OP_FUNC(AMIN_ID(AMIN_SUB_ID_PARSE_STRING), _parse_string),
    EO_OP_FUNC_SENTINEL
  };
  
  eo_class_funcs_set(klass, func_desc);
}

static const Eo_Op_Description op_desc[] = {
     EO_OP_DESCRIPTION(AMIN_SUB_ID_PARSE_URI, "Starts processing an URL containing an Amin document."),
     EO_OP_DESCRIPTION(AMIN_SUB_ID_PARSE_STRING, "Starts processing an Amin document."),
     EO_OP_DESCRIPTION_SENTINEL
};

static const Eo_Class_Description class_desc = {
     EO_VERSION,
     "Amin",
     EO_CLASS_TYPE_REGULAR,
     EO_CLASS_DESCRIPTION_OPS(&AMIN_BASE_ID, op_desc, AMIN_SUB_ID_LAST),
     NULL,
     sizeof(Private_Data),
     _class_constructor,
     NULL
};

EO_DEFINE_CLASS(amin_class_get, &class_desc, EO_BASE_CLASS, NULL);