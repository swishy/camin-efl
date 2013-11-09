#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "machine.h"
#include "common.h"

#define STDINBUFFERSIZE 1

static struct option long_options[] =
{
    {"help",  no_argument,       0, 'h'},
    {"version",  no_argument,       0, 'v'},
    {"adminlist",  required_argument, 0, 'a'},
    {"profile",  no_argument, 0, 'p'},
    {"uri",  required_argument, 0, 'u'},
    {NULL, 0, NULL, 0}
};

void print_usage()
{
  LOG("[-h|-help]\n");
  LOG("[-u|-uri] uri://\n"); 
  LOG("[-p|-profile] as <STDIN>\n");
  LOG("[-a|-adminlist] uri://\n");
  LOG("[-v|-version]\n"); 
  LOG("print_usage called\n");
}

void process_adminlist()
{
  LOG("process_adminlist called");
}

void process_profile()
{
  LOG("process_profile called.");
}

void process_input(char *profile)
{
  LOGF("%s", profile);
  
  // Send to machine for processing.
  parse_content(profile);
}

void read_stdin()
{
  unsigned char     profile[STDINBUFFERSIZE];
  FILE                         *instream;
  int                            bytes_read=0;
  int                            buffer_size=0;
  
  buffer_size=sizeof(unsigned char)*STDINBUFFERSIZE;
  
  // Open stdin for reading. 
  instream=fopen("/dev/stdin","r");
  
  // Check it opened.
  if(instream!=NULL){
    
    // Read from stdin until end. 
    while((bytes_read=fread(&profile, buffer_size, 1, instream))==buffer_size){
      fprintf(stdout, "%c", profile[0]);
    }
  }

  // No point carrying on here ABORT ABORT!!!
  else{
    LOG_ERROR("Unable to open stdin. exiting Amin.", NULL);
  exit(1);
  }
  
  LOGF("Bytes read in [ %i ]", bytes_read);
  
  // pass to stdin handler
  process_input(profile); 
}


int main(int argc, char* argv[])
{
  LOG("Welcome to Amin version 1.0");
  LOG("Today brought to you by caffiene and MoonAlice(tm)...");
  int c;
  
  while (1)
  {
    /* getopt_long stores the option index here. */
    int option_index = 0;
    
    c = getopt_long (argc, argv, "hv:a:pu:",
		     long_options, &option_index);
    
    /* Detect the end of the options. */
    if (c == -1)
      break;
    
    switch (c)
    {
      case 0:
	/* If this option set a flag, do nothing else now. */
	if (long_options[option_index].flag != 0)
	  break;
	LOGF("option %s", long_options[option_index].name);
	if (optarg)
	  LOGF(" with arg %s", optarg);
	LOG("\n");
	break;
	
      case 'h':
	LOG("option -h\n");
	print_usage();
	break;
	
      case 'v':
	LOG("option -v\n");
	break;
	
      case 'a':
	LOGF("option -a with value `%s'", optarg);
	break;
	
      case 'p':
	LOG("option -p\n");
	
	// Read from stdin.
	read_stdin();
	break;
	
      case 'u':
	LOGF("option -u with value `%s'\n", optarg);
	break;
	
      default:
	print_usage();
    }
  }
  
  exit (0);
}
