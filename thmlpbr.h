/*
 *
 * Copyright 2001 by Christopher C. Little
 *
 */

#ifndef THMLPBR_H
#define THMLPBR_H

#include <swfilter.h>

#include <defs.h>

SWORD_NAMESPACE_START

  /** this filter converts ThML text to plain text
  */
class SWDLLEXPORT ThMLPBR:public SWFilter
{
public:
  ThMLPBR ();
  virtual char ProcessText (char *text, int maxlen = -1);
};
SWORD_NAMESPACE_END
#endif
