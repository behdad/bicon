#ifndef __PTY_SPAWN_H
#define __PTY_SPAWN_H
#include <unistd.h>
#include <stdio.h>

#define BUFLEN BUFSIZ

typedef ssize_t (
  *reader) (
  int fd,
  void *buf,
  size_t count);

int spawn (
  const char *file,
  char *const args[],
  reader master_read,
  reader stdin_read);

#endif /*__PTY_SPAWN_H*/
