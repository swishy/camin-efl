#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "Eo.h"

extern EAPI Eo_Op AMIN_XML_BASE_BASE_ID;

enum {
     AMIN_XML_BASE_SUB_ID_PROCESS,
     AMIN_XML_BASE_SUB_ID_LAST
};

#define AMIN_XML_BASE_ID(sub_id) (AMIN_XML_BASE_BASE_ID + sub_id)

/**
 * @def process(document)
 * @brief Starts processing an XML document.
 */
#define process(document) AMIN_XML_BASE_ID(AMIN_XML_BASE_SUB_ID_PROCESS), EO_TYPECHECK(char *, document)

#define AMIN_XML_BASE_CLASS amin_xml_base_class_get()
const Eo_Class *amin_xml_base_class_get(void);