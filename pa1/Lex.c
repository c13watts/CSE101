/****************************************************************************************
*  Cole Watts
*  comwatts
*  PA1
*  Lex.c
*  Arranges input text in alpabetical order
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"

int main(int argc, char *argv[]) {

  FILE *in;
  FILE *out;
  char line[256];
  int result = 0;

  if (argc != 3) 
  {
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }

  in = fopen(argv[1], "r");
  out = fopen(argv[2], "w");

  if (in == NULL) 
  {
    printf("Unable to read from file %s\n", argv[1]);
    exit(1);
  }

  if (out == NULL) 
  {
    printf("Unable to write to file %s\n", argv[2]);
    exit(1);
  }

  while (fgets(line, sizeof(line), in) != NULL) 
  {
    result++;
  }

  char *array[result];
  result = 0;
  rewind(in);

  while (fgets(line, sizeof(line), in) != NULL) 
  {
    array[result] = malloc(sizeof(line));
    strcpy(array[result], line);
    result++;
  }

  List L = newList();

  for (int i = 0; i < result; i++) 
  {

    if (isEmpty(L)) 
    {
      append(L, i);
    } else {
      moveFront(L);
      for (int z = 0; z <= length(L); z++) 
      {
        if (z == length(L)) 
        {
          insertAfter(L, i);
          break;
        }

        if (strcmp(array[i], array[get(L)]) <= 0) 
        {
          insertBefore(L, i);
          break;
        }
        if (z < length(L) - 1) 
        {
          moveNext(L);
        }
      }
    }
  }

  moveFront(L);
  for (int i = 0; i < result; i++) 
  {
    fprintf(out, "%s", array[get(L)]);
    moveNext(L);
  }

  clear(L);
  freeList(&L);

  for (int i = 0; i < result; i++) 
  {
    free(array[i]);
  }

  fclose(in);
  fclose(out);

  return (0);
}
