
Eo * _amin_parse(Eo *obj, Amin_Data *pd, char *profile);

EOAPI EO_FUNC_BODYV(amin_parse, Eo *, 0, EO_FUNC_CALL(profile), char *profile);

static Eo_Op_Description _amin_op_desc[] = {
     EO_OP_FUNC(amin_parse, _amin_parse, "Starts the amin machine processing the current XML profile"),
     EO_OP_SENTINEL
};

static const Eo_Class_Description _amin_class_desc = {
     EO_VERSION,
     "Amin",
     EO_CLASS_TYPE_REGULAR,
     EO_CLASS_DESCRIPTION_OPS(_amin_op_desc),
     NULL,
     sizeof(Amin_Data),
     NULL,
     NULL
};

EO_DEFINE_CLASS(amin_class_get, &_amin_class_desc, EO_BASE_CLASS, NULL);