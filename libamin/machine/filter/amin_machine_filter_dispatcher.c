#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <expat.h>
#include "Eo.h"
#include "common.h"
#include "amin.h"
#include "xml_sax_base.h"
#include "elt.h"
#include "amin_machine_filter_dispatcher.h"

EAPI Eo_Op AMIN_MACHINE_FILTER_DISPATCHER_BASE_ID = 0;

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

#define MY_CLASS AMIN_MACHINE_FILTER_DISPATCHER_CLASS

static void
_start(Eo *obj EINA_UNUSED, void *class_data, va_list *list) {
  int i;

  void *data = va_arg(*list, void*);
  const char *element = va_arg(*list, const char*);
  const char **attributes = va_arg(*list, const char**);

  LOGF("%s %s\n", eo_class_name_get(MY_CLASS), __func__);

  LOG("Dispatching stuff....");

  // TODO Get ref to current class data to access filter.
  //eo_do(pd->filter, start(data, el, attr));


  LOGF("%s", element);

  for (i = 0; attributes[i]; i += 2) {
    LOGF(" %s='%s'", attributes[i], attributes[i + 1]);
  }
}

static void
_class_constructor(Eo_Class *klass)
{
  const Eo_Op_Func_Description func_desc[] = {
    EO_OP_FUNC(XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_START), _start),
    EO_OP_FUNC_SENTINEL
  };

  eo_class_funcs_set(klass, func_desc);
}

static const Eo_Op_Description op_desc[] = {
     EO_OP_DESCRIPTION_SENTINEL
};

static const Eo_Class_Description class_desc = {
     EO_VERSION,
     "Amin Machine Filter Dispatcher",
     EO_CLASS_TYPE_REGULAR,
     EO_CLASS_DESCRIPTION_OPS(&AMIN_MACHINE_FILTER_DISPATCHER_BASE_ID, op_desc, AMIN_MACHINE_FILTER_DISPATCHER_SUB_ID_LAST),
     NULL,
     sizeof(Private_Data),
     _class_constructor,
     NULL
};

EO_DEFINE_CLASS(amin_machine_filter_dispatcher_class_get, &class_desc, AMIN_ELT, EO_BASE_CLASS, NULL);
