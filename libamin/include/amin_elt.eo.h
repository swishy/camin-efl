#ifndef _AMIN_ELT_EO_H_
#define _AMIN_ELT_EO_H_

#define AMIN_ELT_CLASS amin_elt_class_get()

const Eo_Class *amin_elt_class_get(void) EINA_CONST;

/**
 *
 * No description supplied.
 *
 * @param[in] handler The custom handler for the current XSB instance
 *
 */
EOAPI void  amin_elt_constructor(Eo *handler);

/**
 *
 * Returns a configured amin instance to process appropriate document type
 *
 * @param[in] filter No description supplied.
 *
 */
EOAPI Eo * amin_elt_amin_command(Eo *filter);

/**
 *
 * Reimplements Perl regexp magic to ... um ask Bryan...
 *
 * @param[in] filter No description supplied.
 *
 */
EOAPI Eo * amin_elt_white_wash(Eo *filter);


#endif