#ifndef __BJOINING_JOINING_H
#define __BJOINING_JOINING_H

#include "bjoining.h"

int bjoining_vis2cuni (
  unichar * vis,
  int len,
  unichar * cuni,
  int *clen,
  int options);

/*
 * returns the joining status of w to its (next ? "next" : "previous")
 * character.
 *
 * return values:
 *   0  does not join
 *   1  joins
 *  -1  ambigous
 */
int join_type (
  unichar w,
  int next);

unichar arablig (
  unichar first,
  unichar second);

#endif
