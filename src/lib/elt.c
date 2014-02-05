#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <pcre.h>
#include "Eo.h"
#include "common.h"
#include "xml_sax_base.h"
#include "elt.h"

int DEPTH;

EAPI Eo_Op AMIN_ELT_BASE_ID = 0;

typedef struct
{
   xmlSAXHandler parser;
} Private_Data;

#define MY_CLASS AMIN_ELT

static void
_start_document ( Eo *obj EINA_UNUSED, void *class_data, va_list *list )
{
  const Eo_Class *current_class = eo_class_get ( obj );
  LOGF ( "Class is : %s %s", eo_class_name_get ( current_class ), __func__ );
      // Pass back to XML_SAX_BASE
      eo_do_super ( obj, MY_CLASS, document_start ( va_arg ( *list, Eo* ) ) );
}

static void 
_fix_text(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
  LOG("fix text called");
}

static void
_amin_command(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
  LOG("amin_command called");
}

// Trys to shell out and execute command if no amin module exists to handle it.
static void
_white_wash(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
  LOG("white_wash called");
}

static void
_class_constructor(Eo_Class *klass)
{
   const Eo_Op_Func_Description func_desc[] = {
	EO_OP_FUNC ( XML_SAX_BASE_ID ( XML_SAX_BASE_SUB_ID_DOCUMENT_START ), _start_document ),
        EO_OP_FUNC(AMIN_ELT_ID(AMIN_ELT_SUB_ID_AMIN_COMMAND), _amin_command),
        EO_OP_FUNC(AMIN_ELT_ID(AMIN_ELT_SUB_ID_WHITE_WASH), _white_wash),
        EO_OP_FUNC_SENTINEL
   };

   eo_class_funcs_set(klass, func_desc);
}

static const Eo_Op_Description op_desc[] = {
     EO_OP_DESCRIPTION(AMIN_ELT_SUB_ID_AMIN_COMMAND, "Starts processing an Amin command."),
     EO_OP_DESCRIPTION(AMIN_ELT_SUB_ID_WHITE_WASH, "Trys to shell out and execute command if no amin module exists to handle it."),
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

EO_DEFINE_CLASS(amin_elt_class_get, &class_desc, XML_SAX_BASE, NULL);