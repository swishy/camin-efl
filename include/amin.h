#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "Eo.h"

extern EAPI Eo_Op AMIN_BASE_ID;

enum {
     AMIN_SUB_ID_PARSE,
     AMIN_SUB_ID_PROCESS_ADMINLIST,
     AMIN_SUB_ID_PROCESS_PROFILE,
     AMIN_SUB_ID_LAST
};

#define AMIN_ID(sub_id) (AMIN_BASE_ID + sub_id)

/**
 * @def parse(document)
 * @brief Start processing incoming document
 * @param[in] document The XML content
 */
#define parse(document) AMIN_ID(AMIN_SUB_ID_PARSE), EO_TYPECHECK(char, document)

/**
 * @def process_adminlist(adminlist)
 * @brief Process an adminlist
 * @param[out] adminlist An adminlist to process
 */
#define process_adminlist(adminlist) AMIN_ID(AMIN_SUB_ID_PROCESS_ADMINLIST), EO_TYPECHECK(char *, adminlist)

/**
 * @def process_profile(profile)
 * @brief Process a profile
 * @param[out] profile A profile to process
 */
#define process_profile(profile) AMIN_ID(AMIN_SUB_ID_PROCESS_PROFILE), EO_TYPECHECK(char *, profile)

#define AMIN_CLASS amin_class_get()
const Eo_Class *amin_class_get(void);

