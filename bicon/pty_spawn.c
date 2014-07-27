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
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <signal.h>
#include "pty_spawn.h"

static pid_t
_fork (int *master_fd, int *slave_fd)
{
  pid_t pid;
  struct termios ts = {0};
  struct winsize win = {0};
  if (-1 == tcgetattr (1, &ts))
    fprintf (stderr, "bicon: tcgetaddr() failed.\n");
  if (-1 == ioctl(0, TIOCGWINSZ, (char *)&win))
    fprintf (stderr, "bicon: ioctl(0, TIOCGWINSZ) failed.\n");
  pid = forkpty (master_fd, NULL, &ts, &win);
  if (pid != -1)
    {
      if (pid == 0)
	setsid ();
      return pid;
    }
  if (openpty (master_fd, slave_fd, NULL, NULL, NULL) == -1)
    return -1;
  pid = fork ();
  if (pid == -1)
    return -1;
  if (pid == 0)
    {
      setsid ();
      close (*master_fd);
      dup2 (*slave_fd, 0);
      dup2 (*slave_fd, 1);
      dup2 (*slave_fd, 2);
      if (*slave_fd > 2)
	close (*slave_fd);
    }
  return pid;
}

static int
_copy (
  int master_fd,
  reader master_read,
  reader stdin_read,
  pid_t pid)
{
  fd_set rfds;
  char buf[BUFLEN], *buf_p;
  int count, c, ret;
  struct timeval timeout, *ptimeout = NULL;
  struct stat st;
  ino_t cwd = -1;
  char _proc_child_cwd[32];
  snprintf (_proc_child_cwd, sizeof (_proc_child_cwd), "/proc/%u/cwd", pid);
  for (;;)
    {

      FD_ZERO (&rfds);
      FD_SET (master_fd, &rfds);
      FD_SET (0, &rfds);
      ret = select (master_fd + 1, &rfds, NULL, NULL, ptimeout);
      if (-1 == ret)
      {
	if (errno == EINTR)
	  continue;
	return -1;
      }
      if (0 == ret)
      {
        /* Timeout. */

	/* Check whether child cwd changed and follow.  This is useful
	 * with older versions of gnome-terminal that used the process
	 * cwd to for window title...  Might be too slow, who knows... */
	{
	  if (-1 != stat (_proc_child_cwd, &st) && st.st_ino != cwd)
	  {
	    int len;
	    len = readlink (_proc_child_cwd, buf, sizeof (buf));
	    if (len != -1)
	    {
	      buf[len] = '\0';
	      (void) chdir (buf);
	    }
	    cwd = st.st_ino;
	  }
	}

        /* Remove timeout now. */
        ptimeout = NULL;
        continue;
      }
      if (FD_ISSET (master_fd, &rfds))
	{
	  count = master_read (master_fd, buf, sizeof (buf));
	  if (count == -1)
	    return -1;
	  /* TODO while (errno == EINTR)... */ write (1, buf, count);
	}
      if (FD_ISSET (0, &rfds))
	{
	  count = stdin_read (0, buf, sizeof (buf));
	  if (count == -1)
	    return -1;
	  for (buf_p = buf, c = 0; count > 0; buf_p += c, count -= c)
	    c = write (master_fd, buf_p, count);
	}
      /* Set timeout, such that if things are steady, we update cwd
       * next iteration. */
      timeout.tv_sec = 0;
      timeout.tv_usec = 50000; /* 50ms */
      ptimeout = &timeout;
    }
}

static int master_fd, slave_fd;
static pid_t pid;

static void
resize(int dummy)
{
  struct	winsize win;

  /* transmit window change information to the child */
  (void) ioctl(0, TIOCGWINSZ, (char *)&win);
  (void) ioctl(master_fd, TIOCSWINSZ, (char *)&win);

  kill(pid, SIGWINCH);
}

int
bicon_spawn (
  const char *file,
  char *const args[],
  reader master_read,
  reader stdin_read)
{
  struct termios ts, newts;
  struct sigaction sa;

  pid = _fork (&master_fd, &slave_fd);
  if (pid == -1)
    return 126;
  if (pid == 0)
    {
      execvp (file, args);
      fprintf (stderr, "bicon: failed running %s.\n", file);
      exit (1);
    }

  sigemptyset (&sa.sa_mask);
  sa.sa_flags = 0;
  sa.sa_handler = resize;
  if (sigaction(SIGWINCH, &sa, NULL) == -1)
    fprintf (stderr, "bicon: sigaction() failed.\n");

  tcgetattr (1, &ts);
  newts = ts;
  cfmakeraw (&newts);
  tcsetattr (1, TCSAFLUSH, &newts);
  _copy (master_fd, master_read, stdin_read, pid);
  tcsetattr (1, TCSAFLUSH, &ts);
  return 0;
  /* XXX we better somehow return the return value of the forked
   * child, but how?
   */
}
