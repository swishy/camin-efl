#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <expat.h>
#include "Eo.h"
#include "Eina.h"
#include "common.h"
#include "amin_xml_base.h"
#include "amin_elt.h"

int DEPTH;

XML_Parser *parser;

EAPI Eo_Op AMIN_XML_BASE_BASE_ID = 0;

typedef struct
{
   char input;
   Eina_List *filters;
} Private_Data;

#define MY_CLASS AMIN_XML_BASE_CLASS

static void 
_start(void *data, const char *el, const char **attr) {
  int i;
  
  Eo *amin_elt = eo_add_custom(AMIN_ELT_CLASS, NULL, filter_constructor(parser));
  //const Eo_Class *klass = eo_class_get(amin_elt);
  //LOGF("obj-type:'%s'\n", eo_class_name_get(klass));
  
  // TODO Get ref to current class data to access filter.
  //eo_do(pd->filter, start(data, el, attr));
  
  //LOG("Setting element handlers");
  //XML_SetElementHandler(parser, _start2, _end2);
  

  for (i = 0; i < DEPTH; i++)
    LOG("  ");

  LOGF("%s", el);

  for (i = 0; attr[i]; i += 2) {
    LOGF(" %s='%s'", attr[i], attr[i + 1]);
  }

  DEPTH++;
}  /* End of start handler */

static void
_char(void *user_data, const XML_Char *string, int string_len)
{
    // ref important bytes passed in if they arent whitespace.
    if (string_len > 0 && !isspace(*string))
    {
      LOGF("char data in tag: %.*s", string_len, string);
    }    
}

static void 
_end(void *data, const char *el) {
  DEPTH--;
  //eo_do_super(obj, elm_wdg_theme(&int_ret));
}  /* End of end handler */

static void
_process(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
  LOGF("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
  
  LOG("Getting input");
  Private_Data *pd = class_data;
  char *input;
  input = va_arg(*list, char*);
  pd->input = input;
  //pd->filter = eo_add(AMIN_TYPE_FILTER_CLASS,NULL);
  LOG("Got input");
  
  LOGF("INPUT: %s\n", input);
  
  LOG("Initialising parser");
  parser = XML_ParserCreate(NULL);
  if (! parser) {
    LOG("Camin could not allocate memory for parser");
    exit(-1);
  }
  
  LOG("Setting element handlers");
  XML_SetElementHandler(parser, _start, _end);
  XML_SetCharacterDataHandler (parser, _char);
  
  /* parse the xml */
  if(XML_Parse(parser, input, strlen(input), XML_TRUE) == XML_STATUS_ERROR)
  {
    printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));
  }
  
  XML_ParserFree(parser);
}

static void
_class_constructor(Eo_Class *klass)
{
   const Eo_Op_Func_Description func_desc[] = {
        EO_OP_FUNC(AMIN_XML_BASE_ID(AMIN_XML_BASE_SUB_ID_PROCESS), _process),
        EO_OP_FUNC_SENTINEL
   };

   eo_class_funcs_set(klass, func_desc);
}

static const Eo_Op_Description op_desc[] = {
     EO_OP_DESCRIPTION(AMIN_XML_BASE_SUB_ID_PROCESS, "Starts processing an XML document."),
     EO_OP_DESCRIPTION_SENTINEL
};

static const Eo_Class_Description class_desc = {
     EO_VERSION,
     "Amin XML Base",
     EO_CLASS_TYPE_REGULAR,
     EO_CLASS_DESCRIPTION_OPS(&AMIN_XML_BASE_BASE_ID, op_desc, AMIN_XML_BASE_SUB_ID_LAST),
     NULL,
     sizeof(Private_Data),
     _class_constructor,
     NULL
};

EO_DEFINE_CLASS(amin_xml_base_class_get, &class_desc, EO_BASE_CLASS, NULL);