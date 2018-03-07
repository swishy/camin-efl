
void _amin_machine_spec_data_filters_set(Eo *obj, Spec_Data *pd, Eina_Hash *filters);

EOAPI EO_VOID_FUNC_BODYV(amin_machine_spec_data_filters_set, EO_FUNC_CALL(filters), Eina_Hash *filters);

Eina_Hash * _amin_machine_spec_data_filters_get(Eo *obj, Spec_Data *pd);

EOAPI EO_FUNC_BODY(amin_machine_spec_data_filters_get, Eina_Hash *, 0);

static Eo_Op_Description _amin_machine_spec_data_op_desc[] = {
     EO_OP_FUNC(amin_machine_spec_data_filters_set, _amin_machine_spec_data_filters_set, "This sets the filters for the current spec"),
     EO_OP_FUNC(amin_machine_spec_data_filters_get, _amin_machine_spec_data_filters_get, "This gets the filters for the current machine document if set"),
     EO_OP_SENTINEL
};

static const Eo_Class_Description _amin_machine_spec_data_class_desc = {
     EO_VERSION,
     "Amin_Machine_Spec_Data",
     EO_CLASS_TYPE_REGULAR,
     EO_CLASS_DESCRIPTION_OPS(_amin_machine_spec_data_op_desc),
     NULL,
     sizeof(Spec_Data),
     NULL,
     NULL
};

EO_DEFINE_CLASS(amin_machine_spec_data_class_get, &_amin_machine_spec_data_class_desc, EO_BASE_CLASS, NULL);