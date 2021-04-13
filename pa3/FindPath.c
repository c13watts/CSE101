/****************************************************************************************
*  Cole Watts
*  comwatts
*  PA3
*  FindPath.c
*  Client program for Graph ADT
*****************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

#include"Graph.h"
#include"List.h"

int main(int argc, char * argv[]){

	  FILE *in = fopen(argv[1], "r"),
         *out = fopen(argv[2], "w");

    List newL = newList();

    int graphSize = 0;

    int variable1;
    int variable2;
    int variable3;
    int variable4;

    fscanf(in, "%d", &graphSize);
    fscanf(in, "%d", &variable1);
    fscanf(in, "%d", &variable2);


    Graph newG = newGraph(graphSize);

    while(variable1 != NIL && variable2 != NIL){

      if(variable1 == NIL || variable2 == NIL)
      {

        printf("Error: couldnt find edges to graph\n");
        break;
      }

   	  addEdge(newG, variable1, variable2);
      fscanf(in, "%d", &variable1);
      fscanf(in, "%d", &variable2);
    }

    printGraph(out, newG);
    fscanf(in, "%d", &variable3);
    fscanf(in, "%d", &variable4);

    while(variable3 != NIL && variable4 != NIL){

      if(variable3 == NIL || variable4 == NIL)
      {

        printf("Error: couldnt find distance and shortest path to graph\n");
        break;
      }

   	  BFS(newG, variable3);
   	  getPath(newL, newG, variable4);

      fprintf(out, "The distance from ");

   	  if(getDist(newG, variable4) == INF){
        fprintf(out, "%d to %d is infinity\n", variable3, variable4);
	   	  fprintf(out, "No %d-%d path exists\n", variable3, variable4);
      }
	    else{
        fprintf(out, "%d to %d is %d\n", variable3, variable4, getDist(newG, variable4));
	   	  fprintf(out, "A shortest %d-%d path is:", variable3, variable4);
       
	   	  printList(out, newL);
	    }

      fprintf(out, "\n");
      fscanf(in, "%d", &variable3);
      fscanf(in, "%d", &variable4);
      clear(newL);
    }
  
	return (EXIT_SUCCESS);
}