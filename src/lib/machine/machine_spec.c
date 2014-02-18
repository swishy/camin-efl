#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <libxml/SAX2.h>
#include "Eo.h"
#include "common.h"
#include "amin.h"
#include "xinclude.h"
#include "xml_sax_base.h"
#include "elt.h"
#include "machine_spec.h"
#include "document.h"

int DEPTH;

EAPI Eo_Op AMIN_MACHINE_SPEC_BASE_ID = 0;

typedef struct
{
   Eina_List *filters;
   Machine_Spec_Document spec;
} Private_Data;

#define MY_CLASS AMIN_MACHINE_SPEC

static void
_filter_entry_free_cb(void *data)
{
  free(data);
}

static void 
_document_start(Eo *obj, void *class_data, va_list *list) {
  
  FILE *machine_spec;
  long size;
  char *machine_spec_buffer;

  Private_Data *pd = class_data;
  
  LOGF("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
  
  // Get size of machine_spec and read in.
  // TODO implement error handling
  if ((machine_spec = fopen("/etc/amin/machine_spec.xml", "rb")))
  {
    fseek(machine_spec, 0, SEEK_END);
    size = ftell(machine_spec);
    fseek(machine_spec, 0, SEEK_SET);
  }
  
  if ((machine_spec_buffer = malloc(size)))
  {
    fread(machine_spec_buffer, 1, size, machine_spec);
  }
  
  // Set up filter chain.
  Eo *machine_spec_document = eo_add(AMIN_MACHINE_SPEC_DOCUMENT, NULL);
  
  Eo *xinclude_filter = eo_add_custom(AMIN_XINCLUDE, NULL, set_handler_constructor(machine_spec_document));
  
  Eo *xml_base = eo_add_custom(XML_SAX_BASE, NULL, set_handler_constructor(xinclude_filter));
  
  LOG("Kicking parser into action in machine_spec....");

  // Start Machine Spec parsing and assign results to local var.
  eo_do(xml_base, parse_string(machine_spec_buffer, &pd->spec));
}

static void 
_start(Eo *obj, void *class_data, va_list *list) {
  LOGF ( "Class is : %s %s", eo_class_name_get ( MY_CLASS ), __func__ );

  LOG("AMIN_MACHINE_SPEC _start");
  
  LOGF("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
  
  Private_Data *pd = class_data;
  ElementData *element = va_arg ( *list, ElementData* );
  
  LOGF("Number of attributes in machine spec start: %i", element->nb_attributes);
  
  if ( element->nb_attributes > 0 )
        {
          int i = 0;
          int attribute_position = 0;

          // Get values from attributes
          while ( i < element->nb_attributes )
            {
              if ( element->attributes[attribute_position] != NULL )
                {
		  LOGF("Attribute is %s", element->attributes[attribute_position]);
                  if ( strncmp ( element->attributes[attribute_position],"name",sizeof ( element->attributes[attribute_position] ) ) == 0 )
                    {
                      int attribute_length = ( strlen ( element->attributes[attribute_position + 3] ) - strlen ( element->attributes[attribute_position + 4] ) );
                      LOGF("Attribute liength: %i", attribute_length);
		      
		      char *module_name = strndup ( element->attributes[attribute_position + 3], attribute_length );
		      LOGF("Module name: %s", module_name);
		      eina_list_append(pd->filters, module_name);
                    }
                }
              attribute_position = attribute_position + 5;
              i++;
            }
        }
}

static void 
_end_document(Eo *obj, void *class_data, va_list *list) {
  LOGF ( "Class is : %s %s", eo_class_name_get ( MY_CLASS ), __func__ );
  Private_Data *pd = class_data;
  ElementData *element = va_arg ( *list, ElementData* );
  
  LOGF("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
  
  LOGF("Module count: %lu", sizeof(pd->filters));
  
  Eina_List *l_itr;
  char *module;
  
  EINA_LIST_FOREACH(pd->filters, l_itr, module)
    LOGF("Current module is %s", module);

}

static void
_class_constructor(Eo_Class *klass)
{
  const Eo_Op_Func_Description func_desc[] = {
    EO_OP_FUNC(XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_DOCUMENT_START), _document_start),
    EO_OP_FUNC(XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_START), _start),
    EO_OP_FUNC(XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_DOCUMENT_END), _end_document),
    EO_OP_FUNC_SENTINEL
  };
  
  eo_class_funcs_set(klass, func_desc);
}

static const Eo_Op_Description op_desc[] = {
     EO_OP_DESCRIPTION_SENTINEL
};

static const Eo_Class_Description class_desc = {
     EO_VERSION,
     "Amin Machine Spec",
     EO_CLASS_TYPE_REGULAR,
     EO_CLASS_DESCRIPTION_OPS(&AMIN_MACHINE_SPEC_BASE_ID, op_desc, AMIN_MACHINE_SPEC_SUB_ID_LAST),
     NULL,
     sizeof(Private_Data),
     _class_constructor,
     NULL
};

EO_DEFINE_CLASS(amin_machine_spec_class_get, &class_desc, AMIN_ELT, EO_BASE_CLASS, NULL);