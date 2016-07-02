#ifndef _AMIN_ELT_EO_H_
#define _AMIN_ELT_EO_H_

#ifndef _AMIN_ELT_EO_CLASS_TYPE
#define _AMIN_ELT_EO_CLASS_TYPE

typedef Eo Amin_Elt;

#endif

#ifndef _AMIN_ELT_EO_TYPES
#define _AMIN_ELT_EO_TYPES


#endif
#define AMIN_ELT_CLASS amin_elt_class_get()

EAPI const Eo_Class *amin_elt_class_get(void) EINA_CONST;

/**
 * @brief Custom constructor to allow setting of a handler at creation
 *
 * @param[in] handler The custom handler for the current XSB instance
 *
 * @ingroup Amin_Elt
 */
EOAPI void  amin_elt_constructor(Eo *handler);

/**
 * @brief Returns a configured amin instance to process appropriate document
 * type
 *
 * @param[in] filter
 *
 * @return Can return any Eo object
 *
 * @ingroup Amin_Elt
 */
EOAPI Eo * amin_elt_amin_command(Eo *filter);

/**
 * @brief Reimplements Perl regexp magic to ... um ask Bryan...
 *
 * @param[in] filter
 *
 * @ingroup Amin_Elt
 */
EOAPI Eo * amin_elt_white_wash(Eo *filter);


#endif
