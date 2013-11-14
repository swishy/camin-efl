#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "Eo.h"
#include "amin_machine.h"
#include "amin.h"

EAPI Eo_Op AMIN_MACHINE_BASE_ID = 0;

typedef struct
{
   int a;
} Private_Data;

#define MY_CLASS AMIN_MACHINE_CLASS

static Eo*
_get_machine(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
  printf("GET_MACHINE Called");
  printf("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
  return eo_add(AMIN_CLASS, NULL);
}


static void
_class_constructor(Eo_Class *klass)
{
   const Eo_Op_Func_Description func_desc[] = {
        EO_OP_FUNC(AMIN_MACHINE_ID(AMIN_MACHINE_SUB_ID_GET_MACHINE), _get_machine),
        EO_OP_FUNC_SENTINEL
   };

   eo_class_funcs_set(klass, func_desc);
}

static const Eo_Op_Description op_desc[] = {
     EO_OP_DESCRIPTION(AMIN_MACHINE_SUB_ID_GET_MACHINE, "Returns an amin instance."),
     EO_OP_DESCRIPTION_SENTINEL
};

static const Eo_Class_Description class_desc = {
     EO_VERSION,
     "Amin Machine",
     EO_CLASS_TYPE_REGULAR,
     EO_CLASS_DESCRIPTION_OPS(&AMIN_MACHINE_BASE_ID, op_desc, AMIN_MACHINE_SUB_ID_LAST),
     NULL,
     sizeof(Private_Data),
     _class_constructor,
     NULL
};

EO_DEFINE_CLASS(amin_machine_class_get, &class_desc, EO_BASE_CLASS, NULL);
