#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>

#define NAME "bicon.so"

#define default_lang "en_US"
#define utf8_on_str "\e%G"
#define utf8_off_str "\e%@"


#define hook_function(name, lib, oncecode, precode) \
void* \
name() \
{ \
  static void* (*p) () = NULL; \
  const char *errmsg = "No error!"; \
  void *plib; \
 \
  /* grab the original hook. */ \
  if (!p) \
    { \
      plib = dlopen (lib, RTLD_LAZY); \
      if (plib == NULL) \
	{ \
	  errmsg = dlerror (); \
	  goto err_dlopen; \
	} \
      p = dlsym (plib, #name); \
      if (p == NULL) \
	{ \
	  errmsg = dlerror (); \
	  goto err_dlsym; \
	} \
      /* do the oncecode work. */ \
      oncecode; \
    } \
 \
  /* do the precode work. */ \
  precode; \
 \
  /* call the original function. */ \
  return (*p) (); \
 \
err_dlsym: \
  dlclose (lib); \
 \
err_dlopen: \
  fprintf (stderr, NAME ": error: %s\n", errmsg); \
  exit (1); \
}

#define turn_utf8_off \
  do { \
    char *term = getenv ("TERM"); \
    if (term == NULL) \
      term = ""; \
 \
    putenv ("LANG=" default_lang); \
    if (!strcmp (term, "linux")) \
      { \
	write (1, utf8_off_str, sizeof utf8_off_str); \
      } \
  } while (0)

/* turn utf-8 off for following functions. */
hook_function (SLtt_init_video, "libslang.so", turn_utf8_off,);
hook_function (initscr, "libcurses.so", turn_utf8_off,);

void
init (
  void)
{
  return;
}
