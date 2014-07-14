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
