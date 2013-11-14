#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "Eo.h"

extern EAPI Eo_Op AMIN_MACHINE_BASE_ID;

enum {
     AMIN_MACHINE_SUB_ID_GET_MACHINE,
     AMIN_MACHINE_SUB_ID_LAST
};

#define AMIN_MACHINE_ID(sub_id) (AMIN_MACHINE_BASE_ID + sub_id)

/**
 * @def get_machine()
 * @brief Returns a configured amin instance to process appropriate document type.
 */
#define get_machine() AMIN_MACHINE_ID(AMIN_MACHINE_SUB_ID_GET_MACHINE)

#define AMIN_MACHINE_CLASS amin_machine_class_get()
const Eo_Class *amin_machine_class_get(void);
