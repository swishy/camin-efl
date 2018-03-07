#define EFL_BETA_API_SUPPORT
#include <Eo.h>
#include "amin_machine_spec_data.eo.h"

typedef struct
{
    Eina_Hash *filters;
} Spec_Data;

EOLIAN static void
_amin_machine_spec_data_filters_set(Eo *obj, Spec_Data *pd, Eina_Hash *filters)
{
    return pd->filters;
}

EOLIAN static Eina_Hash *
_amin_machine_spec_data_filters_get(Eo *obj, Spec_Data *pd)
{
    pd->filters = filters;
}

#include "amin_machine_spec_data.eo.c"
