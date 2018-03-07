#ifndef _AMIN_MACHINE_SPEC_DATA_EO_H_
#define _AMIN_MACHINE_SPEC_DATA_EO_H_

#ifndef _AMIN_MACHINE_SPEC_DATA_EO_CLASS_TYPE
#define _AMIN_MACHINE_SPEC_DATA_EO_CLASS_TYPE

typedef Eo Amin_Machine_Spec_Data;

#endif

#ifndef _AMIN_MACHINE_SPEC_DATA_EO_TYPES
#define _AMIN_MACHINE_SPEC_DATA_EO_TYPES


#endif
#define AMIN_MACHINE_SPEC_DATA_CLASS amin_machine_spec_data_class_get()

EWAPI const Efl_Class *amin_machine_spec_data_class_get(void);

/**
 * @brief This sets the filters for the current spec
 *
 * @param[in] obj The object.
 * @param[in] filters The filters for the current machine document
 *
 * @ingroup Amin_Machine_Spec_Data
 */
EOAPI void amin_machine_spec_data_filters_set(Eo *obj, Eina_Hash *filters);

/**
 * @brief This gets the filters for the current machine document if set
 *
 * @param[in] obj The object.
 *
 * @return The filters for the current machine document
 *
 * @ingroup Amin_Machine_Spec_Data
 */
EOAPI Eina_Hash *amin_machine_spec_data_filters_get(const Eo *obj);

#endif
