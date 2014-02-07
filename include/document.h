#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "Eo.h"
#include <Ecore.h>
#include <Ecore_Con.h>

extern EAPI Eo_Op AMIN_MACHINE_SPEC_DOCUMENT_BASE_ID;

typedef struct
{
   const char *element;
   const char *name_space;
   const char *name;
   const char *position;
   const char *download;
   const char *version;
   const char *module;
} Filter_Data;

typedef struct
{
   Eina_List *filters;
   Eina_List *bundles;
   char *machine_name;
   char *generator;
   char *log;
   char **filter_params;
} Machine_Spec_Document;

enum {
     AMIN_MACHINE_SPEC_DOCUMENT_SUB_ID_LAST
};

#define AMIN_MACHINE_SPEC_DOCUMENT_ID(sub_id) (AMIN_MACHINE_SPEC_DOCUMENT_BASE_ID + sub_id)


#define AMIN_MACHINE_SPEC_DOCUMENT amin_machine_spec_document_class_get()
const Eo_Class *amin_machine_spec_document_class_get(void);