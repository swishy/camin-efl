#ifndef _XML_SAX_BASE_EO_H_
#define _XML_SAX_BASE_EO_H_

#ifndef _XML_SAX_BASE_EO_CLASS_TYPE
#define _XML_SAX_BASE_EO_CLASS_TYPE

typedef Eo Xml_Sax_Base;

#endif

#ifndef _XML_SAX_BASE_EO_TYPES
#define _XML_SAX_BASE_EO_TYPES


#endif
#define XML_SAX_BASE_CLASS xml_sax_base_class_get()

EAPI const Eo_Class *xml_sax_base_class_get(void) EINA_CONST;

/**
 * @brief This sets the handler of the current XSB object
 *
 * @param[in] handler The handler for the current XSB instance
 *
 * @ingroup Xml_Sax_Base
 */
EOAPI void  xml_sax_base_handler_set(Eo *handler);

/**
 * @brief This gets the handler of the XSB object if set
 *
 * @return The handler for the current XSB instance
 *
 * @ingroup Xml_Sax_Base
 */
EOAPI Eo * xml_sax_base_handler_get(void);

/**
 * @brief This sets a custom content handler
 *
 * @param[in] handler The content handler for the current XSB instance
 *
 * @ingroup Xml_Sax_Base
 */
EOAPI void  xml_sax_base_content_handler_set(Eo *handler);

/**
 * @brief This gets the current content handler if set
 *
 * @return The content handler for the current XSB instance
 *
 * @ingroup Xml_Sax_Base
 */
EOAPI Eo * xml_sax_base_content_handler_get(void);

/**
 * @brief This sets a custom document handler
 *
 * @param[in] handler The document handler for the current XSB instance
 *
 * @ingroup Xml_Sax_Base
 */
EOAPI void  xml_sax_base_document_handler_set(Eo *handler);

/**
 * @brief This gets the current document handler
 *
 * @return The document handler for the current XSB instance
 *
 * @ingroup Xml_Sax_Base
 */
EOAPI Eo * xml_sax_base_document_handler_get(void);

/**
 * @brief This method starts the parsing process of the XML document passed in
 *
 * @param[in] document The XML Document to parse
 *
 * @return Can return any Eo object
 *
 * @ingroup Xml_Sax_Base
 */
EOAPI Eo * xml_sax_base_parse_string(char *document);

/**
 * @brief Receives the document locator on start of parsing
 *
 * @param[in] loc The LibXML2 locator pointer
 *
 * @ingroup Xml_Sax_Base
 */
EOAPI void  xml_sax_base_set_document_locator(void *ctx, xmlSAXLocatorPtr loc);

/**
 * @brief Called when the XML Namespace element is hit
 *
 * @param[in] user_data Function is passed the user_data set
 *
 * @ingroup Xml_Sax_Base
 */
EOAPI void  xml_sax_base_document_start(void *user_data);

/**
 * @brief Called when XML node element start is hit
 *
 * @param[in] elementData Data associated with the element
 *
 * @ingroup Xml_Sax_Base
 */
EOAPI void  xml_sax_base_element_start(ElementData *elementData);

/**
 * @brief Called when XML characters are found within an element
 *
 * @param[in] string
 * @param[in] string_len
 *
 * @ingroup Xml_Sax_Base
 */
EOAPI void  xml_sax_base_element_char(void *data, const xmlChar *string, int string_len);

/**
 * @brief Called when the end of an XML element is hit
 *
 * @param[in] data
 *
 * @ingroup Xml_Sax_Base
 */
EOAPI void  xml_sax_base_element_end(ElementData *data);

/**
 * @brief Called when XML end document is hit
 *
 * @param[in] data
 *
 * @ingroup Xml_Sax_Base
 */
EOAPI void  xml_sax_base_document_end(void *data);


#endif
