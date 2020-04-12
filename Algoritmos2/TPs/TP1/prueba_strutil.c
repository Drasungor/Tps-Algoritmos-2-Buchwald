#include <stdio.h>
#include <stdlib.h>
#include "strutil.h"





int main(int argc, char const *argv[]) {

  char** demn=split("QUE HACES FLACO", '\0');
  char** demn2=split("QUE HACES FLACO", ' ');

  int i=0;

  while (demn[i]!=NULL) {
    printf("%s\n", demn[i]);
    i++;
  }

  i=0;

  while (demn2[i]!=NULL) {
    printf("%s\n", demn2[i]);
    i++;
  }

  char* demn3=join(demn2, ' ');

  printf("%s\n", demn3);

  free_strv(demn);
  free_strv(demn2);
  free(demn3);

  return 0;
}
