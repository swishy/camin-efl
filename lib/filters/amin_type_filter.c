#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "Eo.h"
#include "amin_type_filter.h"

EAPI Eo_Op AMIN_TYPE_FILTER_BASE_ID = 0;

typedef struct
{
   int a;
} Private_Data;

#define MY_CLASS AMIN_TYPE_FILTER_CLASS

static void
_start(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
   Private_Data *pd = class_data;
   int a;
   a = va_arg(*list, int);
   pd->a = a;
   printf("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
}

static void
_end(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
   const Private_Data *pd = class_data;
   int *ret;
   ret = va_arg(*list, int *);
   if (ret)
      *ret = pd->a * pd->a * pd->a;
   printf("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
}

static void
_class_constructor(Eo_Class *klass)
{
   const Eo_Op_Func_Description func_desc[] = {
        EO_OP_FUNC(AMIN_FILTER_INTERFACE_ID(AMIN_FILTER_INTERFACE_SUB_ID_START), _start),
        EO_OP_FUNC(AMIN_FILTER_INTERFACE_ID(AMIN_FILTER_INTERFACE_SUB_ID_END), _end),
        EO_OP_FUNC_SENTINEL
   };

   eo_class_funcs_set(klass, func_desc);
}

static const Eo_Op_Description op_desc[] = {
     EO_OP_DESCRIPTION_SENTINEL
};

static const Eo_Class_Description class_desc = {
     EO_VERSION,
     "Amin Type Filter",
     EO_CLASS_TYPE_REGULAR,
     EO_CLASS_DESCRIPTION_OPS(&AMIN_TYPE_FILTER_BASE_ID, op_desc, AMIN_TYPE_FILTER_SUB_ID_LAST),
     NULL,
     sizeof(Private_Data),
     _class_constructor,
     NULL
};

EO_DEFINE_CLASS(amin_type_filter_class_get, &class_desc, EO_BASE_CLASS, AMIN_FILTER_INTERFACE_CLASS, NULL);
