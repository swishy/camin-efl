#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <unistd.h>
#include <Ecore.h>
#include <Ecore_Getopt.h>
#include "amin.h"
#include "common.h"
#include "elt.h"

struct context
{
  Ecore_Fd_Handler *handler;
};

void read_stdin();

static unsigned char _adminlist_callback(const Ecore_Getopt *parser, const Ecore_Getopt_Desc *desc, const char *str, void *data, Ecore_Getopt_Value *storage);

static unsigned char _uri_callback(const Ecore_Getopt *parser, const Ecore_Getopt_Desc *desc, const char *str, void *data, Ecore_Getopt_Value *storage);

static const Ecore_Getopt optdesc = {
  "CAmin",
  NULL,
  "0.0",
  "(C) 2014 ProjectAmin.org",
  "",
  "Amin implementation in C",
  0,
  {
    ECORE_GETOPT_CALLBACK_ARGS('a', "adminlist", "[-a|-adminlist] uri://", "STRING", _adminlist_callback, NULL),
    ECORE_GETOPT_CALLBACK_ARGS('u', "uri", "[-u|-uri] uri://", "STRING", _uri_callback, NULL),
    ECORE_GETOPT_STORE_TRUE('p', "profile", "[-p|-profile] as <STDIN>"),
    ECORE_GETOPT_HELP('h', "help"),
    ECORE_GETOPT_SENTINEL
  }
};

static unsigned char
_adminlist_callback(const Ecore_Getopt *parser, const Ecore_Getopt_Desc *desc, const char *str, void *data, Ecore_Getopt_Value *storage)
{
   printf("Adminlist Callback received %s\n", str);
   
   ecore_main_loop_quit();

   return ECORE_CALLBACK_CANCEL;
}

static unsigned char
_uri_callback(const Ecore_Getopt *parser, const Ecore_Getopt_Desc *desc, const char *str, void *data, Ecore_Getopt_Value *storage)
{
   printf("URI Callback received %s\n", str);
   
   ecore_main_loop_quit();

   return ECORE_CALLBACK_CANCEL;
}

static Eina_Bool _stdin_handler_cb(void *data, Ecore_Fd_Handler *handler)
{
  
  // Setup local vars.
  struct context *ctxt = data;
  char buf[1024];
  size_t nbytes;
  int fd;
  
  // Get the currently active fd and bail out on error.
  if (ecore_main_fd_handler_active_get(handler, ECORE_FD_ERROR))
  {
    LOG("An error has occured accessing STDIN, exiting Amin.");
    ecore_main_loop_quit();
    ctxt->handler = NULL;
    return ECORE_CALLBACK_CANCEL;
  }
  
  // Read till no futher data.
  fd = ecore_main_fd_handler_fd_get(handler);
  nbytes = read(fd, buf, sizeof(buf));
  if (nbytes == 0)
  {
    LOG("STDIN contained no data exiting Amin.");
    ecore_main_loop_quit();
    ctxt->handler = NULL;
    return ECORE_CALLBACK_CANCEL;
  }
  
  LOGF("Read %zd bytes from input: \"%s\"\n", nbytes, buf);
  
  // We want to remove the handler as we have process data relevant.
  ctxt->handler = NULL;
  
  LOG("Creating Amin Instance");
  Eo *amin = eo_add(AMIN, NULL);
  
  const Eo_Class *klass = eo_class_get(amin);
  printf("obj-type:'%s'\n", eo_class_name_get(klass));
  
  eo_do(amin, parse(buf));
  
  // All done jumping out....
  ecore_main_loop_quit();
  
  // Signal no further events to this callback.
  return ECORE_CALLBACK_CANCEL;
}

void read_stdin()
{
  // Create struct to maintain pointer to handler.
  struct context ctxt = {0};
  
  // Setup handler and callback.
  ctxt.handler = ecore_main_fd_handler_add(STDIN_FILENO,
					   ECORE_FD_READ | ECORE_FD_ERROR,
					   _stdin_handler_cb,
					   &ctxt, NULL, NULL);
}


int main(int argc, char* argv[])
{
  LOG("Welcome to Amin version 1.0");
  LOG("Today brought to you by caffiene and MoonAlice(tm)...");
  
  // Define vars to contain commandline options.
  char *adminlist;
  char *uri;
  Eina_Bool profile = EINA_FALSE;
  Eina_Bool quit = EINA_FALSE;
  
  Ecore_Getopt_Value values[] = {
	ECORE_GETOPT_VALUE_STR(adminlist),
	ECORE_GETOPT_VALUE_STR(uri),
	ECORE_GETOPT_VALUE_BOOL(profile),
	ECORE_GETOPT_VALUE_BOOL(quit),
	ECORE_GETOPT_VALUE_NONE
  };

  if (!ecore_init())
  {
    printf("ERROR: Cannot init Eo / Ecore!\n");
    return -1;
  }
  
  // Parse commandline arguments.
  if (ecore_getopt_parse(&optdesc, values, argc, argv) < 0)
  {
    LOG("Failed to parse options passed to Amin");
    return 1;
  }
  
  // We are exepcting something from stdin so lets read it!
  if (profile)
  {
    read_stdin();
  }
  
  ecore_main_loop_begin();
  
  ecore_shutdown();
  
  return 0;
}