#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <libxml/SAX2.h>
#include "Eo.h"

extern EAPI Eo_Op AMIN_ELT_BASE_ID;

// Struct to maintain state through the parser.
typedef struct ElementData
{
  void *ctx;
  const xmlChar *localname;
  const xmlChar *prefix;
  const xmlChar *URI;
  int nb_namespaces;
  const xmlChar **namespaces;
  int nb_attributes;
  int nb_defaulted;
  const xmlChar **attributes; 
} ElementData ;

enum {
     AMIN_ELT_SUB_ID_AMIN_COMMAND,
     AMIN_ELT_SUB_ID_WHITE_WASH,
     AMIN_ELT_SUB_ID_FILTER_CONSTRUCTOR,
     AMIN_ELT_SUB_ID_DOCUMENT_START,
     AMIN_ELT_SUB_ID_START,
     AMIN_ELT_SUB_ID_CHAR,
     AMIN_ELT_SUB_ID_END, 
     AMIN_ELT_SUB_ID_DOCUMENT_END,
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

/**
 * @def document_start(void *user_data)
 * @brief Called when XML namespace element is hit.
 */
#define document_start(user_data) AMIN_ELT_ID(AMIN_ELT_SUB_ID_DOCUMENT_START), EO_TYPECHECK(void *, data)

/**
 * @def start(ElementData *elementData)
 * @brief Called when XML start element is hit.
 */
#define start(elementData) AMIN_ELT_ID(AMIN_ELT_SUB_ID_START), EO_TYPECHECK(void *, elementData)

/**
 * @def char(void *data, const XML_Char *string, int string_len)
 * @brief Called when XML characters are found in element.
 */
#define char(data, string, string_length) AMIN_ELT_ID(AMIN_ELT_SUB_ID_CHAR), EO_TYPECHECK(void *, data), EO_TYPECHECK(const xmlChar *, string), EO_TYPECHECK(int, string_len)

/**
 * @def end(void *data)
 * @brief Called when XML start element is hit.
 */
#define end(data) AMIN_ELT_ID(AMIN_ELT_SUB_ID_END), EO_TYPECHECK(void *, data)

/**
 * @def document_end(void *data, const char *element)
 * @brief Called when XML start element is hit.
 */
#define document_end(data) AMIN_ELT_ID(AMIN_ELT_SUB_ID_DOCUMENT_END), EO_TYPECHECK(void *, data)

#define AMIN_ELT amin_elt_class_get()
const Eo_Class *amin_elt_class_get(void);