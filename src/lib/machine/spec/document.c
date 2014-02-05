#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <expat.h>
#include "Eo.h"
#include "common.h"
#include "amin.h"
#include "xml_sax_base.h"
#include "elt.h"
#include "document.h"

int DEPTH;

EAPI Eo_Op AMIN_MACHINE_SPEC_DOCUMENT_BASE_ID = 0;

typedef struct
{
   Eina_List *attrs;
   Eina_List *filters;
} Private_Data;

#define MY_CLASS AMIN_MACHINE_SPEC_DOCUMENT

_start_document ( Eo *obj EINA_UNUSED, void *class_data, va_list *list )
{
  LOG("IN DOCUMENT START DOCUMENT FILTER");
  
  ElementData *element = va_arg ( *list, ElementData* );
  
  const Eo_Class *current_class = eo_class_get ( obj );
  LOGF ( "Class is : %s %s", eo_class_name_get ( current_class ), __func__ );
  
  eo_do_super ( obj, MY_CLASS, document_start ( element ) );
}

static void 
_start(Eo *obj EINA_UNUSED, void *class_data, va_list *list) {
  int i;
  
  ElementData *element = va_arg ( *list, ElementData* );
  
  LOGF("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
  
  LOG("IN DOCUMENT FILTER");
  
  eo_do_super ( obj, MY_CLASS, start ( element ) );
 
} 

static void
_class_constructor(Eo_Class *klass)
{
  const Eo_Op_Func_Description func_desc[] = {
    EO_OP_FUNC(XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_DOCUMENT_START), _start_document),
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
     "Amin Machine Spec Document",
     EO_CLASS_TYPE_REGULAR,
     EO_CLASS_DESCRIPTION_OPS(&AMIN_MACHINE_SPEC_DOCUMENT_BASE_ID, op_desc, AMIN_MACHINE_SPEC_DOCUMENT_SUB_ID_LAST),
     NULL,
     sizeof(Private_Data),
     _class_constructor,
     NULL
};

EO_DEFINE_CLASS(amin_machine_spec_document_class_get, &class_desc, AMIN_ELT, EO_BASE_CLASS, NULL);