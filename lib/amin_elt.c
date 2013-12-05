#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <expat.h>
#include <pcre.h>
#include "Eo.h"
#include "common.h"
#include "amin_elt.h"
#include "amin_xml_base.h"

int DEPTH;

EAPI Eo_Op AMIN_ELT_BASE_ID = 0;

typedef struct
{
   XML_Parser parser;
   char input;
   Eina_List *attrs;
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

#define MY_CLASS AMIN_ELT_CLASS

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
_fix_text(char *input)
{
  LOGF("input %s", input);
}

static void
_amin_command(Eo_Class *klass)
{
  LOG("amin_command called");
}

static void
_white_wash(Eo_Class *klass)
{
  LOG("white_wash called");
}

static void
_filter_constructor(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
  
   eo_do_super(obj, MY_CLASS, eo_constructor());
  
   XML_Parser *parser;
   parser = va_arg(*list, XML_Parser*);
   
   Private_Data *pd = class_data;
   
   pd->parser = parser;
  
   LOG("Setting element handlers again.");
   XML_SetElementHandler(parser, _start, _end);
   LOG("Setting char handler");
   XML_SetCharacterDataHandler (parser, _char);
}

static void
_constructor(Eo *obj, void *_pd EINA_UNUSED, va_list *list EINA_UNUSED)
{
   eo_error_set(obj);
   LOG_ERROR("Please use filter_constructor when creating class '%s'", MY_CLASS);
}

static void
_class_constructor(Eo_Class *klass)
{
   const Eo_Op_Func_Description func_desc[] = {
        EO_OP_FUNC(EO_BASE_ID(EO_BASE_SUB_ID_CONSTRUCTOR), _constructor),
        EO_OP_FUNC(AMIN_ELT_ID(AMIN_ELT_SUB_ID_AMIN_COMMAND), _amin_command),
        EO_OP_FUNC(AMIN_ELT_ID(AMIN_ELT_SUB_ID_WHITE_WASH), _white_wash),
        EO_OP_FUNC(AMIN_ELT_ID(AMIN_ELT_SUB_ID_FILTER_CONSTRUCTOR), _filter_constructor),
        EO_OP_FUNC_SENTINEL
   };

   eo_class_funcs_set(klass, func_desc);
}

static const Eo_Op_Description op_desc[] = {
     EO_OP_DESCRIPTION(AMIN_ELT_SUB_ID_AMIN_COMMAND, "Starts processing an Amin command."),
     EO_OP_DESCRIPTION(AMIN_ELT_SUB_ID_WHITE_WASH, "Resets filter state."),
     EO_OP_DESCRIPTION(AMIN_ELT_SUB_ID_FILTER_CONSTRUCTOR, "Constructor function to use for filter instances."),
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