
void _xml_sax_base_handler_set(Eo *obj, Xml_Base_Data *pd, Eo *handler);

EOAPI EO_VOID_FUNC_BODYV(xml_sax_base_handler_set, EO_FUNC_CALL(handler), Eo *handler);

Eo * _xml_sax_base_handler_get(Eo *obj, Xml_Base_Data *pd);

EOAPI EO_FUNC_BODY(xml_sax_base_handler_get, Eo *, 0);

void _xml_sax_base_content_handler_set(Eo *obj, Xml_Base_Data *pd, Eo *handler);

EOAPI EO_VOID_FUNC_BODYV(xml_sax_base_content_handler_set, EO_FUNC_CALL(handler), Eo *handler);

Eo * _xml_sax_base_content_handler_get(Eo *obj, Xml_Base_Data *pd);

EOAPI EO_FUNC_BODY(xml_sax_base_content_handler_get, Eo *, 0);

void _xml_sax_base_document_handler_set(Eo *obj, Xml_Base_Data *pd, Eo *handler);

EOAPI EO_VOID_FUNC_BODYV(xml_sax_base_document_handler_set, EO_FUNC_CALL(handler), Eo *handler);

Eo * _xml_sax_base_document_handler_get(Eo *obj, Xml_Base_Data *pd);

EOAPI EO_FUNC_BODY(xml_sax_base_document_handler_get, Eo *, 0);

Eo * _xml_sax_base_parse_string(Eo *obj, Xml_Base_Data *pd, char *document);

EOAPI EO_FUNC_BODYV(xml_sax_base_parse_string, Eo *, 0, EO_FUNC_CALL(document), char *document);

void _xml_sax_base_set_document_locator(Eo *obj, Xml_Base_Data *pd, void *ctx, xmlSAXLocatorPtr loc);

EOAPI EO_VOID_FUNC_BODYV(xml_sax_base_set_document_locator, EO_FUNC_CALL(ctx, loc), void *ctx, xmlSAXLocatorPtr loc);

void _xml_sax_base_document_start(Eo *obj, Xml_Base_Data *pd, void *user_data);

EOAPI EO_VOID_FUNC_BODYV(xml_sax_base_document_start, EO_FUNC_CALL(user_data), void *user_data);

void _xml_sax_base_element_start(Eo *obj, Xml_Base_Data *pd, ElementData *elementData);

EOAPI EO_VOID_FUNC_BODYV(xml_sax_base_element_start, EO_FUNC_CALL(elementData), ElementData *elementData);

void _xml_sax_base_element_char(Eo *obj, Xml_Base_Data *pd, void *data, const xmlChar *string, int string_len);

EOAPI EO_VOID_FUNC_BODYV(xml_sax_base_element_char, EO_FUNC_CALL(data, string, string_len), void *data, const xmlChar *string, int string_len);

void _xml_sax_base_element_end(Eo *obj, Xml_Base_Data *pd, ElementData *data);

EOAPI EO_VOID_FUNC_BODYV(xml_sax_base_element_end, EO_FUNC_CALL(data), ElementData *data);

void _xml_sax_base_document_end(Eo *obj, Xml_Base_Data *pd, void *data);

EOAPI EO_VOID_FUNC_BODYV(xml_sax_base_document_end, EO_FUNC_CALL(data), void *data);

static const Eo_Op_Description _xml_sax_base_op_desc[] = {
     EO_OP_FUNC(xml_sax_base_handler_set, _xml_sax_base_handler_set),
     EO_OP_FUNC(xml_sax_base_handler_get, _xml_sax_base_handler_get),
     EO_OP_FUNC(xml_sax_base_content_handler_set, _xml_sax_base_content_handler_set),
     EO_OP_FUNC(xml_sax_base_content_handler_get, _xml_sax_base_content_handler_get),
     EO_OP_FUNC(xml_sax_base_document_handler_set, _xml_sax_base_document_handler_set),
     EO_OP_FUNC(xml_sax_base_document_handler_get, _xml_sax_base_document_handler_get),
     EO_OP_FUNC(xml_sax_base_parse_string, _xml_sax_base_parse_string),
     EO_OP_FUNC(xml_sax_base_set_document_locator, _xml_sax_base_set_document_locator),
     EO_OP_FUNC(xml_sax_base_document_start, _xml_sax_base_document_start),
     EO_OP_FUNC(xml_sax_base_element_start, _xml_sax_base_element_start),
     EO_OP_FUNC(xml_sax_base_element_char, _xml_sax_base_element_char),
     EO_OP_FUNC(xml_sax_base_element_end, _xml_sax_base_element_end),
     EO_OP_FUNC(xml_sax_base_document_end, _xml_sax_base_document_end),
};

static const Eo_Class_Description _xml_sax_base_class_desc = {
     EO_VERSION,
     "Xml_Sax_Base",
     EO_CLASS_TYPE_REGULAR,
     EO_CLASS_DESCRIPTION_OPS(_xml_sax_base_op_desc),
     NULL,
     sizeof(Xml_Base_Data),
     NULL,
     NULL
};

EO_DEFINE_CLASS(xml_sax_base_class_get, &_xml_sax_base_class_desc, EO_BASE_CLASS, NULL);