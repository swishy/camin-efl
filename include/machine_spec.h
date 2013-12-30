#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "Eo.h"
#include <Ecore.h>
#include <Ecore_Con.h>

extern EAPI Eo_Op AMIN_MACHINE_SPEC_BASE_ID;

enum {
     AMIN_MACHINE_SPEC_SUB_ID_LAST
};

#define AMIN_MACHINE_SPEC_ID(sub_id) (AMIN_MACHINE_SPEC_BASE_ID + sub_id)

#define AMIN_MACHINE_SPEC_CLASS amin_machine_spec_class_get()
const Eo_Class *amin_machine_spec_class_get(void);