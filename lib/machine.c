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

  for (;;) {
    int done;

    done = feof(input);

    if (! XML_Parse(parser, input, sizeof(input), done)) {
      LOGF("Parse error at line %d:\n%s\n",
	      XML_GetCurrentLineNumber(parser),
	      XML_ErrorString(XML_GetErrorCode(parser)));
      
      // TODO handle and return profile with error elements.
      exit(-1);
    }

    if (done)
      break;
  }
}