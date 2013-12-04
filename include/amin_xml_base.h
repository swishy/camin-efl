#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "Eo.h"

extern EAPI Eo_Op AMIN_XML_BASE_BASE_ID;

enum {
     AMIN_XML_BASE_SUB_ID_PROCESS,
     AMIN_XML_BASE_SUB_ID_START,
     AMIN_XML_BASE_SUB_ID_END,
     AMIN_XML_BASE_SUB_ID_CHAR,
     AMIN_XML_BASE_SUB_ID_LAST
};

#define AMIN_XML_BASE_ID(sub_id) (AMIN_XML_BASE_BASE_ID + sub_id)

/**
 * @def process(document)
 * @brief Starts processing an XML document.
 */
#define process(document) AMIN_XML_BASE_ID(AMIN_XML_BASE_SUB_ID_PROCESS), EO_TYPECHECK(char *, document)

/**
 * @def start(void *data, const char *element, const char **attribute)
 * @brief Called when start element is hit.
 */
#define start(data, element, attribute) AMIN_XML_BASE_ID(AMIN_XML_BASE_SUB_ID_START), EO_TYPECHECK(void *, data), EO_TYPECHECK(const char *, element), EO_TYPECHECK(const char **, attribute)

/**
 * @def end(void *data, const char *element)
 * @brief Called when end element is hit.
 */
#define end(data, element) AMIN_XML_BASE_ID(AMIN_XML_BASE_SUB_ID_END), EO_TYPECHECK(void *, data), EO_TYPECHECK(const char *, element)

/**
 * @def char(void *user_data, const XML_Char *string, int string_len)
 * @brief Called when char data is found.
 */
#define char(user_data, string, string_len) AMIN_XML_BASE_ID(AMIN_XML_BASE_SUB_ID_CHAR), EO_TYPECHECK(void *, user_data), EO_TYPECHECK(const XML_Char *, string), EO_TYPECHECK(int, string_len)

#define AMIN_XML_BASE_CLASS amin_xml_base_class_get()
const Eo_Class *amin_xml_base_class_get(void);