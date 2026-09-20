#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *greeting = malloc(32);
  strcpy(greeting, "Hello, world!");
  printf("%s\n", greeting);

  free(greeting);



  return 0;
}
