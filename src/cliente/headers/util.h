#ifndef _UTIL_H_
  #define _UTIL_H_

  #include <stdlib.h> /* exit */
  #include <string.h>
  #include <stdio.h>
  #include <ctype.h>

  char *trimwhitespace(char *);
  void die(char *);
  void itos(char *, int);
  void downcase(char *);

#endif
