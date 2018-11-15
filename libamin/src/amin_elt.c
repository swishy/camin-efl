#include <Eo.h>
#include "xml_sax_base.eo.h"
#include "amin_elt.eo.h"

typedef struct
{
    const char *localname;
    const char *prefix;
    const char *command;
    const char *command_name;
} Amin_Elt_Data;

EOLIAN static void
_amin_elt_amin_elt_constructor(Eo *obj, Amin_Elt_Data *pd, Efl_Object *handler)
{

}

EOLIAN static Efl_Object *
_amin_elt_amin_command(Eo *obj, Amin_Elt_Data *pd, Efl_Object *filter)
{

}

EOLIAN static Efl_Object *
_amin_elt_white_wash(Eo *obj, Amin_Elt_Data *pd, Efl_Object *filter)
{

}

EOLIAN static void
_amin_elt_xml_sax_base_document_start(Eo *obj, Amin_Elt_Data *pd, void *user_data)
{
    // TODO implement Amin Elt logic here.
    xml_sax_base_document_start(efl_parent_get(obj), user_data);
}

EOLIAN static void
_amin_elt_class_constructor(Efl_Class *klass)
{

}

#include "amin_elt.eo.c"
