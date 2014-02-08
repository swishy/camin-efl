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
   xmlSAXHandler parser;
   char input;
   Eina_List *attrs;
   Eina_List *filters;
   char command;
   char param;
   char target;
   char flag;
   char name;
   char element;
   char doctype;
   char docname;
   char text;
   Eo *filter;
} Private_Data;

#define MY_CLASS AMIN_MACHINE_SPEC

static void 
_document_start(Eo *obj, void *class_data, va_list *list) {
  
  FILE *machine_spec;
  long size;
  char *machine_spec_buffer;

  Private_Data *data = eo_data_ref(obj, MY_CLASS);
  
  //pd->filters = NULL;
  
  LOGF("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
  
  LOG("MachineSpec start....");

  
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
  
  LOGF("%s", machine_spec_buffer);
  
  Eo *machine_spec_document = eo_add(AMIN_MACHINE_SPEC_DOCUMENT, NULL);
  
  Eo *xinclude_filter = eo_add_custom(AMIN_XINCLUDE, NULL, set_handler_constructor(machine_spec_document));
  
  Eo *xml_base = eo_add_custom(XML_SAX_BASE, NULL, set_handler_constructor(xinclude_filter));
  
  LOG("Kicking parser into action in machine_spec....");
  
  // TODO implement out param on xml_sax_base tp receive the result of parsing....
  Machine_Spec_Document *spec;
  eo_do(xinclude_filter, parse_string(machine_spec_buffer, &spec));
  LOG("machine spec oarse string comepled.....");
  LOGF("We have a doc %s", spec->machine_name);
  
}

static void 
_start(Eo *obj, void *class_data, va_list *list) {
  int i;
  
  LOG("AMIN_MACHINE_SPEC _start");
  
  void *data = va_arg(*list, void*);
  const char *element = va_arg(*list, const char*);
  const char **attributes = va_arg(*list, const char**);
  
  size_t module_length = (strlen(element) + strlen(attributes[1]));
  
  char *module = malloc(sizeof(char) * module_length);
  
  //eina_str_join(module, module_length, "", element, attributes[1]);
  
  
  
  LOGF("Element: %s", element);
  LOGF("Attribute: %s", attributes[1]);
  
  LOGF("Module: %s", module);
  
  
  /** PERL FOO 
    my ($self, $element) = @_;
	my %attrs = %{$element->{Attributes}};
    my $module = $element->{Prefix} . "::" . $element->{'LocalName'};
    if ($attrs{'{}name'}->{'Value'}) {
        $module .= "::" . $attrs{'{}name'}->{'Value'};
    }
    $self->{'filters'}->{$module} = "";
  
  eina_str_join_len(prologue, 106, ' ', part1, strlen(part1), part2, strlen(part2));*/
  
} 

static void
_char(Eo *obj, void *class_data, va_list *list)
{
  /**void *data = va_arg(*list, void*);
  const XML_Char *string = va_arg(*list, const XML_Char*);
  int length = va_arg(*list, int);

    // ref important bytes passed in if they arent whitespace.
    if (length > 0 && !isspace(*string))
    {
      LOGF("char data in tag: %.*s", length, string);
    }    */
}

static void
_class_constructor(Eo_Class *klass)
{
  const Eo_Op_Func_Description func_desc[] = {
    EO_OP_FUNC(XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_DOCUMENT_START), _document_start),
    EO_OP_FUNC(XML_SAX_BASE_ID(XML_SAX_BASE_SUB_ID_START), _start),
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