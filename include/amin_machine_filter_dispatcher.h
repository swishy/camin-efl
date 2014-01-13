#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "Eo.h"
#include <Ecore.h>
#include <Ecore_Con.h>

extern EAPI Eo_Op AMIN_MACHINE_FILTER_DISPATCHER_BASE_ID;

enum {
     AMIN_MACHINE_FILTER_DISPATCHER_SUB_ID_LAST
};

#define AMIN_MACHINE_FILTER_DISPATCHER_ID(sub_id) (AMIN_MACHINE_FILTER_DISPATCHER_BASE_ID + sub_id)


#define AMIN_MACHINE_FILTER_DISPATCHER_CLASS amin_machine_filter_dispatcher_class_get()
const Eo_Class *amin_machine_filter_dispatcher_class_get(void);