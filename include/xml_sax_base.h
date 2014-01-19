#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "Eo.h"
#include <libxml/SAX2.h>

extern EAPI Eo_Op XML_SAX_BASE_BASE_ID;

enum {
     XML_SAX_BASE_SUB_ID_PARSE,
     XML_SAX_BASE_SUB_ID_LAST
};

#define XML_SAX_BASE_ID(sub_id) (XML_SAX_BASE_BASE_ID + sub_id)

/**
 * @def parse(document)
 * @brief Starts the Amin machine processing a XML document passed in.
 */
#define parse(document) XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_PARSE), EO_TYPECHECK(char *, document)

#define XML_SAX_BASE xml_sax_base_class_get()
const Eo_Class *xml_sax_base_class_get(void);