#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "Eo.h"
#include <libxml/SAX2.h>

extern EAPI Eo_Op XML_SAX_BASE_BASE_ID;

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
     XML_SAX_BASE_SUB_ID_PARSE_STRING,
     XML_SAX_BASE_SUB_ID_SET_DOCUMENT_LOCATOR,
     XML_SAX_BASE_SUB_ID_DOCUMENT_START,
     XML_SAX_BASE_SUB_ID_START,
     XML_SAX_BASE_SUB_ID_CHAR,
     XML_SAX_BASE_SUB_ID_END, 
     XML_SAX_BASE_SUB_ID_DOCUMENT_END,
     XML_SAX_BASE_SUB_ID_LAST
};

#define XML_SAX_BASE_ID(sub_id) (XML_SAX_BASE_BASE_ID + sub_id)

/**
 * @def parse(document)
 * @brief Starts parsing a XMl document.
 */
#define parse_string(document) XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_PARSE_STRING), EO_TYPECHECK(const char *, document)

/**
 * @def set_document_locator(void *user_data)
 * @brief Receives the document locator on startup.
 */
#define set_document_locator(user_data) XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_SET_DOCUMENT_LOCATOR), EO_TYPECHECK(void *, user_data)

/**
 * @def document_start(void *user_data)
 * @brief Called when XML namespace element is hit.
 */
#define document_start(user_data) XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_DOCUMENT_START), EO_TYPECHECK(void *, user_data)

/**
 * @def start(ElementData *elementData)
 * @brief Called when XML start element is hit.
 */
#define start(elementData) XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_START), EO_TYPECHECK(ElementData *, elementData)

/**
 * @def char(void *data, const XML_Char *string, int string_len)
 * @brief Called when XML characters are found in element.
 */
#define char(data, string, string_length) XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_CHAR), EO_TYPECHECK(void *, data), EO_TYPECHECK(const xmlChar *, string), EO_TYPECHECK(int, string_len)

/**
 * @def end(ElementData *data)
 * @brief Called when XML start element is hit.
 */
#define end(data) XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_END), EO_TYPECHECK(ElementData *, data)

/**
 * @def document_end(void *data)
 * @brief Called when XML start element is hit.
 */
#define document_end(data) XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_DOCUMENT_END), EO_TYPECHECK(void *, data)

#define XML_SAX_BASE xml_sax_base_class_get()
const Eo_Class *xml_sax_base_class_get(void);