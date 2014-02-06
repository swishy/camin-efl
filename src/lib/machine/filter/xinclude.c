#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <pcre.h>
#include <string.h>
#include "Eo.h"
#include "Eina.h"
#include "common.h"
#include "xml_sax_base.h"
#include "elt.h"
#include "xinclude.h"
#include "uriparser/Uri.h"

int DEPTH;

EAPI Eo_Op AMIN_XINCLUDE_BASE_ID = 0;

static const char XINCLUDE_NAMESPACE[] = "http://www.w3.org/2001/XInclude";

static const char NS_XML[] = "http://www.w3.org/XML/1998/namespace";

static const char XINCLUDE_TAG[] = "include";

static const char CWD[] = "/";

typedef struct
{
  Eo *handler;
  Eo *current_filter;
  Eina_Array *locators;
  Eina_Array *bases;
  const xmlChar **attributes;
  char *href;
  int depth;
  int level;
}
XInclude_Data;

#define MY_CLASS AMIN_XINCLUDE

static void
_start_document ( Eo *obj EINA_UNUSED, void *class_data, va_list *list )
{
  //Xml_Base_Data *data = class_data;
  XInclude_Data *pd = class_data;
  pd->level = 0;
  if ( pd->depth == 0 )
    {
      // Pass back to XML_SAX_BASE
      eo_do_super ( obj, MY_CLASS, document_start ( va_arg ( *list, Eo* ) ) );
    }
  pd->depth++;
}

static void
_start ( Eo *obj EINA_UNUSED, void *class_data, va_list *list )
{
  const Eo_Class *current_class = eo_class_get ( obj );
  LOGF ( "Class is : %s %s", eo_class_name_get ( current_class ), __func__ );

  
  XInclude_Data *pd = class_data;
  ElementData *element = va_arg ( *list, ElementData* );
  if ( pd->level == 0 )
    {
      pd->attributes = element->attributes;

      // Handle XML_BASE stuff?? 
      // TODO investigate what X::S::B is currently doing also.

      // Handle xincludes
      LOGF ( "XML URI %s", element->URI );
      LOGF ( "XML localname %s", element->localname );

      if ( element->URI != NULL )
        {
          if ( strncmp ( element->URI,XINCLUDE_NAMESPACE,sizeof ( XINCLUDE_NAMESPACE ) ) == 0 &&  strncmp ( element->localname,XINCLUDE_TAG,sizeof ( XINCLUDE_TAG ) ) == 0 )
            {
              if ( element->nb_attributes > 0 )
                {
                  int i = 0;
                  int attribute_position = 0;
                  char *parse_value;

                  // Get values from attributes
                  while ( i < element->nb_attributes )
                    {
                      if ( element->attributes[attribute_position] != NULL )
                        {
                          if ( strncmp ( element->attributes[attribute_position],"href",sizeof ( element->attributes[attribute_position] ) ) == 0 )
                            {
                              int attribute_length = ( strlen ( element->attributes[attribute_position + 3] ) - strlen ( element->attributes[attribute_position + 4] ) );
                              pd->href = strndup ( element->attributes[attribute_position + 3], attribute_length );
                            }

                          else if ( strncmp ( element->attributes[attribute_position],"parse",sizeof ( element->attributes[attribute_position] ) ) == 0 )
                            {
                              int attribute_length = ( strlen ( element->attributes[attribute_position + 3] ) - strlen ( element->attributes[attribute_position + 4] ) );
                              parse_value = strndup ( element->attributes[attribute_position + 3], attribute_length );
                            }
                        }
                      attribute_position = attribute_position + 5;
                      i++;
                    }

                  // Invalid XInclude so throw error
                  if ( pd->href == NULL || parse_value == NULL )
                    {
                      eo_error_set ( obj );
                    }

                  if ( strncmp ( parse_value,"text",sizeof ( parse_value ) ) == 0 )
                    {
                      LOG ( "PLEASE IMPLEMENT _include_text_document" );
                    }
                  else if ( strncmp ( parse_value,"xml",sizeof ( parse_value ) ) == 0 )
                    {
                      LOG ( "PLEASE IMPLEMENT _include_xml_document" );
                    }
                  else
                    {
		      // Invalid XInclude so error
                      eo_error_set ( obj );
                    }
                    
                    pd->level++;
                }
            }
          else
            {
              // Pass back to XML_SAX_BASE
              eo_do_super ( obj, MY_CLASS, start ( element ) );
            }
        }
    }
}

static void
_set_document_locator ( Eo *obj EINA_UNUSED, void *class_data, va_list *list )
{
  Eo *ctx = va_arg ( *list, Eo* );
  xmlSAXLocatorPtr location_pointer = va_arg ( *list, xmlSAXLocatorPtr );
  //Xml_Base_Data *data = eo_data_ref(obj, XML_SAX_BASE);
  XInclude_Data *pd = class_data;
  if ( pd->locators == NULL )
    {
      // TODO do this in the constructor!
      pd->locators = eina_array_new ( 1 );
    }
  eina_array_push ( pd->locators, location_pointer );

  if ( pd->bases == NULL )
    {
      pd->bases = eina_array_new ( 1 );
    }

  const xmlChar *bob = location_pointer->getSystemId(&ctx);
  LOGF("BOBS VALUE: %s", (const char*)bob);
  // Do we have a URI?
  // TODO split this into util.!!
  UriParserStateA state;
  UriUriA location_uri;

  state.uri = &location_uri;
  if ( uriParseUriA ( &state, ( const char* ) location_pointer->getSystemId ) != URI_SUCCESS )
    {
      /* Failure */
      uriFreeUriMembersA ( &location_uri );
      LOG ( "Somethin bad happened parsing URI" );
    }

  eina_array_push ( pd->bases, &location_uri );

  const Eo_Class *current_class = eo_class_get ( obj );
  LOGF ( "Class is : %s %s", eo_class_name_get ( current_class ), __func__ );

  // Pass back to parent
  eo_do_super ( obj, MY_CLASS, set_document_locator ( ctx, location_pointer ) );
}

static void
_end ( Eo *obj EINA_UNUSED, void *class_data, va_list *list )
{
  XInclude_Data *pd = class_data;
  ElementData *element = va_arg ( *list, ElementData* );

  if ( element->URI != NULL && element->localname != NULL )
    {
      if ( strncmp ( element->URI,XINCLUDE_NAMESPACE,sizeof ( XINCLUDE_NAMESPACE ) ) == 0 &&  strncmp ( element->localname,XINCLUDE_TAG,sizeof ( XINCLUDE_TAG ) ) == 0 )
        {
          pd->level--;
        }
    }
  else if ( pd->level == 0 )
    {

      // Pass back to XML_SAX_BASE
      eo_do_super ( obj, MY_CLASS, end ( element ) );
    }
}

static void
_end_document ( Eo *obj EINA_UNUSED, void *class_data, va_list *list )
{
  XInclude_Data *pd = class_data;
  eina_array_pop ( pd->locators );
  pd->depth--;
  if ( pd->depth == 0 )
    {
      // Pass back to XML_SAX_BASE
      eo_do_super ( obj, MY_CLASS, document_end ( va_arg ( *list, ElementData* ) ) );
    }

}

static void
_class_constructor ( Eo_Class *klass )
{
  const Eo_Op_Func_Description func_desc[] =
  {
    EO_OP_FUNC ( XML_SAX_BASE_ID ( XML_SAX_BASE_SUB_ID_SET_DOCUMENT_LOCATOR ), _set_document_locator ),
    EO_OP_FUNC ( XML_SAX_BASE_ID ( XML_SAX_BASE_SUB_ID_DOCUMENT_START ), _start_document ),
    EO_OP_FUNC ( XML_SAX_BASE_ID ( XML_SAX_BASE_SUB_ID_START ), _start ),
    EO_OP_FUNC ( XML_SAX_BASE_ID ( XML_SAX_BASE_SUB_ID_END ), _end ),
    EO_OP_FUNC ( XML_SAX_BASE_ID ( XML_SAX_BASE_SUB_ID_DOCUMENT_END ), _end_document ),
    EO_OP_FUNC_SENTINEL
  };

  eo_class_funcs_set ( klass, func_desc );
}

static const Eo_Op_Description op_desc[] =
{
  EO_OP_DESCRIPTION_SENTINEL
};

static const Eo_Class_Description class_desc =
{
  EO_VERSION,
  "Amin XInclude",
  EO_CLASS_TYPE_REGULAR,
  EO_CLASS_DESCRIPTION_OPS ( &AMIN_XINCLUDE_BASE_ID, op_desc, AMIN_XINCLUDE_SUB_ID_LAST ),
  NULL,
  sizeof ( XInclude_Data ),
  _class_constructor,
  NULL
};

EO_DEFINE_CLASS ( amin_xinclude_class_get, &class_desc, AMIN_ELT, NULL );

