#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <Eo.h>

extern EAPI Eo_Op AMIN_FILTER_INTERFACE_BASE_ID;

enum {
     AMIN_FILTER_INTERFACE_SUB_ID_START,
     AMIN_FILTER_INTERFACE_SUB_ID_END,
     AMIN_FILTER_INTERFACE_SUB_ID_LAST
};

#define AMIN_FILTER_INTERFACE_ID(sub_id) (AMIN_FILTER_INTERFACE_BASE_ID + sub_id)


/**
 * @def Delegate for expat start callback
 */
#define start(data, element, attributes) AMIN_FILTER_INTERFACE_ID(AMIN_FILTER_INTERFACE_SUB_ID_START), EO_TYPECHECK(void *, data), EO_TYPECHECK(const char *, element), EO_TYPECHECK(const char *, attributes)

#define end(data, element, attributes) AMIN_FILTER_INTERFACE_ID(AMIN_FILTER_INTERFACE_SUB_ID_END), EO_TYPECHECK(void *, data), EO_TYPECHECK(const char *, element)

#define AMIN_FILTER_INTERFACE_CLASS amin_filter_interface_class_get()
const Eo_Class *amin_filter_interface_class_get(void);