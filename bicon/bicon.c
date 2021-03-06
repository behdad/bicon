#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <bjoining.h>
#include "pty_spawn.h"
#include "bicon_read.h"

char **args;
const char SH[] = "/bin/sh";

int
main (
  int argc,
  char **argv)
{
  int i;
  args = malloc (argc * sizeof (char *));
  if (argc == 1)
    {
      char *sh = getenv ("SHELL");
      args[0] = sh ? sh : (char *) SH;
      args[1] = NULL;
    }
  else
    {
      int args_start;
      if (strcmp(argv[1], "--reshape-only") == 0) {
        bicon_options = B_LOGICAL_OUTPUT_LOG2CUNI | B_NO_LA_LIGATURE;
        args_start = 2;
      } else {
        args_start = 1;
      }
      for (i = args_start; i < argc; i++)
        args[i - args_start] = argv[i];
      args[argc - args_start] = NULL;
    }
  if (!bicon_read_init ())
    {
      fprintf (stderr, "Error: FriBidi is not compiled with UTF-8 support\n");
      exit (1);
    }
  return bicon_spawn (args[0], args, bicon_read, read);
}
