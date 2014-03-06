#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <expat.h>
#include "Eo.h"
#include "common.h"
#include "amin.h"
#include "amin_machine_dispatcher.h"

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

#define MY_CLASS AMIN_MACHINE_DISPATCHER


static void
_dispatcher_constructor(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
   // TODO Reorder filter list.

   // TODO Set machine name in spec

   // TODO Update filter list in spec

}

static void
_constructor(Eo *obj, void *_pd EINA_UNUSED, va_list *list EINA_UNUSED)
{
   eo_error_set(obj);
   LOG_ERROR("Please use _dispatcher_constructor when creating class '%s'", eo_class_name_get(MY_CLASS));
}

static void
_class_constructor(Eo_Class *klass)
{
   const Eo_Op_Func_Description func_desc[] = {
        EO_OP_FUNC(EO_BASE_ID(EO_BASE_SUB_ID_CONSTRUCTOR), _constructor),
        EO_OP_FUNC(AMIN_MACHINE_DISPATCHER_ID(AMIN_MACHINE_DISPATCHER_SUB_ID_DISPATCHER_CONSTRUCTOR), _dispatcher_constructor),
        EO_OP_FUNC_SENTINEL
   };

   eo_class_funcs_set(klass, func_desc);
}

static const Eo_Op_Description op_desc[] = {
     EO_OP_DESCRIPTION(AMIN_MACHINE_DISPATCHER_SUB_ID_DISPATCHER_CONSTRUCTOR, "Constructs a dispatcher."),
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

EO_DEFINE_CLASS(amin_machine_dispatcher_class_get, &class_desc, EO_BASE_CLASS, NULL);
