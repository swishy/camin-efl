#ifndef _XML_SAX_BASE_EO_H_
#define _XML_SAX_BASE_EO_H_

#define XML_SAX_BASE_CLASS xml_sax_base_class_get()

const Eo_Class *xml_sax_base_class_get(void) EINA_CONST;

/**
 *
 * No description supplied.
 *
 * @param[in] handler The custom handler for the current XSB instance
 *
 */
EOAPI void  xml_sax_base_constructor(Eo *handler);

/**
 *
 * This sets the handler of the current XSB object
 *
 * @param[in] handler The handler for the current XSB instance
 *
 */
EOAPI void  xml_sax_base_handler_set(Eo *handler);

/**
 *
 * This gets the handler of the XSB object if set
 *
 *
 */
EOAPI Eo * xml_sax_base_handler_get(void);

/**
 *
 * This sets a custom content handler
 *
 * @param[in] handler The content handler for the current XSB instance
 *
 */
EOAPI void  xml_sax_base_content_handler_set(Eo *handler);

/**
 *
 * This gets the current content handler if set
 *
 *
 */
EOAPI Eo * xml_sax_base_content_handler_get(void);

/**
 *
 * This sets a custom document handler
 *
 * @param[in] handler The document handler for the current XSB instance
 *
 */
EOAPI void  xml_sax_base_document_handler_set(Eo *handler);

/**
 *
 * This gets the current document handler
 *
 *
 */
EOAPI Eo * xml_sax_base_document_handler_get(void);

/**
 *
 * This method starts the parsing process of the XML document passed in
 *
 * @param[in] document The XML Document to parse
 *
 */
EOAPI Eo * xml_sax_base_parse_string(char *document);

/**
 *
 * Receives the document locator on start of parsing
 *
 * @param[in] ctx The Libxml2 parser context
 * @param[in] loc The LibXML2 locator pointer
 *
 */
EOAPI void  xml_sax_base_set_document_locator(void *ctx, xmlSAXLocatorPtr loc);

/**
 *
 * Called when the XML Namespace element is hit
 *
 * @param[in] user_data Function is passed the user_data set
 *
 */
EOAPI void  xml_sax_base_document_start(void *user_data);

/**
 *
 * Called when XML node element start is hit
 *
 * @param[in] elementData Data associated with the element
 *
 */
EOAPI void  xml_sax_base_element_start(ElementData *elementData);

/**
 *
 * Called when XML characters are found within an element
 *
 * @param[in] data No description supplied.
 * @param[in] string No description supplied.
 * @param[in] string_len No description supplied.
 *
 */
EOAPI void  xml_sax_base_element_char(void *data, const xmlChar *string, int string_len);

/**
 *
 * Called when the end of an XML element is hit
 *
 * @param[in] data No description supplied.
 *
 */
EOAPI void  xml_sax_base_element_end(ElementData *data);

/**
 *
 * Called when XML end document is hit
 *
 * @param[in] data No description supplied.
 *
 */
EOAPI void  xml_sax_base_document_end(void *data);


#endif