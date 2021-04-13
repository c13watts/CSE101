#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "Dictionary.h"

typedef struct NodeObj
{
   struct NodeObj* rightNode;
   struct NodeObj* leftNode;
   struct NodeObj* parentNode;

   char* key;
   int value;

} NodeObj;

typedef NodeObj* Node;

Node newNode(KEY_TYPE k, VAL_TYPE v)
{
   Node N = malloc(sizeof(NodeObj));
   N->key = k;
   N->value = v;

   N->rightNode = NULL;
   N->leftNode = NULL;
   N->parentNode = NULL;

   return N;	
}

void freeNode(Node* pN)
{
   if(pN == NULL)
   {
		printf("Error: Node pN is NULL\n");
		exit(EXIT_FAILURE);
   }
}

Node Search(Node x, KEY_TYPE k)
{
   if(x < 0)
   {
		printf("Error: Node x is NULL\n");
		exit(EXIT_FAILURE);
   }

   if(x == NULL || KEY_CMP(x->key,k) == 0)
   {
      return x;
   }

   if(KEY_CMP(k, x->key) < 0)
   {
      return Search(x->leftNode,k);
   }

   return Search(x->rightNode,k);
}

Node Max(Node x)
{
   if(x == NULL)
   {
		printf("Error: Node x is NULL\n");
   }
   
   else 
   {
      while(x->rightNode != NULL)
      {
         x = x->rightNode;
      }
   }
   
   return x;
}

Node Min(Node x)
{
   if(x == NULL)
   {
		printf("Error: Node x is NULL\n");
      
   }
   
   else 
   {
      while(x->leftNode != NULL)
      {
         x = x->leftNode;
      }
   }
   
   return x;
}

Node Latter(Node x)
{
   if(x < 0)
   {
		printf("Error: Node x is NULL\n");
		exit(EXIT_FAILURE);
   }

   if(x->rightNode != NULL)
   {
      x = Min(x->rightNode);
      return x;
   }

   Node y = x->parentNode;

   while(y != NULL && x == y->rightNode)
   {
      x = y;
      y = y->parentNode;
   }

   return y;
}

Node Former(Node x)
{
   if(x < 0)
   {
		printf("Error: Node x is NULL\n");
		exit(EXIT_FAILURE);
   }

   if(x->leftNode != NULL)
   {
      x = Max(x->leftNode);
      return x; 
   }

   Node y = x->parentNode;
   while (y != NULL && KEY_CMP(x->key,y->key) < 0)
   {
      x = y;
      y = y->parentNode;
   }

   return y;
}

typedef struct DictionaryObj
{
   Node root;
   Node current;
   int unique;
   int size;
} DictionaryObj;

Dictionary newDictionary(int unique)
{
   Dictionary D = malloc(sizeof(DictionaryObj));
   D->root = NULL;
   D->current = NULL;
   D->unique = unique;
   D->size = 0;
   return D;
}

void freeDictionary(Dictionary* pD)
{
   if(pD == NULL)
   {
		printf("Error: Dictionary pD is NULL\n");
		exit(EXIT_FAILURE);
   }
}	

int getUnique(Dictionary D)
{
   if(D == NULL)
   {
		printf("Error: Dictionary D is NULL\n");
		exit(EXIT_FAILURE);
   }

   return D->unique;
}

int size(Dictionary D)
{
   if(D == NULL)
   {
		printf("Error: Dictionary D is NULL\n");
		exit(EXIT_FAILURE);
   }

   return D->size;
}

	
void Transplant(Dictionary D, Node u, Node v)
{
   if(D == NULL)
   {
		printf("Error: Dictionary D is NULL\n");
		exit(EXIT_FAILURE);
   }

   if(u < 0)
   {
		printf("Error: Dictionary D is NULL\n");
		exit(EXIT_FAILURE);
   }

   if(v < 0)
   {
		printf("Error: Dictionary D is NULL\n");
		exit(EXIT_FAILURE);
   }

   if(u->parentNode == NULL)
   {
      D->root = v;

      if(v != NULL)
      {
         v->parentNode = NULL;
      }
   }

   else if(u == u->parentNode->leftNode)
   {
      u->parentNode->leftNode = v;
   }

   else
   {
      u->parentNode->rightNode = v;
   }

   if(v != NULL)
   {
      v->parentNode = u->parentNode;
   }
}

VAL_TYPE lookup(Dictionary D, KEY_TYPE k)
{
   if(D == NULL)
   {
		printf("Error: Dictionary D is NULL\n");
		exit(EXIT_FAILURE);
   }

   Node n = Search(D->root,k);

   if(n == NULL)
   {
      return VAL_UNDEF;
   }

   return n->value;
}

void delete(Dictionary D, KEY_TYPE k)
{
   if(D == NULL)
   {
		printf("Error: Dictionary D is NULL\n");
		exit(EXIT_FAILURE);
   }

   if(lookup(D,k) == VAL_UNDEF)
   {  
      printf("Error: calling lookup() when Dictionary D is NULL\n");
		exit(EXIT_FAILURE);
   }

   Node newNode1 = D->root;

   while(strcmp(newNode1->key, k) != 0)
   {
      if(strcmp(newNode1->key, k) < 0)
      {
         newNode1 = newNode1->rightNode;
      }	
      else if (strcmp(newNode1->key, k) > 0)
      {
         newNode1 = newNode1->leftNode;
      }
   }	

   if(D->current == newNode1)
   {
      D->current = NULL;
   }

   if(newNode1->rightNode == NULL)
   {
      Transplant(D, newNode1, newNode1->leftNode);
   }

   else if(newNode1->leftNode == NULL)
   {
      Transplant(D, newNode1, newNode1->rightNode);
   }

   D->size -= 1; 
}

void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v)
{
   if(D == NULL)
   {
		printf("Error: Dictionary D is NULL\n");
		exit(EXIT_FAILURE);
   }

   Node rootNode = D->root;
   Node nullNode = NULL;
   Node N = newNode(k, v);

   while(rootNode != NULL)
   {
      nullNode = rootNode;

      if (strcmp(k, rootNode->key) < 0)
      {
         rootNode = rootNode->leftNode;
      }
      
      else
      {
         rootNode = rootNode->rightNode;
      }
   }

   if (nullNode == NULL)
   {
      D->root = N;
   }

   else if (strcmp(k, nullNode->key) < 0)
   {
      N->parentNode = nullNode;
      nullNode->leftNode = N;
   }   
 
   else
   {
      N->parentNode = nullNode;
      nullNode->rightNode = N;
   }

   D->size++;
}

void makeEmpty(Dictionary D)
{
   if (D == NULL)
   {
      printf("Error: Dictionary D is NULL\n");
      exit(EXIT_FAILURE);
   }

   while(D->root != NULL)
   {
      delete(D,D->root->key); 
   }
}

VAL_TYPE currentVal(Dictionary D)
{
   if (D == NULL)
   {
      printf("Error: Dictionary D is NULL\n");
      exit(EXIT_FAILURE);
   }

   if(D->current == NULL)
   {
      return VAL_UNDEF;
   }

   return D->current->value;
}

KEY_TYPE currentKey(Dictionary D)
{
   if (D == NULL)
   {
      printf("Error: Dictionary D is NULL\n");
      exit(EXIT_FAILURE);
   }

   if(D->current == NULL)
   {
      return KEY_UNDEF;
   }

   return D->current->key;
}

VAL_TYPE prev(Dictionary D)
{
   if (D == NULL)
   {
      printf("Error: Dictionary D is NULL\n");
      exit(EXIT_FAILURE);
   }

  if(D->current == NULL)
  {
     return currentVal(D);
  }

  D->current = Former(D->current);

  return currentVal(D);
}

VAL_TYPE next(Dictionary D)
{
   if (D == NULL)
   {
      printf("Error: Dictionary D is NULL\n");
      exit(EXIT_FAILURE);
   }

  if(D->current == NULL)
  {
     return currentVal(D);
  }

  D->current = Latter(D->current);

  return currentVal(D);
}

VAL_TYPE beginReverse(Dictionary D)
{
   if (D == NULL)
   {
      printf("Error: Dictionary D is NULL\n");
      exit(EXIT_FAILURE);
   }

   D->current = Max(D->root);

   return currentVal(D);
}

VAL_TYPE beginForward(Dictionary D)
{
   if (D == NULL)
   {
      printf("Error: Dictionary D is NULL\n");
      exit(EXIT_FAILURE);
   }

   D->current = Min(D->root);

   return currentVal(D); 
}

void printDictionary(FILE* out, Dictionary D)
{
   if (D == NULL)
   {
      printf("Error: Dictionary D is NULL\n");
      exit(EXIT_FAILURE);
   }

   Node x = D->root;
   fprintf(out, "%s %d\n", x->key, x->value);
}