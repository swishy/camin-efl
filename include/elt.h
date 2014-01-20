#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <libxml/SAX2.h>
#include "Eo.h"

extern EAPI Eo_Op AMIN_ELT_BASE_ID;

enum {
     AMIN_ELT_SUB_ID_AMIN_COMMAND,
     AMIN_ELT_SUB_ID_WHITE_WASH,
     AMIN_ELT_SUB_ID_FILTER_CONSTRUCTOR,
     AMIN_ELT_SUB_ID_LAST
};

#define AMIN_ELT_ID(sub_id) (AMIN_ELT_BASE_ID + sub_id)

/**
 * @def amin_command(AMIN_ELT)
 * @brief Returns a configured amin instance to process appropriate document type.
 */
#define amin_command(filter) AMIN_ELT_ID(AMIN_ELT_SUB_ID_AMIN_COMMAND), EO_TYPECHECK(Eo_Class *, filter)

/**
 * @def whitewash(AMIN_ELT)
 * @brief Returns a configured amin instance to process appropriate document type.
 */
#define white_wash(filter) AMIN_ELT_ID(AMIN_ELT_SUB_ID_WHITE_WASH), EO_TYPECHECK(Eo_Class *, filter)

/**
 * @def filter_constructor(xmlSAXHandler, parser, Eo *, parent)
 * @brief Must be used to construct ELT instance or inherited classes to allow parser delegation.
 */
#define filter_constructor(parser, parent) AMIN_ELT_ID(AMIN_ELT_SUB_ID_FILTER_CONSTRUCTOR), EO_TYPECHECK(xmlSAXHandler, parser), EO_TYPECHECK(Eo *, parent)

#define AMIN_ELT amin_elt_class_get()
const Eo_Class *amin_elt_class_get(void);