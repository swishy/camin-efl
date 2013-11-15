#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "Eo.h"

extern EAPI Eo_Op AMIN_BASE_ID;

enum {
     AMIN_SUB_ID_PROCESS,
     AMIN_SUB_ID_LAST
};

#define AMIN_ID(sub_id) (AMIN_BASE_ID + sub_id)

/**
 * @def process(document)
 * @brief Returns a configured amin instance to process appropriate document type.
 */
#define process(document) AMIN_ID(AMIN_SUB_ID_PROCESS), EO_TYPECHECK(char *, document)

#define AMIN_CLASS amin_class_get()
const Eo_Class *amin_class_get(void);

