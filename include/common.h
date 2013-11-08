// Logging macros.
#define UVERR(err, msg) fprintf(stderr, "%s: %s\n", msg, uv_err_name(err))
#define LOG_ERROR(fmt, params...) fprintf(stderr, fmt "\n", params);;
#define LOG(msg) puts(msg);
#define LOGF(fmt, params...) printf(fmt "\n", params);