#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <libxml/SAX.h>
#include "Eo.h"
#include "common.h"
#include "amin.h"
#include "xml_sax_base.h"
#include "elt.h"
#include "xinclude.h"
#include "machine_spec.h"
#include "document.h"
#include "amin_machine_dispatcher.h"
#include "uriparser/Uri.h"

EAPI Eo_Op AMIN_BASE_ID = 0;

typedef struct
{
   char input;
} Private_Data;


#define MY_CLASS AMIN

static void
_parse(Eo *obj, void *class_data, va_list *list)
{

  // Document is only thing passed to us so pop if off the list.
  const char *profile = va_arg(*list, const char *);

  // TODO wrap into function.
  // Check if the profile is a URI
  UriParserStateA state;
  UriUriA machine_spec_uri;
  state.uri = &machine_spec_uri;
  Eo *machine_spec;

  if ( uriParseUriA ( &state, profile ) != URI_SUCCESS )
    {
      /* Failure */
      uriFreeUriMembersA ( &machine_spec_uri );
      machine_spec = eo_add(AMIN_MACHINE_SPEC, NULL);
    } else {
      machine_spec = eo_add(AMIN_MACHINE_SPEC, NULL); // TODO ADD set_uri function to class.
    }

  Eo *xinclude_filter = eo_add_custom(AMIN_XINCLUDE, NULL, set_handler_constructor(machine_spec));

  Eo *xml_base = eo_add_custom(XML_SAX_BASE, NULL, set_handler_constructor(machine_spec));

  const Eo_Class *xml_base_class = eo_class_get(xml_base);
  LOGF("obj-type:'%s'\n", eo_class_name_get(xml_base_class));

  LOG("Kicking parser into action....");

  // TODO Move to struct once declared at completeion of machine_spec.
  int foo;

  eo_do(xml_base, parse_string(profile, &foo));

  /**LOG("Loading AMIN machine spec");
  Eo *amin_machine_spec = eo_add_custom(AMIN_MACHINE_SPEC, NULL, filter_constructor(machine_parser, obj));
  const Eo_Class *machine_class = eo_class_get(amin_machine_spec);
  LOGF("obj-type:'%s'\n", eo_class_name_get(machine_class));
*/
  /**HandlerData handlerData;
  handlerData.current_filter = amin_machine_spec;
  handlerData.saxHandler = machine_parser;

  LOG("start parsing");
  if (xmlSAXUserParseMemory(&machine_parser, &handlerData, profile, strlen(profile)) < 0 ) {
    LOG("Issue parsing XML document");
  };
  */

}

static void
_class_constructor(Eo_Class *klass)
{
  const Eo_Op_Func_Description func_desc[] = {
    EO_OP_FUNC(AMIN_ID(AMIN_SUB_ID_PARSE), _parse),
    EO_OP_FUNC_SENTINEL
  };

  eo_class_funcs_set(klass, func_desc);
}

static const Eo_Op_Description op_desc[] = {
     EO_OP_DESCRIPTION(AMIN_SUB_ID_PARSE, "Starts processing an Amin document."),
     EO_OP_DESCRIPTION_SENTINEL
};

static const Eo_Class_Description class_desc = {
     EO_VERSION,
     "Amin",
     EO_CLASS_TYPE_REGULAR,
     EO_CLASS_DESCRIPTION_OPS(&AMIN_BASE_ID, op_desc, AMIN_SUB_ID_LAST),
     NULL,
     sizeof(Private_Data),
     _class_constructor,
     NULL
};

EO_DEFINE_CLASS(amin_class_get, &class_desc, EO_BASE_CLASS, NULL);
