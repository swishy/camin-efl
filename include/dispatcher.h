#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "Eo.h"
#include <Ecore.h>
#include <Ecore_Con.h>

extern EAPI Eo_Op AMIN_MACHINE_DISPATCHER_BASE_ID;

enum {
     AMIN_MACHINE_DISPATCHER_SUB_ID_PARSE_URI,
     AMIN_MACHINE_DISPATCHER_SUB_ID_PARSE_STRING,
     AMIN_MACHINE_DISPATCHER_SUB_ID_LAST
};

#define AMIN_MACHINE_DISPATCHER_ID(sub_id) (AMIN_MACHINE_DISPATCHER_BASE_ID + sub_id)

/**
 * @def parse_uri(url)
 * @brief Starts the Amin machine processing a URI passed in.
 */
#define parse_uri(url) AMIN_MACHINE_DISPATCHER_ID(AMIN_MACHINE_DISPATCHER_SUB_ID_PARSE_URI), EO_TYPECHECK(Ecore_Con_Url *, url)

/**
 * @def parse_string(document)
 * @brief Starts the Amin machine processing a URI passed in.
 */
#define parse_string(document) AMIN_MACHINE_DISPATCHER_ID(AMIN_MACHINE_DISPATCHER_SUB_ID_PARSE_STRING), EO_TYPECHECK(char *, document)

#define AMIN_MACHINE_DISPATCHER_CLASS amin_machine_dispatcher_class_get()
const Eo_Class *amin_machine_dispatcher_class_get(void);