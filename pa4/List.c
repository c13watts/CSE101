/****************************************************************************************
*  Cole Watts
*  comwatts
*  PA4
*  List.c
*  Implementation file for List ADT
*****************************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"


// NodeObj
typedef struct NodeObj 
{
  int data;
  struct NodeObj *after;
  struct NodeObj *before;
} NodeObj;

// Node
typedef NodeObj *Node;

// newNode()
// constructor of the Node type
Node newNode(int a) 
{
  Node new_Node = malloc(sizeof(NodeObj));
  assert(new_Node != NULL);
  new_Node->data = a;
  new_Node->after = NULL;
  new_Node->before = NULL;
  return (new_Node);
}

// freeNode()
// destructor for the Node type
void freeNode(Node *prevNode) 
{
  if (prevNode != NULL && *prevNode != NULL) 
  {
    free(*prevNode);
    *prevNode = NULL;
  }
}

// ListObj
typedef struct ListObj 
{
  Node front;
  Node back;
  Node cursor;
  int index;
  int totalItems;
} ListObj;


//newList()
List newList(void) 
{
  List L;
  L = malloc(sizeof(ListObj));
  assert(L != NULL);
  L->front = NULL;
  L->back = NULL;
  L->cursor = NULL;
  L->index = -1;
  L->totalItems = 0;
  return (L);
};

//freeList()
void freeList(List *pL) 
{
  if (pL != NULL && *pL != NULL) 
  {

    if (!isEmpty(*pL))
      clear(*pL);

    free(*pL);
    *pL = NULL;
  }
};


int isEmpty(List L) 
{
  if (L == NULL) 
  {
    printf("List Error: calling isEmpty() on NULL List reference\n");
    exit(1);
  }
  return (L->totalItems == 0);
}

// Returns length of List.
int length(List L) 
{
  if (L == NULL) 
  {
    printf("List Error: calling length() on NULL List reference\n");
    exit(1);
  }
  return (L->totalItems);
};

// Returns index of cursor element if defined, -1 otherwise.
int index(List L) 
{
  if (L == NULL) 
  {
    printf("List Error: calling index() on NULL List reference\n");
    exit(1);
  }

  if (L->cursor == NULL) 
  {
    return -1;
  }
  int count = 0;
  for (Node I = L->cursor; I->before != NULL; I = I->before) 
  {
    count++;
  }
  return count;
};

// Returns front element of L. Pre: length()>0
int front(List L) 
{
  if (L == NULL) 
  {
    printf("List Error: calling front() on NULL List reference\n");
    exit(1);
  }

  if (isEmpty(L)) 
  {
    printf("List Error: calling front() on an empty List\n");
    exit(1);
  }
  return (L->front->data);
};

// Returns back element of L. Pre: length()>0
int back(List L) 
{
  if (L == NULL) 
  {
    printf("List Error: calling back() on NULL List reference\n");
    exit(1);
  }

  if (isEmpty(L)) 
  {
    printf("List Error: calling back() on an empty List\n");
    exit(1);
  }
  return (L->back->data);
};

// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L)
{
  if (L == NULL) 
  {
    printf("List Error: calling get() on NULL List reference\n");
    exit(1);
  }

  if (isEmpty(L)) 
  {
    printf("List Error: calling get() on an empty List\n");
    exit(1);
  }

  if (index(L) < 0)
  {
    printf("List Error: calling get() on NULL cursor reference\n");
    exit(1);
  }
  return (L->cursor->data);
};

// Returns true (1) iff Lists A and B are in same state, returns false(0) otherwise.
int equals(List A, List B) 
{
  Node a = A->front;
  Node b = B->front;
  int sameState = 0;

  if (A == NULL || B == NULL) 
  {
    printf("List Error: calling get() on NULL List reference\n");
    exit(1);
  }

  if (isEmpty(A) && isEmpty(B)) 
  {
    sameState = 1;
    return sameState;
  }
  if (isEmpty(A) && !isEmpty(B)) 
  {
    return sameState;
  }
  if (!isEmpty(A) && isEmpty(B)) 
  {
    return sameState;
  }

  while (a->data == b->data) 
  {
    if (a->after == NULL || b->after == NULL) 
    {
      if (a->after == NULL && b->after == NULL) 
      {
        sameState = 1;
        return sameState;
      }
      break;
    }
    a = a->after;
    b = b->after;
  }
  return sameState;
};

// Manipulation procedures

// Resets L to its original empty state.
void clear(List L) 
{
  if (L == NULL) 
  {
    printf("List Error: calling clear() on NULL List reference\n");
    exit(1);
  }

  while ((L->totalItems) > 0) 
  {
    deleteFront(L);
  }
};

// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L) 
{
  if (L == NULL) 
  {
    printf("List Error: calling moveFront() on NULL List reference\n");
    exit(1);
  }

  if (isEmpty(L)) 
  {
    printf("List Error: calling moveFront() on an empty List\n");
    exit(1);
  }
  L->cursor = L->front;
};

// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L) 
{
  if (L == NULL) 
  {
    printf("List Error: calling moveBack() on NULL List reference\n");
    exit(1);
  }

  if (isEmpty(L)) 
  {
    printf("List Error: calling moveBack() on an empty List\n");
    exit(1);
  }
  L->cursor = L->back;
};

// If cursor is defined and not at front, move cursor one
// step toward the front of L;if cursor is defined and at
// front, cursor becomes undefined;if cursor is undefined
// do nothing
void movePrev(List L) 
{
  if (L == NULL) 
  {
    printf("List Error: calling movePrev() on NULL List reference\n");
    exit(1);
  }
  if (L->cursor != NULL && L->cursor->before == NULL) 
  {
    L->cursor = NULL;
  } 
  else if (L->cursor != NULL) 
  {
    L->cursor = L->cursor->before;
  }
};

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined;if cursor is undefined
// do nothing
void moveNext(List L) 
{
  if (L == NULL) 
  {
    printf("List Error: calling moveNext() on NULL List reference\n");
    exit(1);
  }
  if (L->cursor != NULL && L->cursor->after == NULL) 
  {
    L->cursor = NULL;
  } 
  else if (L->cursor != NULL) 
  {
    L->cursor = L->cursor->after;
  }
};

// Insert new element into L.  
//If L is non-empty, insertion takes place before front element
void prepend(List L, int data) 
{
  Node new_Node = newNode(data);

  if (L == NULL) 
  {
    printf("List Error: calling prepend() on NULL List reference\n");
    exit(1);
  }

  if (isEmpty(L)) 
  {
    L->front = new_Node;
    L->back = new_Node;
  } 
  else 
  {
    L->front->before = new_Node;
    new_Node->after = L->front;
    L->front = new_Node;
  }
  L->totalItems++;
};

// Insert new element into L.  
//If L is non-empty, insertion takes place after back element.
void append(List L, int data) 
{
  Node new_Node = newNode(data);

  if (L == NULL) 
  {
    printf("List Error: calling append() on NULL List reference\n");
    exit(1);
  }


  if (isEmpty(L)) 
  {
    L->front = new_Node;
    L->back = new_Node;
  } 
  else 
  {
    L->back->after = new_Node;
    new_Node->before = L->back;
    L->back = new_Node;
  }
  L->totalItems++;
};

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data) 
{
  Node new_Node = newNode(data);

  if (L == NULL) 
  {
    printf("List Error: calling insertBefore() on NULL List reference\n");
    exit(1);
  }

  if (isEmpty(L)) 
  {
    printf("List Error: calling insertBefore() on an empty List\n");
    exit(1);
  }

  if (index(L) < 0) 
  {
    printf("List Error: calling insertBefore() on NULL cursor reference\n");
    exit(1);
  }

  if (L->cursor->before == NULL) 
  {
    L->cursor->before = new_Node;
    new_Node->after = L->cursor;
    L->front = new_Node;
  } 
  else 
  {
    Node C = L->cursor->before;
    L->cursor->before = new_Node;
    C->after = new_Node;
    new_Node->after = L->cursor;
    new_Node->before = C;
  }
  L->totalItems++;
};

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data) 
{
  Node new_Node = newNode(data);

  if (L == NULL) 
  {
    printf("List Error: calling insertAfter() on NULL List reference\n");
    exit(1);
  }

  if (isEmpty(L)) 
  {
    printf("List Error: calling insertAfter() on an empty List\n");
    exit(1);
  }

  if (index(L) < 0) 
  {
    printf("List Error: calling insertAfter() on NULL cursor reference\n");
    exit(1);
  }

  if (L->cursor->after == NULL) 
  {
    L->cursor->after = new_Node;
    new_Node->before = L->cursor;
    L->back = new_Node;
  } 
  else 
  {
    Node C = L->cursor->after;
    L->cursor->after = new_Node;
    C->before = new_Node;
    new_Node->before = L->cursor;
    new_Node->after = C;
  }
  L->totalItems++;
};

// Delete the front element. 
//Pre: length()>0
void deleteFront(List L) 
{
  if (L == NULL) 
  {
    printf("List Error: calling deleteFront() on NULL List reference\n");
    exit(1);
  }

  if (isEmpty(L)) 
  {
    printf("List Error: calling deleteFront() on an empty List\n");
    exit(1);
  }

  Node C = L->front;

  if (length(L) == 1) 
  {
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    freeNode(&C);
  } 
  else if (index(L) == 0) 
  {
    L->cursor = NULL;
    L->front = L->front->after;
    L->front->before = NULL;
    freeNode(&C);
  } 
  else 
  {
    L->front = L->front->after;
    L->front->before = NULL;
    freeNode(&C);
  }
  L->totalItems--;
};

// Delete the backelement. 
//Pre: length()>0
void deleteBack(List L) 
{
  if (L == NULL) 
  {
    printf("List Error: calling deleteBack() on NULL List reference\n");
    exit(1);
  }

  if (isEmpty(L)) 
  {
    printf("List Error: calling deleteBack() on an empty List\n");
    exit(1);
  }

  Node C = L->back;

  if (length(L) == 1) 
  {
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    freeNode(&C);
  } 
  else if (index(L) == (L->totalItems - 1)) 
  {
    L->cursor = NULL;
    L->back = L->back->before;
    L->back->after = NULL;
    freeNode(&C);
  } 
  else 
  {
    L->back = L->back->before;
    L->back->after = NULL;
    freeNode(&C);
  }

  L->totalItems--;
};

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete (List L) 
{
  if (L == NULL) 
  {
    printf("List Error: calling delete() on NULL List reference\n");
    exit(1);
  }

  if (isEmpty(L)) 
  {
    printf("List Error: calling delete() on an empty List\n");
    exit(1);
  }

  if (index(L) < 0) 
  {
    printf("List Error: calling delete() on NULL cursor reference\n");
    exit(1);
  }

  Node C = L->cursor;
  Node Prev = L->cursor->before;
  Node Next = L->cursor->after;

  if (length(L) == 1) 
  {
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    freeNode(&C);
  } 
  else if (index(L) == (L->totalItems - 1)) 
  {
    L->cursor = NULL;
    L->back = L->back->before;
    L->back->after = NULL;
    freeNode(&C);
  } 
  else if (index(L) == 0) 
  {
    L->cursor = NULL;
    L->front = L->front->after;
    L->front->before = NULL;
    freeNode(&C);
  } 
  else 
  {
    L->cursor = NULL;
    Prev->after = Next;
    Next->before = Prev;
    freeNode(&C);
  }
  L->totalItems--;
};

// Other operations

void printList(FILE *out, List L) 
{
  if (L == NULL) 
  {
    printf("List Error: calling printList() on NULL List reference\n");
    exit(1);
  }

  for (Node I = L->front; I != NULL; I = I->after) 
  {
    if (I != NULL) 
    {
      fprintf(out, "%d ", (I->data));
    }
  }
};

List copyList(List L) 
{
  if (L == NULL) 
  {
    printf("List Error: calling copyList() on NULL List reference\n");
    exit(1);
  }

  List C = newList();

  Node n = L->front;

  while (n != NULL) 
  {
    append(C, (n->data));
    n = n->after;
  }
  return C;
};