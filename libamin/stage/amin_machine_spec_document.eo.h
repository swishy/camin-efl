#ifndef _AMIN_MACHINE_SPEC_DOCUMENT_EO_H_
#define _AMIN_MACHINE_SPEC_DOCUMENT_EO_H_

#define AMIN_MACHINE_SPEC_DOCUMENT_CLASS amin_machine_spec_document_class_get()

const Eo_Class *amin_machine_spec_document_class_get(void) EINA_CONST;

/**
 *
 * This gets the filters for the current machine document if set
 *
 *
 */
EOAPI Eina_Hash * amin_machine_spec_document_filters_get(void);


#endif