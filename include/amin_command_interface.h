#include <Eo.h>

extern EAPI Eo_Op AMIN_COMMAND_INTERFACE_BASE_ID;

enum {
     AMIN_COMMAND_INTERFACE_SUB_ID_PARSE,
     AMIN_COMMAND_INTERFACE_SUB_ID_LAST
};

#define AMIN_COMMAND_INTERFACE_ID(sub_id) (AMIN_COMMAND_INTERFACE_BASE_ID + sub_id)


/**
 * @def Amin command parsing interface (result)
 * @brief Parse command profile
 * @param[out] ret char pointer to result - value
 */
#define interface_parse_get(result) AMIN_COMMAND_INTERFACE_ID(AMIN_COMMAND_INTERFACE_SUB_ID_PARSE), EO_TYPECHECK(char *, result)

#define AMIN_COMMAND_INTERFACE_CLASS amin_command_interface_class_get()
const Eo_Class *amin_command_interface_class_get(void);
