#ifndef SIMPLE_H
#define SIMPLE_H

#include "Eo.h"
#include "amin_filter_interface.h"

extern EAPI Eo_Op AMIN_TYPE_FILTER_BASE_ID;

enum {
     AMIN_TYPE_FILTER_SUB_ID_LAST
};

#define AMIN_TYPE_FILTER_ID(sub_id) (AMIN_TYPE_FILTER_BASE_ID + sub_id)

#define AMIN_TYPE_FILTER_CLASS amin_type_filter_class_get()
const Eo_Class *amin_type_filter_class_get(void);

#endif