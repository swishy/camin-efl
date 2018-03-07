
void _amin_machine_spec_data_filters_set(Eo *obj, Spec_Data *pd, Eina_Hash *filters);

EOAPI EFL_VOID_FUNC_BODYV(amin_machine_spec_data_filters_set, EFL_FUNC_CALL(filters), Eina_Hash *filters);

Eina_Hash *_amin_machine_spec_data_filters_get(Eo *obj, Spec_Data *pd);

EOAPI EFL_FUNC_BODY_CONST(amin_machine_spec_data_filters_get, Eina_Hash *, NULL);

static Eina_Bool
_amin_machine_spec_data_class_initializer(Efl_Class *klass)
{
   const Efl_Object_Ops *opsp = NULL, *copsp = NULL;

#ifndef AMIN_MACHINE_SPEC_DATA_EXTRA_OPS
#define AMIN_MACHINE_SPEC_DATA_EXTRA_OPS
#endif

   EFL_OPS_DEFINE(ops,
      EFL_OBJECT_OP_FUNC(amin_machine_spec_data_filters_set, _amin_machine_spec_data_filters_set),
      EFL_OBJECT_OP_FUNC(amin_machine_spec_data_filters_get, _amin_machine_spec_data_filters_get),
      AMIN_MACHINE_SPEC_DATA_EXTRA_OPS
   );
   opsp = &ops;

#ifdef AMIN_MACHINE_SPEC_DATA_EXTRA_CLASS_OPS
   EFL_OPS_DEFINE(cops, AMIN_MACHINE_SPEC_DATA_EXTRA_CLASS_OPS);
   copsp = &cops;
#endif

   return efl_class_functions_set(klass, opsp, copsp);
}

static const Efl_Class_Description _amin_machine_spec_data_class_desc = {
   EO_VERSION,
   "Amin.Machine.Spec.Data",
   EFL_CLASS_TYPE_REGULAR,
   sizeof(Spec_Data),
   _amin_machine_spec_data_class_initializer,
   NULL,
   NULL
};

EFL_DEFINE_CLASS(amin_machine_spec_data_class_get, &_amin_machine_spec_data_class_desc, EFL_OBJECT_CLASS, NULL);
