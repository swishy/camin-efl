
void _amin_machine_spec_xml_sax_base_document_start(Eo *obj, Spec_Data *pd, void *user_data);


void _amin_machine_spec_xml_sax_base_element_start(Eo *obj, Spec_Data *pd, ElementData *elementData);


void _amin_machine_spec_xml_sax_base_document_end(Eo *obj, Spec_Data *pd, void *data);


static Eo_Op_Description _amin_machine_spec_op_desc[] = {
     EO_OP_FUNC_OVERRIDE(xml_sax_base_document_start, _amin_machine_spec_xml_sax_base_document_start),
     EO_OP_FUNC_OVERRIDE(xml_sax_base_element_start, _amin_machine_spec_xml_sax_base_element_start),
     EO_OP_FUNC_OVERRIDE(xml_sax_base_document_end, _amin_machine_spec_xml_sax_base_document_end),
     EO_OP_SENTINEL
};

static const Eo_Class_Description _amin_machine_spec_class_desc = {
     EO_VERSION,
     "Amin_Machine_Spec",
     EO_CLASS_TYPE_REGULAR,
     EO_CLASS_DESCRIPTION_OPS(_amin_machine_spec_op_desc),
     NULL,
     sizeof(Spec_Data),
     NULL,
     NULL
};

EO_DEFINE_CLASS(amin_machine_spec_class_get, &_amin_machine_spec_class_desc, AMIN_ELT_CLASS, NULL);