/*
Copyright (c) 2001, 2002, 2003 Python Software Foundation; All Rights Reserved
Copyright (c) Muhammad Alkarouri

This code is a direct translation of the pty.spawn function and its 
dependencies, as included in Python 2.2.3, to the C language.

This code is governed by the same license as pty.spawn,
namely the PSF License Agreement For Python 2.2.3
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <pty.h>
#include <sys/types.h>
#include <sys/select.h>
#include "pty_spawn.h"

static pid_t
_fork (
  int *master_fd)
{
  pid_t pid;
  int slave_fd;
  pid = forkpty (master_fd, NULL, NULL, NULL);
  if (pid != -1)
    {
      if (pid == 0)
	setsid ();
      return pid;
    }
  if (openpty (master_fd, &slave_fd, NULL, NULL, NULL) == -1)
    return -1;
  pid = fork ();
  if (pid == -1)
    return -1;
  if (pid == 0)
    {
      setsid ();
      close (*master_fd);
      dup2 (slave_fd, 0);
      dup2 (slave_fd, 1);
      dup2 (slave_fd, 2);
      if (slave_fd > 2)
	close (slave_fd);
    }
  return pid;
}

static int
_copy (
  int master_fd,
  reader master_read,
  reader stdin_read)
{
  fd_set rfds;
  char buf[BUFLEN], *buf_p;
  int count, c;
  for (;;)
    {
      FD_ZERO (&rfds);
      FD_SET (master_fd, &rfds);
      FD_SET (0, &rfds);
      if (select (master_fd + 1, &rfds, NULL, NULL, NULL) == -1)
	return -1;
      if (FD_ISSET (master_fd, &rfds))
	{
	  count = master_read (master_fd, buf, sizeof (buf));
	  if (count == -1)
	    return -1;
	  write (1, buf, count);
	}
      if (FD_ISSET (0, &rfds))
	{
	  count = stdin_read (0, buf, sizeof (buf));
	  if (count == -1)
	    return -1;
	  for (buf_p = buf, c = 0; count > 0; buf_p += c, count -= c)
	    c = write (master_fd, buf_p, count);
	}
    }
}

int
bicon_spawn (
  const char *file,
  char *const args[],
  reader master_read,
  reader stdin_read)
{
  pid_t pid;
  int master_fd;
  struct termios ts, newts;
  pid = _fork (&master_fd);
  if (pid == -1)
    return 126;
  if (pid == 0) {
    execvp (file, args);
    fprintf(stderr, "bicon: failed running %s\n", file);
    exit(1);
  }
  tcgetattr (1, &ts);
  newts = ts;
  cfmakeraw (&newts);
  tcsetattr (1, TCSAFLUSH, &newts);
  _copy (master_fd, master_read, stdin_read);
  tcsetattr (1, TCSAFLUSH, &ts);
  return 0;
  /* XXX we better somehow return the return value of the forked
   * child, but how?
   */
}
