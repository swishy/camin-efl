#ifndef _AMIN_EO_H_
#define _AMIN_EO_H_

#ifndef _AMIN_EO_CLASS_TYPE
#define _AMIN_EO_CLASS_TYPE

typedef Eo Amin;

#endif

#ifndef _AMIN_EO_TYPES
#define _AMIN_EO_TYPES


#endif
#define AMIN_CLASS amin_class_get()

EWAPI const Efl_Class *amin_class_get(void);

/**
 * @brief Docs - Starts the amin machine processing the current XML profile.
 *
 * @param[in] obj The object.
 * @param[in] profile
 *
 * @ingroup Amin
 */
EOAPI Efl_Object *amin_parse(const Eo *obj, const char *profile) EINA_WARN_UNUSED_RESULT;

#endif
