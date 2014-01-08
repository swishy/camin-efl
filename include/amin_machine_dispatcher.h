#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "Eo.h"
#include <Ecore.h>
#include <Ecore_Con.h>

extern EAPI Eo_Op AMIN_MACHINE_DISPATCHER_BASE_ID;

enum {
    AMIN_MACHINE_DISPATCHER_SUB_ID_DISPATCHER_CONSTRUCTOR,
     AMIN_MACHINE_DISPATCHER_SUB_ID_LAST
};

#define AMIN_MACHINE_DISPATCHER_ID(sub_id) (AMIN_MACHINE_DISPATCHER_BASE_ID + sub_id)

/**
 * @def dispatcher_constructor(Eo *, spec)
 * @brief Must be used to construct ELT instance or inherited classes to allow parser delegation.
 */
#define dispatcher_constructor(spec) AMIN_MACHINE_DISPATCHER_ID(AMIN_MACHINE_DISPATCHER_SUB_ID_DISPATCHER_CONSTRUCTOR), EO_TYPECHECK(Eo *, spec)


#define AMIN_MACHINE_DISPATCHER_CLASS amin_machine_dispatcher_class_get()
const Eo_Class *amin_machine_dispatcher_class_get(void);