#ifndef __BICON_READ_H
#define __BICON_READ_H

extern int bicon_options;

ssize_t bicon_read (
  int fd,
  void *buf,
  size_t ct);
int bicon_read_init (
  void);

#endif /*__BJOIN_H*/
