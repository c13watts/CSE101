/****************************************************************************************
*  Cole Watts
*  comwatts
*  PA4
*  Graph.c
*  Implementation file for Graph ADT
*****************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include <stdbool.h>
#include "Graph.h"

typedef struct GraphObj
{
   int edgeSize;
   int vertSize;

   List* adjArray;

   int* arrayParent;
   int* arrayDisc;
   int* arrayStop;
   char* arrayColor;

} GraphObj;

Graph newGraph(int n)
{
   Graph newG;
   newG= malloc(sizeof(GraphObj));
   newG->arrayParent = calloc(n+1,sizeof(int));
   newG->arrayDisc = calloc(n+1,sizeof(int));
   newG->arrayStop = calloc(n+1,sizeof(int));
   newG->arrayColor = calloc(n+1,sizeof(char));

   newG->adjArray = malloc(sizeof(List) * (n+1));

   int var;

   for(var = 1; var < n+1; var++)
   {
      newG->arrayParent[var] = NIL;
      newG->arrayDisc[var] = UNDEF;
      newG->arrayStop[var] = UNDEF;
      newG->arrayColor[var] = WHITE;

      newG->adjArray[var] = newList();

   }

   newG->vertSize = n;
   newG->edgeSize = 0;

   return newG;
}

void freeGraph(Graph* pG)
{
   if(pG == NULL)
   {
		printf("Error: Graph is NULL\n");
		exit(EXIT_FAILURE);
   }
}

int getSize(Graph newG)
{
   
   if(newG == NULL)
   {
		printf("Error: Graph is NULL\n");
		exit(EXIT_FAILURE);
   }

   return newG->edgeSize;
}

int getOrder(Graph newG)
{

   if(newG == NULL)
   {
		printf("Error: Graph is NULL\n");
		exit(EXIT_FAILURE);
   }

   return newG->vertSize;
}

int getFinish(Graph newG, int u)
{
   if(newG == NULL)
   {
		printf("Error: Graph is NULL\n");
		exit(EXIT_FAILURE);
   }

   if(1 > u)
   {
      printf("Error: Out of bounds\n");
      exit(EXIT_FAILURE);
   }

   if(getOrder(newG) < u)
   {
      printf("Error: Out of bounds\n");
      exit(EXIT_FAILURE);
   }

   return newG->arrayStop[u];
}

int getDiscover(Graph newG, int u)
{
   if(newG == NULL)
   {
		printf("Error: Graph is NULL\n");
		exit(EXIT_FAILURE);
   }

   if(1 > u)
   {
      printf("Error: Out of bounds\n");
      exit(EXIT_FAILURE);
   }

   if(getOrder(newG) < u)
   {
      printf("Error: Out of bounds\n");
      exit(EXIT_FAILURE);
   }

   return newG->arrayDisc[u];
}

int getParent(Graph newG, int u)
{
   if(newG == NULL)
   {
		printf("Error: Graph is NULL\n");
		exit(EXIT_FAILURE);
   }

   if(1 > u)
   {
      printf("Error: Out of bounds\n");
      exit(EXIT_FAILURE);
   }

   if(getOrder(newG) < u)
   {
      printf("Error: Out of bounds\n");
      exit(EXIT_FAILURE);
   }

   return newG->arrayParent[u];
}

void addArc(Graph newG, int u, int v)
{
   if(newG == NULL)
   {
		printf("Error: Graph is NULL\n");
		exit(EXIT_FAILURE);
   }

   if(1 > u)
   {
      printf("Error: Out of bounds\n");
      exit(EXIT_FAILURE);
   }

   if(u > getOrder(newG))
   {
      printf("Error: Out of bounds\n");
      exit(EXIT_FAILURE);
   }

   if(1 > v)
   {
      printf("Error: Out of bounds\n");
      exit(EXIT_FAILURE);
   }

   if(v > getOrder(newG))
   {
      printf("Error: Out of bounds\n");
      exit(EXIT_FAILURE);
   }

   List uList = newG->adjArray[u];
   bool boolVariableU = false;

   if(length(uList) == 0)
   {
      append(uList, v);
   }
   else
   {
      moveFront(uList);

      while(boolVariableU == 0 && index(uList) != -1)
      {
         if(get(uList) > v)
         {
            insertBefore(uList, v);
            
            boolVariableU = true;
         }
         else
         {
            moveNext(uList);
         }
      }

      if(boolVariableU == 0)
      {
         append(uList, v);
      }
   }

   newG->edgeSize++;
}

void addEdge(Graph newG, int u, int v)
{
   if(newG == NULL){
		printf("Error: Graph is NULL\n");
		exit(EXIT_FAILURE);
   }

   if(1 > u)
   {
      printf("Error: Out of bounds\n");
      exit(EXIT_FAILURE);
   }

   if(getOrder(newG) < u)
   {
      printf("Error: Out of bounds\n");
      exit(EXIT_FAILURE);
   }

   if(1 > v)
   {
      printf("Error: Out of bounds\n");
      exit(EXIT_FAILURE);
   }

   if(getOrder(newG) < v)
   {
      printf("Error: Out of bounds\n");
      exit(EXIT_FAILURE);
   }

   List uList = newG->adjArray[u];
   List vList = newG->adjArray[v];
   bool boolVariableU = false;
   bool boolVariableV = false;

   if(length(uList) == 0)
   {
      append(uList, v);
   }
   else
   {
      moveFront(uList);

      while(boolVariableU == 0 && index(uList) != -1 )
      {
         if(get(uList) < v)
         {
            moveNext(uList);
         }

         else
         {
            insertBefore(uList, v);

            boolVariableU = true;
         }
      }
      
      if(boolVariableU == 0)
      {
         append(uList, v);
      }
   }

   if(length(vList) == 0)
   {
      append(vList, u);
   }
   else
   {
      moveFront(vList);

      while(boolVariableV == 0 && index(vList) != -1)
      {
         if(get(vList) < u )
         {
            moveNext(vList);
         }

         else
         {
            insertBefore(vList, u);

            boolVariableV = true; 
         }
      }

      if(boolVariableV == 0)
      {
         append(vList, u);
      }
   }

   newG->edgeSize++;
}

void visit(Graph newG, List S, int *time, int x)
{
   if(newG == NULL)
   {
		printf("Error: Graph is NULL\n");
		exit(EXIT_FAILURE);
   }

   if(S == NULL)
   {
		printf("Error: List is NULL\n");
		exit(EXIT_FAILURE);
   }

   List variable = newG->adjArray[x];

   newG->arrayDisc[x] = ++(*time);
   newG->arrayColor[x] = GREY;
   newG->arrayColor[x] = BLACK;

   if(!isEmpty(variable))
   {
      moveFront(variable);

      while(index(variable) != INF)
      {
         if(newG->arrayColor[get(variable)] == WHITE)
         {
            newG->arrayParent[get(variable)] = x;

            visit(newG, S, time, get(variable));
         }

         moveNext(variable);
      }
   }

   newG->arrayStop[x] = ++(*time);

   while(index(S) != getOrder(newG) - 1)
   {
      moveNext(S);
   }

   insertAfter(S,x);
   moveFront(S);
}

void DFS(Graph newG, List S)
{
   if(newG == NULL)
   {
		printf("Error: Graph is NULL\n");
		exit(EXIT_FAILURE);
   }

   if(S == NULL)
   {
		printf("Error: List is NULL\n");
		exit(EXIT_FAILURE);
   }

   if(length(S) != getOrder(newG)){
        printf("Graph Error: invalid length\n");
        exit(EXIT_FAILURE);
    }
   
   int var = 0;
   int time = 0;

   for(var = 1; var <= getOrder(newG); var++)
   {
      newG->arrayColor[var] = WHITE;
      newG->arrayParent[var] = NIL;
   }

   moveFront(S);

   while(index(S) != INF)
   {
      if(newG->arrayColor[get(S)] == WHITE)
      {
         visit(newG, S, &time, get(S));
      }
      moveNext(S);
   }

   for(var = 1; var <= getOrder(newG); var++)
   {
      deleteFront(S);
   }
}

Graph transpose(Graph newG)
{
   if(newG == NULL)
   {
		printf("Error: Graph is NULL\n");
		exit(EXIT_FAILURE);
   }

   Graph transposeG = newGraph(getOrder(newG)); 

   int var;

   for(var = 1; var <= getOrder(newG); var++)
   {
      List transposeL = newG->adjArray[var];
      moveFront(transposeL);

      while(index(transposeL) >= 0)
      {
         addArc(transposeG, get(transposeL), var);

         moveNext(transposeL);
      }
   }

   return transposeG;
}

Graph copyGraph(Graph newG)
{
   if(newG == NULL)
   {
		printf("Error: Graph is NULL\n");
		exit(EXIT_FAILURE);
   }

   Graph copyG = newGraph(getOrder(newG));

   return copyG;   
}

void printGraph(FILE* out, Graph newG)
{
   int var;
   
   for(var = 1; var <= getOrder(newG); var++)
   {
		fprintf(out, "%d:", var);
		
      if(length(newG->adjArray[var]) == 0)
      {
			fprintf(out, " ");
		}
		
      printList(out, newG->adjArray[var]);
		fprintf(out, "\n");

	}

     fprintf(out, "\n");
}
