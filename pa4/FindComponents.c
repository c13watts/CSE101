/****************************************************************************************
*  Cole Watts
*  comwatts
*  PA4
*  FindComponents.c
*  Client program for Graph ADT
*****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

int main(int argc, char *argv[])
{

  FILE *in = fopen(argv[1], "r"),
       *out = fopen(argv[2], "w");

  List newList1 = newList();
  List newList2 = newList();

  int a = 0;
  int graphSize = 0;
  int variable1;
  int variable2;

  fscanf(in, "%d", &graphSize);
  fscanf(in, "%d", &variable1);
  fscanf(in, "%d", &variable2);

  Graph newG = newGraph(graphSize);

  while (variable1 != NIL && variable2 != NIL)
  {

    if (variable1 == NIL && variable2 == NIL)
    {
      printf("Error: something went wrong");
      fprintf(out, "\n");
      break;
    }

    addArc(newG, variable1, variable2);
    fscanf(in, "%d", &variable1);
    fscanf(in, "%d", &variable2);
  }

  fprintf(out, "Adjacency list representation of G:");
  fprintf(out, "\n");
  printGraph(out, newG);

  int var;

  for (var = 1; var <= graphSize; var++)
  {
    append(newList1, var);
  }

  DFS(newG, newList1);
  Graph transposeG = transpose(newG);
  DFS(transposeG, newList1);

  moveFront(newList1);

  while (index(newList1) != INF)
  {
    if (getParent(transposeG, get(newList1)) == NIL)
    {
      a++;
    }
    moveNext(newList1);
  }

  fprintf(out, "G contains %d strongly connected components:", a);
  moveBack(newList1);

  for (var = 1; var <= a; var++)
  {
    while (newList1 != NIL && newList2 != NIL)
    {
      if (newList1 == NIL && newList2 == NIL)
      {
        printf("Error: something went wrong");
        fprintf(out, "\n");
        break;
      }

      prepend(newList2, get(newList1));

      if (getParent(transposeG, get(newList1)) == NIL)
      {
        fprintf(out, "\n");
        fprintf(out, "Component %d: ", var);
        printList(out, newList2);
        break;
      }

      movePrev(newList1);
    }

    movePrev(newList1);
    clear(newList2);
  }

  return (EXIT_SUCCESS);
}
