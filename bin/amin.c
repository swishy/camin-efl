#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

static struct option long_options[] =
{
    {"help",  no_argument,       0, 'h'},
    {"version",  no_argument,       0, 'v'},
    {"adminlist",  required_argument, 0, 'a'},
    {"profile",  required_argument, 0, 'p'},
    {"uri",  required_argument, 0, 'u'},
    {NULL, 0, NULL, 0}
};

void print_usage()
{
  printf("[-h|-help]\n");
  printf("[-u|-uri] uri://\n"); 
  printf("[-p|-profile] as <STDIN>\n");
  printf("[-a|-adminlist] uri://\n");
  printf("[-v|-version]\n"); 
  printf("print_usage called\n");
}

void process_adminlist()
{
  printf("process_adminlist called");
}

void process_profile()
{
  printf("process_profile called.");
}


int main(int argc, char* argv[])
{
      printf("Welcome to Amin version 1.0");
      printf("Today brought to you by caffiene and MoonAlice(tm)...");
       int c;
     
       while (1)
         {
           /* getopt_long stores the option index here. */
           int option_index = 0;
     
           c = getopt_long (argc, argv, "hv:a:p:u:",
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
               printf ("option %s", long_options[option_index].name);
               if (optarg)
                 printf (" with arg %s", optarg);
               printf ("\n");
               break;
     
             case 'h':
               puts ("option -h\n");
	       print_usage();
               break;
     
             case 'v':
               puts ("option -v\n");
               break;
     
             case 'a':
               printf ("option -a with value `%s'\n", optarg);
               break;
     
             case 'p':
               printf ("option -p with value `%s'\n", optarg);
               break;
	       
	     case 'u':
               printf ("option -u with value `%s'\n", optarg);
               break;
     
             default:
	       print_usage();
             }
         }
         
         // Currently exit till we have something happening....
     
       exit (0);
}
