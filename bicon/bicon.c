#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pty_spawn.h"
#include "bicon_read.h"

char **args;
const char SH[]="/bin/sh";

int
main (int argc, char **argv)
{
  int i;
  args=malloc(argc*sizeof(char *));
  if (argc==1){
    char *sh=getenv("SHELL");
    args[0]=sh?sh:SH;
    args[1]=NULL;
  }else{
    for (i = 1; i < argc; i++)
      args[i-1]=argv[i];
    args[argc-1]=NULL;
  }
  initbread ();
  spawn (args[0], args, bicon_read, read);
}
