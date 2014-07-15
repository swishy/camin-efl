#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <libxml/SAX2.h>
#include "Eo.h"

// Logging macros.
#define UVERR(err, msg) fprintf(stderr, "%s: %s\n", msg, uv_err_name(err))
#define LOG_ERROR(fmt, params...) fprintf(stderr, fmt "\n", params);;
#define LOG(msg) puts(msg);
#define LOGF(fmt, params...) printf(fmt "\n", params);

// Spec struct
typedef struct Spec
{
   /* etc. */
} Spec ;

// TODO Not happy about this....
typedef struct
{
    Eo *content_handler;
    Eo *document_handler;
    Eo *handler;
    Eo *result;
}
Xml_Base_Data;

typedef struct
{
    const char *element;
    const char *name_space;
    const char *name;
    const char *position;
    const char *download;
    const char *version;
    const char *module;
} Filter_Data;


typedef struct
{
    const char *name;
    Filter_Data *data;
} Filter;

typedef struct
{
    const char *machine_name;
    char *generator;
    char *log;
    char **filter_params;
    Eina_Hash *filters;
} Machine_Spec_Document;
