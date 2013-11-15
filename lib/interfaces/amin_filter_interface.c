#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <Eo.h>
#include "amin_filter_interface.h"

EAPI Eo_Op AMIN_FILTER_INTERFACE_BASE_ID = 0;

#define MY_CLASS AMIN_FILTER_INTERFACE_CLASS

static const Eo_Op_Description op_desc[] = {
     EO_OP_DESCRIPTION(AMIN_FILTER_INTERFACE_SUB_ID_START, "Expat start element callback"),
     EO_OP_DESCRIPTION(AMIN_FILTER_INTERFACE_SUB_ID_END, "Expat end element callback"),
     EO_OP_DESCRIPTION_SENTINEL
};

static const Eo_Class_Description class_desc = {
     EO_VERSION,
     "Amin Filter Interface",
     EO_CLASS_TYPE_INTERFACE,
     EO_CLASS_DESCRIPTION_OPS(&AMIN_FILTER_INTERFACE_BASE_ID, op_desc, AMIN_FILTER_INTERFACE_SUB_ID_LAST),
     NULL,
     0,
     NULL,
     NULL
};

EO_DEFINE_CLASS(amin_filter_interface_class_get, &class_desc, NULL, NULL)