#ifndef _AMIN_EO_H_
#define _AMIN_EO_H_

#ifndef _AMIN_EO_CLASS_TYPE
#define _AMIN_EO_CLASS_TYPE

typedef Eo Amin;

#endif

#ifndef _AMIN_EO_TYPES
#define _AMIN_EO_TYPES


#endif
#define AMIN_CLASS amin_class_get()

EAPI const Eo_Class *amin_class_get(void) EINA_CONST;

EOAPI Eo * amin_parse(char *profile);


#endif
