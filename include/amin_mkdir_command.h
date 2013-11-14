#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <Eo.h>
#include "amin_command_interface.h"

extern EAPI Eo_Op AMIN_MKDIR_COMMAND_BASE_ID;

enum {
     AMIN_MKDIR_COMMAND_SUB_ID_LAST
};

#define AMIN_MKDIR_COMMAND_ID(sub_id) (AMIN_MKDIR_COMMAND_BASE_ID + sub_id)

#define AMIN_MKDIR_COMMAND_CLASS mkdir_command_class_get()
const Eo_Class *mkdir_command_class_get(void);
