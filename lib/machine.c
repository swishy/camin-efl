#include <expat.h>
#include "machine.h"
#include "common.h"

int Depth;

void start(void *data, const char *el, const char **attr) {
  int i;

  for (i = 0; i < Depth; i++)
    LOG("  ");

  LOGF("%s", el);

  for (i = 0; attr[i]; i += 2) {
    LOGF(" %s='%s'", attr[i], attr[i + 1]);
  }

  Depth++;
}  /* End of start handler */

void end(void *data, const char *el) {
  Depth--;
}  /* End of end handler */

void parse_content(char *input)
{

  XML_Parser parser = XML_ParserCreate(NULL);
  if (! parser) {
    LOG("Camin could not allocate memory for parser");
    exit(-1);
  }

  XML_SetElementHandler(parser, start, end);

  /* parse the xml */
    if(XML_Parse(parser, input, strlen(input), XML_TRUE) == XML_STATUS_ERROR)
    {
        printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));
    }

    XML_ParserFree(parser);
}