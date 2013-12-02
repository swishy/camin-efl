#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <expat.h>
#include "Eo.h"
#include "common.h"
#include "amin.h"
#include "amin_xml_base.h"
#include "amin_elt.h"

int DEPTH;

EAPI Eo_Op AMIN_BASE_ID = 0;

typedef struct
{
   char input;
   Eo *handler;
} Private_Data;

#define MY_CLASS AMIN_CLASS

static void
_parse(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
  LOG("Creating Amin Elt Instance");
  Eo *amin_elt = eo_add(AMIN_ELT_CLASS, NULL);
  const Eo_Class *klass = eo_class_get(amin_elt);
  LOGF("obj-type:'%s'\n", eo_class_name_get(klass));
  
  Private_Data *pd = class_data;
  pd->handler = amin_elt;
  
  char *document;
  document = va_arg(*list, char*);
  
  eo_do(amin_elt, process(document));
}

static void
_class_constructor(Eo_Class *klass)
{
   const Eo_Op_Func_Description func_desc[] = {
        EO_OP_FUNC(AMIN_ID(AMIN_SUB_ID_PARSE), _parse),
        EO_OP_FUNC_SENTINEL
   };

   eo_class_funcs_set(klass, func_desc);
}

static const Eo_Op_Description op_desc[] = {
     EO_OP_DESCRIPTION(AMIN_SUB_ID_PARSE, "Starts processing an Amin document."),
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