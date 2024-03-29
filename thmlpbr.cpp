/*
 *
 * Copyright 2001 by Christopher C. Little
 *
 */

/******************************************************************************
 *
 * thmlpbr -	SWFilter decendant to strip out all ThML tags or convert to
 *		ASCII rendered symbols with some Palm Bible Reader markup.
 */


#include <stdlib.h>
#include <string.h>
#include "thmlpbr.h"
SWORD_NAMESPACE_START

ThMLPBR::ThMLPBR() {
}


char ThMLPBR::ProcessText(char *text, int maxlen)
{
  char *to, *from, token[2048];
  int tokpos = 0;
  bool intoken = false;
  int len;
  bool ampersand = false;
  bool sechead = false;
  bool havesechead = false;

  len = strlen(text) + 1;						// shift string to right of buffer
  if (len < maxlen) {
    memmove(&text[maxlen - len], text, len);
    from = &text[maxlen - len];
  }
  else	from = text;							// -------------------------------
	
  for (to = text; *from; from++) {
    if (*from == 10 || *from == 13)
      from++;
    if (*from == '<') {
      intoken = true;
      tokpos = 0;
      memset(token, 0, 2048);
      ampersand = false;
      continue;
    }
    else if (*from == '&') {
      intoken = true;
      tokpos = 0;
      memset(token, 0, 2048);
      ampersand = true;
      continue;
    }
    if (*from == ';' && ampersand) {
      intoken = false;

      if (!strncmp("nbsp", token, 4)) *to++ = ' ';
      else if (!strncmp("quot", token, 4)) *to++ = '"';
      else if (!strncmp("amp", token, 3)) *to++ = '&';
      else if (!strncmp("lt", token, 2)) *to++ = '<';
      else if (!strncmp("gt", token, 2)) *to++ = '>';
      else if (!strncmp("brvbar", token, 6)) *to++ = '|';
      else if (!strncmp("sect", token, 4)) *to++ = '�';
      else if (!strncmp("copy", token, 4)) *to++ = '�';
      else if (!strncmp("laquo", token, 5)) *to++ = '�';
      else if (!strncmp("reg", token, 3)) *to++ = '�';
      else if (!strncmp("acute", token, 5)) *to++ = '�';
      else if (!strncmp("para", token, 4)) *to++ = '�';
      else if (!strncmp("raquo", token, 5)) *to++ = '�';

      else if (!strncmp("Aacute", token, 6)) *to++ = '�';
      else if (!strncmp("Agrave", token, 6)) *to++ = '�';
      else if (!strncmp("Acirc", token, 5)) *to++ = '�';
      else if (!strncmp("Auml", token, 4)) *to++ = '�';
      else if (!strncmp("Atilde", token, 6)) *to++ = '�';
      else if (!strncmp("Aring", token, 5)) *to++ = '�';
      else if (!strncmp("aacute", token, 6)) *to++ = '�';
      else if (!strncmp("agrave", token, 6)) *to++ = '�';
      else if (!strncmp("acirc", token, 5)) *to++ = '�';
      else if (!strncmp("auml", token, 4)) *to++ = '�';
      else if (!strncmp("atilde", token, 6)) *to++ = '�';
      else if (!strncmp("aring", token, 5)) *to++ = '�';
      else if (!strncmp("Eacute", token, 6)) *to++ = '�';
      else if (!strncmp("Egrave", token, 6)) *to++ = '�';
      else if (!strncmp("Ecirc", token, 5)) *to++ = '�';
      else if (!strncmp("Euml", token, 4)) *to++ = '�';
      else if (!strncmp("eacute", token, 6)) *to++ = '�';
      else if (!strncmp("egrave", token, 6)) *to++ = '�';
      else if (!strncmp("ecirc", token, 5)) *to++ = '�';
      else if (!strncmp("euml", token, 4)) *to++ = '�';
      else if (!strncmp("Iacute", token, 6)) *to++ = '�';
      else if (!strncmp("Igrave", token, 6)) *to++ = '�';
      else if (!strncmp("Icirc", token, 5)) *to++ = '�';
      else if (!strncmp("Iuml", token, 4)) *to++ = '�';
      else if (!strncmp("iacute", token, 6)) *to++ = '�';
      else if (!strncmp("igrave", token, 6)) *to++ = '�';
      else if (!strncmp("icirc", token, 5)) *to++ = '�';
      else if (!strncmp("iuml", token, 4)) *to++ = '�';
      else if (!strncmp("Oacute", token, 6)) *to++ = '�';
      else if (!strncmp("Ograve", token, 6)) *to++ = '�';
      else if (!strncmp("Ocirc", token, 5)) *to++ = '�';
      else if (!strncmp("Ouml", token, 4)) *to++ = '�';
      else if (!strncmp("Otilde", token, 6)) *to++ = '�';
      else if (!strncmp("oacute", token, 6)) *to++ = '�';
      else if (!strncmp("ograve", token, 6)) *to++ = '�';
      else if (!strncmp("ocirc", token, 5)) *to++ = '�';
      else if (!strncmp("ouml", token, 4)) *to++ = '�';
      else if (!strncmp("otilde", token, 6)) *to++ = '�';
      else if (!strncmp("Uacute", token, 6)) *to++ = '�';
      else if (!strncmp("Ugrave", token, 6)) *to++ = '�';
      else if (!strncmp("Ucirc", token, 5)) *to++ = '�';
      else if (!strncmp("Uuml", token, 4)) *to++ = '�';
      else if (!strncmp("uacute", token, 6)) *to++ = '�';
      else if (!strncmp("ugrave", token, 6)) *to++ = '�';
      else if (!strncmp("ucirc", token, 5)) *to++ = '�';
      else if (!strncmp("uuml", token, 4)) *to++ = '�';
      else if (!strncmp("Yacute", token, 6)) *to++ = '�';
      else if (!strncmp("yacute", token, 6)) *to++ = '�';
      else if (!strncmp("yuml", token, 4)) *to++ = '�';

      else if (!strncmp("deg", token, 3)) *to++ = '�';
      else if (!strncmp("plusmn", token, 6)) *to++ = '�';
      else if (!strncmp("sup2", token, 4)) *to++ = '�';
      else if (!strncmp("sup3", token, 4)) *to++ = '�';
      else if (!strncmp("sup1", token, 4)) *to++ = '�';
      else if (!strncmp("nbsp", token, 4)) *to++ = '�';
      else if (!strncmp("pound", token, 5)) *to++ = '�';
      else if (!strncmp("cent", token, 4)) *to++ = '�';
      else if (!strncmp("frac14", token, 6)) *to++ = '�';
      else if (!strncmp("frac12", token, 6)) *to++ = '�';
      else if (!strncmp("frac34", token, 6)) *to++ = '�';
      else if (!strncmp("iquest", token, 6)) *to++ = '�';
      else if (!strncmp("iexcl", token, 5)) *to++ = '�';
      else if (!strncmp("ETH", token, 3)) *to++ = '�';
      else if (!strncmp("eth", token, 3)) *to++ = '�';
      else if (!strncmp("THORN", token, 5)) *to++ = '�';
      else if (!strncmp("thorn", token, 5)) *to++ = '�';
      else if (!strncmp("AElig", token, 5)) *to++ = '�';
      else if (!strncmp("aelig", token, 5)) *to++ = '�';
      else if (!strncmp("Oslash", token, 6)) *to++ = '�';
      else if (!strncmp("curren", token, 6)) *to++ = '�';
      else if (!strncmp("Ccedil", token, 6)) *to++ = '�';
      else if (!strncmp("ccedil", token, 6)) *to++ = '�';
      else if (!strncmp("szlig", token, 5)) *to++ = '�';
      else if (!strncmp("Ntilde", token, 6)) *to++ = '�';
      else if (!strncmp("ntilde", token, 6)) *to++ = '�';
      else if (!strncmp("yen", token, 3)) *to++ = '�';
      else if (!strncmp("not", token, 3)) *to++ = '�';
      else if (!strncmp("ordf", token, 4)) *to++ = '�';
      else if (!strncmp("uml", token, 3)) *to++ = '�';
      else if (!strncmp("shy", token, 3)) *to++ = '�';
      else if (!strncmp("macr", token, 4)) *to++ = '�';
      continue;
      
    }
    else if (*from == '>' && !ampersand) {
      intoken = false;
      // process desired tokens
      if (!strncmp(token, "sync type=\"Strongs\" value=\"", 27)) {
	*to++ = ' ';
	*to++ = '<';
	for (unsigned int i = 27; token[i] != '\"'; i++)
	  *to++ = token[i];
	*to++ = '>';
	continue;
      }
      else if (!strncmp(token, "sync type=\"Morph\" value=\"", 25)) {
	*to++ = ' ';
	*to++ = '(';
	for (unsigned int i = 25; token[i] != '\"'; i++)
	  *to++ = token[i];
	*to++ = ')';
	continue;
      }
      else if (!strncmp(token, "note", 4)) {
	*to++ = ' ';
	*to++ = '(';
        continue;
      }
      else if (!strncmp(token, "/note", 5)) {
	*to++ = ')';
	*to++ = ' ';
        continue;
      }
      else if (!strncmp(token, "div class=\"sechead\"", 19)) {
        *to++ = '<';
        *to++ = 'D';
        *to++ = 'E';
        *to++ = 'S';
        *to++ = 'C';
        *to++ = 'T';
        *to++ = 'E';
        *to++ = 'X';
        *to++ = 'T';
        *to++ = '>';
        sechead = true;
        havesechead = true;
        continue;
      }
      else if (!strncmp(token, "/div", 4) && sechead) {
        *to++ = '<';
        *to++ = 'V';
        *to++ = 'E';
        *to++ = 'R';
        *to++ = 'S';
        *to++ = 'T';
        *to++ = 'E';
        *to++ = 'X';
        *to++ = 'T';
        *to++ = '>';
        sechead = false;
        havesechead = true;
        continue;
      }
      else if (!strncmp(token, "br", 2)) {
	*to++ = '\n';
        continue;
      }
      else if (!strncmp(token, "/p", 2)) {
	*to++ = '\n';
        continue;
      }
      continue;
    }

    if (intoken) {
	if (tokpos < 2047)
                token[tokpos++] = *from;
    }
    else
    	*to++ = *from;
  }
  *to++ = 0;
  *to = 0;

  if (!havesechead) {
          len = strlen(text) + 1;
          // shift string to right 10 bytes (if there's room)
          if (maxlen > len + 10) {
                  memmove(&text[10], text, len);
                  text[0] = '<';
                  text[1] = 'V';
                  text[2] = 'E';
                  text[3] = 'R';
                  text[4] = 'S';
                  text[5] = 'T';
                  text[6] = 'E';
                  text[7] = 'X';
                  text[8] = 'T';
                  text[9] = '>';
          }
  }
  return 0;
}
SWORD_NAMESPACE_END
