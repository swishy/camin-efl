#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <expat.h>
#include "Eo.h"
#include "common.h"
#include "amin_elt.h"

int DEPTH;

EAPI Eo_Op AMIN_ELT_BASE_ID = 0;

typedef struct
{
   char input;
   Eo *filter;
} Private_Data;

#define MY_CLASS AMIN_ELT_CLASS

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
_class_constructor(Eo_Class *klass)
{
   const Eo_Op_Func_Description func_desc[] = {
        EO_OP_FUNC(AMIN_ELT_ID(AMIN_ELT_SUB_ID_AMIN_COMMAND), _amin_command),
        EO_OP_FUNC(AMIN_ELT_ID(AMIN_ELT_SUB_ID_WHITE_WASH), _white_wash),
        EO_OP_FUNC_SENTINEL
   };

   eo_class_funcs_set(klass, func_desc);
}

static const Eo_Op_Description op_desc[] = {
     EO_OP_DESCRIPTION(AMIN_ELT_SUB_ID_AMIN_COMMAND, "Starts processing an Amin command."),
     EO_OP_DESCRIPTION(AMIN_ELT_SUB_ID_WHITE_WASH, "Resets filter state."),
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