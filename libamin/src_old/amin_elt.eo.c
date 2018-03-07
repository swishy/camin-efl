
void _amin_elt_constructor(Eo *obj, Amin_Elt_Data *pd, Eo *handler);

EOAPI EO_VOID_FUNC_BODYV(amin_elt_constructor, EO_FUNC_CALL(handler), Eo *handler);

Eo * _amin_elt_amin_command(Eo *obj, Amin_Elt_Data *pd, Eo *filter);

EOAPI EO_FUNC_BODYV(amin_elt_amin_command, Eo *, 0, EO_FUNC_CALL(filter), Eo *filter);

Eo * _amin_elt_white_wash(Eo *obj, Amin_Elt_Data *pd, Eo *filter);

EOAPI EO_FUNC_BODYV(amin_elt_white_wash, Eo *, 0, EO_FUNC_CALL(filter), Eo *filter);

void _amin_elt_xml_sax_base_document_start(Eo *obj, Amin_Elt_Data *pd, void *user_data);


static const Eo_Op_Description _amin_elt_op_desc[] = {
     EO_OP_FUNC_OVERRIDE(xml_sax_base_document_start, _amin_elt_xml_sax_base_document_start),
     EO_OP_FUNC(amin_elt_constructor, _amin_elt_constructor),
     EO_OP_FUNC(amin_elt_amin_command, _amin_elt_amin_command),
     EO_OP_FUNC(amin_elt_white_wash, _amin_elt_white_wash),
};

static const Eo_Class_Description _amin_elt_class_desc = {
     EO_VERSION,
     "Amin_Elt",
     EO_CLASS_TYPE_REGULAR,
     EO_CLASS_DESCRIPTION_OPS(_amin_elt_op_desc),
     NULL,
     sizeof(Amin_Elt_Data),
     NULL,
     NULL
};

EO_DEFINE_CLASS(amin_elt_class_get, &_amin_elt_class_desc, XML_SAX_BASE_CLASS, NULL);