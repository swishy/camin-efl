#ifndef _AMIN_EO_H_
#define _AMIN_EO_H_

#define AMIN_CLASS amin_class_get()

const Eo_Class *amin_class_get(void) EINA_CONST;

/**
 *
 * Starts the amin machine processing the current XML document
 *
 * @param[in] document No description supplied.
 *
 */
EOAPI Eo * amin_parse(char *document);


#endif