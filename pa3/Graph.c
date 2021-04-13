/****************************************************************************************
*  Cole Watts
*  comwatts
*  PA3
*  Graph.c
*  Implementation file for Graph ADT
*****************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include <stdbool.h>

#include "List.h"
#include "Graph.h"

typedef struct GraphObj
{
   int edgeSize;
   int source;
   int vertSize;

   List* adjArray;

   int* arrayDist;
   int* arrayParent;
   char* arrayColor;

} GraphObj;


Graph newGraph(int n)
{
   Graph newG;
   newG = malloc(sizeof(GraphObj));

   newG->arrayDist = calloc(n+1, sizeof(int));
   newG->arrayParent = calloc(n+1, sizeof(int));
   newG->arrayColor = calloc(n+1, sizeof(char));
   
   newG->adjArray = malloc(sizeof(List) * (n+1));

   int var;

   for(var = 1; var < n+1; var++){   

      newG->arrayDist[var] = INF;
      newG->arrayParent[var] = NIL;
      newG->arrayColor[var] = WHITE;

      newG->adjArray[var] = newList();
   }

   newG->edgeSize = 0;
   newG->source = NIL;
   newG->vertSize = n;

   return newG;
}

void freeGraph(Graph* pG)
{
   if(pG == NULL){
		printf("Error: Graph is NULL\n");
		exit(EXIT_FAILURE);
   }
}

int getSource(Graph newG)
{
   if(newG == NULL){
		printf("Error: Graph is NULL\n");
		exit(EXIT_FAILURE);
   }
   return newG->source;
}

int getOrder(Graph newG)
{
   if(newG == NULL){
		printf("Error: Graph is NULL\n");
		exit(EXIT_FAILURE);
   }

   return newG->vertSize;
}

int getSize(Graph newG)
{
   if(newG == NULL){
		printf("Error: Graph is NULL\n");
		exit(EXIT_FAILURE);
   }
   return newG->edgeSize;
}

int getDist(Graph newG, int u)
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

   if(getSource(newG) == NIL)
   {
      return INF;
   }

   return newG->arrayDist[u];
}

int getParent(Graph newG, int u)
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

   if(getSource(newG) == NIL)
   {
      return NIL;	
   }

   return newG->arrayParent[u];
}

void getPath(List newL, Graph newG, int u)
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

   if(getSource(newG) == NIL)
   {
      printf("Error: No source\n");
      exit(EXIT_FAILURE);
   }

   if(u == getSource(newG))
   {
      append(newL, getSource(newG));
   }

   else if(getParent(newG, u) == 0)
   {
      append(newL, 0);
   }

   else
   {
      getPath(newL, newG, getParent(newG, u));
      append(newL, u);
   }
}

void addArc(Graph newG, int u, int v)
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

void makeNull(Graph newG)
{
   if(newG == NULL){
		printf("Error: Graph is NULL\n");
		exit(EXIT_FAILURE);
   }

   int var;

   for(var = 1; var <= getOrder(newG); var++)
   {
      clear(newG->adjArray[var]);
   }

   newG->edgeSize = 0;
}

void BFS(Graph newG, int s)
{
   if(newG == NULL){
		printf("Error: Graph is NULL\n");
		exit(EXIT_FAILURE);
   }

   if(1 > s)
   {
      printf("Error: Out of bounds\n");
      exit(EXIT_FAILURE);
   }

   if(getOrder(newG) < s)
   {
      printf("Error: Out of bounds\n");
      exit(EXIT_FAILURE);
   }
   
   int var;

   for(var = 1; var <= getOrder(newG); var++)
   {         
      newG->arrayDist[var] = INF;
      newG->arrayParent[var] = NIL;
      newG->arrayColor[var] = WHITE;
   }
   
   newG->source = s;

   newG->arrayDist[s] = 0;
   newG->arrayParent[s] = NIL;
   newG->arrayColor[s] = GREY;

   List sequence = newList();
   append(sequence,s);
  
   while(length(sequence) != 0)
   {
      int uDist = newG->arrayDist[front(sequence)];

      List uList = newG->adjArray[front(sequence)];

      if(!isEmpty(uList))
      {
         moveFront(uList);

         while(index(uList) != -1)
         {
            if(newG->arrayColor[get(uList)] == WHITE)
   
            {               
               newG->arrayDist[get(uList)] = uDist + 1;
               newG->arrayParent[get(uList)] = front(sequence);
               newG->arrayColor[get(uList)] = GREY;
               
               append(sequence, get(uList));
            }

            moveNext(uList);
         }
      }

      newG->arrayColor[front(sequence)] = BLACK;
      deleteFront(sequence);
   }

   freeList(&sequence);
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
