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
#include <string.h>
#include <unistd.h>
#include <errno.h>
#ifdef __APPLE__
    #include <util.h>
    #pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
    #pragma GCC diagnostic ignored "-Wreturn-type"
#else
    #include <pty.h>
#endif
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include "pty_spawn.h"

static volatile int done;

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

static inline int
_xread (
  reader read,
  int fd,
  void *buf,
  size_t count)
{
  int ret;
  do {
    ret = read (fd, buf, count);
  } while (ret == -1 && errno == EINTR && !done);
  return ret;
}

static inline void
_xwrite (
  int fd,
  char *buf,
  size_t count)
{
  int ret;
  for (; count; buf += ret, count -= ret)
  {
    do {
      ret = write (fd, buf, count);
    } while (ret == -1 && errno == EINTR && !done);
    if (ret == -1)
    {
      fprintf (stderr, "bicon: write() failed.\n");
      exit (1);
    }
  }
}

static void
_copy (
  int master_fd,
  reader master_read,
  reader stdin_read,
  pid_t pid)
{
  fd_set rfds;
  char buf[BUFLEN];
  int count, ret;
  struct timeval timeout, *ptimeout = NULL;
  struct stat st;
  ino_t cwd = -1;
  char _proc_child_cwd[32];
  snprintf (_proc_child_cwd, sizeof (_proc_child_cwd), "/proc/%u/cwd", pid);
  for (;!done;)
    {

      FD_ZERO (&rfds);
      FD_SET (master_fd, &rfds);
      FD_SET (0, &rfds);
      ret = select (master_fd + 1, &rfds, NULL, NULL, ptimeout);
      if (-1 == ret)
      {
	if (errno == EINTR && !done)
	  continue;
	return;
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
	  count = _xread (master_read, master_fd, buf, sizeof (buf));
	  if (count == -1)
	    return;
	  _xwrite (1, buf, count);
	}
      if (FD_ISSET (0, &rfds))
	{
	  count = _xread (stdin_read, 0, buf, sizeof (buf));
	  if (count == -1)
	    return;
	  _xwrite (master_fd, buf, count);
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

static void
child(int dummy)
{
  done = 1;
  fprintf (stderr, "done\n");
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
  int status, ret;

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
  sigemptyset (&sa.sa_mask);
  sa.sa_flags = 0;
  sa.sa_handler = child;
  if (sigaction(SIGCHLD, &sa, NULL) == -1)
    fprintf (stderr, "bicon: sigaction() failed.\n");

  tcgetattr (1, &ts);
  newts = ts;
  cfmakeraw (&newts);
  tcsetattr (1, TCSAFLUSH, &newts);
  _copy (master_fd, master_read, stdin_read, pid);
  tcsetattr (1, TCSAFLUSH, &ts);

  do {
    ret = waitpid (pid, &status, 0);
  } while (ret == -1 && errno == EINTR);
  if (ret == -1)
  {
    fprintf (stderr, "bicon: waitpid() failed.\n");
    exit (1);
  }
  return WEXITSTATUS (status);
}
