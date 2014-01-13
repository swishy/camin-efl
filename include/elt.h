#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <expat.h>
#include "Eo.h"

extern EAPI Eo_Op AMIN_ELT_BASE_ID;

enum {
     AMIN_ELT_SUB_ID_AMIN_COMMAND,
     AMIN_ELT_SUB_ID_WHITE_WASH,
     AMIN_ELT_SUB_ID_FILTER_CONSTRUCTOR,
     AMIN_ELT_SUB_ID_NAMESPACE_START,
     AMIN_ELT_SUB_ID_START,
     AMIN_ELT_SUB_ID_CHAR,
     AMIN_ELT_SUB_ID_END, 
     AMIN_ELT_SUB_ID_NAMESPACE_END,
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
 * @def filter_constructor(XML_Parser *, parser, Eo *, parent)
 * @brief Must be used to construct ELT instance or inherited classes to allow parser delegation.
 */
#define filter_constructor(parser, parent) AMIN_ELT_ID(AMIN_ELT_SUB_ID_FILTER_CONSTRUCTOR), EO_TYPECHECK(XML_Parser, parser), EO_TYPECHECK(Eo *, parent)

/**
 * @def namespace_start(void *data, const char *prefix, const char *uri)
 * @brief Called when XML namespace element is hit.
 */
#define namespace_start(data, prefix, uri) AMIN_ELT_ID(AMIN_ELT_SUB_ID_NAMESPACE_START), EO_TYPECHECK(void *, data), EO_TYPECHECK(const char *, prefix), EO_TYPECHECK(const char *, uri)


/**
 * @def start(void *data, const char *element, const char **attributes)
 * @brief Called when XML start element is hit.
 */
#define start(data, element, attributes) AMIN_ELT_ID(AMIN_ELT_SUB_ID_START), EO_TYPECHECK(void *, data), EO_TYPECHECK(const char *, element), EO_TYPECHECK(const char **, attributes)

/**
 * @def char(void *data, const XML_Char *string, int string_len)
 * @brief Called when XML characters are found in element.
 */
#define char(data, string, string_length) AMIN_ELT_ID(AMIN_ELT_SUB_ID_CHAR), EO_TYPECHECK(void *, data), EO_TYPECHECK(const XML_Char *, string), EO_TYPECHECK(int, string_len)

/**
 * @def end(void *data, const char *element)
 * @brief Called when XML start element is hit.
 */
#define end(data, element) AMIN_ELT_ID(AMIN_ELT_SUB_ID_END), EO_TYPECHECK(void *, data), EO_TYPECHECK(const char *, element)

/**
 * @def namespace_end(void *data, const char *element)
 * @brief Called when XML start element is hit.
 */
#define namespace_end(vdata, prefix) AMIN_ELT_ID(AMIN_ELT_SUB_ID_NAMESPACE_END), EO_TYPECHECK(void *, data), EO_TYPECHECK(const char *, prefix)

#define AMIN_ELT amin_elt_class_get()
const Eo_Class *amin_elt_class_get(void);