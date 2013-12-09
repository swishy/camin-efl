#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "Eo.h"
#include <Ecore.h>
#include <Ecore_Con.h>

extern EAPI Eo_Op AMIN_BASE_ID;

enum {
     AMIN_SUB_ID_PARSE_URI,
     AMIN_SUB_ID_PARSE_STRING,
     AMIN_SUB_ID_LAST
};

#define AMIN_ID(sub_id) (AMIN_BASE_ID + sub_id)

/**
 * @def parse_uri(url)
 * @brief Starts the Amin machine processing a URI passed in.
 */
#define parse_uri(url) AMIN_ID(AMIN_SUB_ID_PARSE_URI), EO_TYPECHECK(Ecore_Con_Url *, url)

/**
 * @def parse_string(document)
 * @brief Starts the Amin machine processing a XML document passed in.
 */
#define parse_string(document) AMIN_ID(AMIN_SUB_ID_PARSE_STRING), EO_TYPECHECK(char *, document)

#define AMIN_CLASS amin_class_get()
const Eo_Class *amin_class_get(void);

