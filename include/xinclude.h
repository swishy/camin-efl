#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <libxml/SAX2.h>
#include "Eo.h"

extern EAPI Eo_Op AMIN_XINCLUDE_BASE_ID;

enum {
     AMIN_XINCLUDE_SUB_ID_LAST
};

#define AMIN_XINCLUDE_ID(sub_id) (AMIN_XINCLUDE_BASE_ID + sub_id)

#define AMIN_XINCLUDE amin_xinclude_class_get()
const Eo_Class *amin_xinclude_class_get(void);