
Eina_Hash * _amin_machine_spec_document_filters_get(Eo *obj, Document_Data *pd);

EOAPI EO_FUNC_BODY(amin_machine_spec_document_filters_get, Eina_Hash *, 0);

void _amin_machine_spec_document_xml_sax_base_document_start(Eo *obj, Document_Data *pd, void *user_data);


void _amin_machine_spec_document_xml_sax_base_element_start(Eo *obj, Document_Data *pd, ElementData *elementData);


void _amin_machine_spec_document_xml_sax_base_element_char(Eo *obj, Document_Data *pd, void *data, const xmlChar *string, int string_len);


void _amin_machine_spec_document_xml_sax_base_element_end(Eo *obj, Document_Data *pd, ElementData *data);


void _amin_machine_spec_document_xml_sax_base_document_end(Eo *obj, Document_Data *pd, void *data);


static Eo_Op_Description _amin_machine_spec_document_op_desc[] = {
     EO_OP_FUNC_OVERRIDE(xml_sax_base_document_start, _amin_machine_spec_document_xml_sax_base_document_start),
     EO_OP_FUNC_OVERRIDE(xml_sax_base_element_start, _amin_machine_spec_document_xml_sax_base_element_start),
     EO_OP_FUNC_OVERRIDE(xml_sax_base_element_char, _amin_machine_spec_document_xml_sax_base_element_char),
     EO_OP_FUNC_OVERRIDE(xml_sax_base_element_end, _amin_machine_spec_document_xml_sax_base_element_end),
     EO_OP_FUNC_OVERRIDE(xml_sax_base_document_end, _amin_machine_spec_document_xml_sax_base_document_end),
     EO_OP_FUNC(amin_machine_spec_document_filters_get, _amin_machine_spec_document_filters_get, "This gets the filters for the current machine document if set"),
     EO_OP_SENTINEL
};

static const Eo_Class_Description _amin_machine_spec_document_class_desc = {
     EO_VERSION,
     "Amin_Machine_Spec_Document",
     EO_CLASS_TYPE_REGULAR,
     EO_CLASS_DESCRIPTION_OPS(_amin_machine_spec_document_op_desc),
     NULL,
     sizeof(Document_Data),
     NULL,
     NULL
};

EO_DEFINE_CLASS(amin_machine_spec_document_class_get, &_amin_machine_spec_document_class_desc, AMIN_ELT_CLASS, NULL);