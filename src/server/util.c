#include "headers/util.h"

char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace(*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace(*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;
}

void die(char *msg){
  perror(msg); 
  exit(EXIT_FAILURE);
}

void itos(char *string, int number){
  sprintf(string,"%d",number);
}