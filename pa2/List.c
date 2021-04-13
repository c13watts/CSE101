/****************************************************************************************
*  Cole Watts
*  comwatts
*  PA2
*  List.c
*  Implementation file for List ADT
*****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

typedef struct NodeObj{ 
    long data; 
    struct NodeObj* after;
    struct NodeObj* before;
} NodeObj;

typedef NodeObj* Node; Node newNode(long data){
    Node new_Node = malloc(sizeof(NodeObj));
    new_Node->data = data; 
    new_Node->before = NULL;
    return(new_Node);
}

void freeNode(Node* prevNode){
    if(prevNode!= NULL && *prevNode != NULL){
        free(*prevNode);
        *prevNode = NULL; 
    }
}

typedef struct ListObj{
    Node front;  
    Node back;
    Node cursor;  
    int totalItems;
    int index; 

} ListObj; 

List newList(void){
    List L; 
    L = malloc(sizeof(ListObj));
    L-> front = NULL;
    L-> back = NULL;
    L-> cursor = NULL; 
    L-> totalItems = 0; 
    L -> index = -1;
    return L;  
}

void freeList(List* prevList){
    clear(*prevList);
    if(prevList != NULL && *prevList != NULL){
        clear(*prevList);
        free(*prevList);
        *prevList = NULL;
    }     
}

int length(List L){
    if(L== NULL){
        printf("List Error: calling totalItems() on NULL List reference\n");
        exit(1);

    } 
    else if(L-> front == NULL){
        return 0;
    } 
    else{ 
        return L->totalItems; 
    }
}

int index(List L){
    if(L== NULL){
        printf("List Error: calling index() on NULL List reference\n");
        exit(1);

    } 
    else if(L -> cursor != NULL){ 
        return L-> index; 
    } 
    else
        return -1; 
    
} 
long front(List L){
    if(L== NULL){
         printf("List Error: calling front() on NULL List reference\n");
    exit(1);

    } 
    else if(L->totalItems <= 0){
        printf("List Error: calling front() on an empty List\n");
        exit(1);

    } 
    else{
        return L-> front -> data;
    } 
}
long back(List L){
    if(L == NULL){
        printf("List Error: calling back() on NULL List reference\n");
        exit(1);

    } 
    else if(L->totalItems <= 0){
        printf("List Error: calling back() on an empty List\n");
        exit(1);
    }
    else{
        return L-> back -> data;  
    }
}

long get(List L){
    if(L == NULL){
        printf("List Error: calling get() on NULL List reference\n");
        exit(1);

    } 
    else if(length(L)>0 && index(L) >=0){
        return L -> cursor -> data; 
    } 
    else if(length(L) <= 0){
        printf("List Error: calling get() on an empty List\n");
        exit(1);

    } 
    else if(index(L) < 0){
      printf("List Error: calling get() on NULL cursor reference\n");
      exit(1);

    } 
    else{
        exit(1);
    }
} 

void set(List A, long x){
    if(A == NULL){
        printf("Error");
        exit(1);
    }
    else if(A->totalItems <= 0){
        printf("Error");
        exit(1);
    } 
    else if(A->index < 0){
        printf("Error");
        exit(1);
    }
    else{
        A->cursor->data = x;

    }
}
void clear(List L){
    if(L == NULL){
        printf("List Error: calling clear() on NULL List reference\n");
        exit(1);

    } 
    else{ 
        while(L->front != NULL){
            deleteFront(L);
        }
        L -> front = L-> back = L-> cursor = NULL; 
        L -> totalItems = 0;
    } 
}

void moveFront(List L){
    if(L == NULL){
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(1);

    }
    else if(L->totalItems > 0) {
        L->cursor = L->front;
        L-> index = 0; 
    }
} 

void moveBack(List L){
    if(L == NULL){
        printf("List Error: calling moveBack() on NULL List reference\n");
    exit(1);

    }
    else if (L->totalItems >0){
        L->cursor = L->back;
        L-> index = L->totalItems - 1; 
    }
} 

void movePrev(List L){
    if(L == NULL){
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(1);

    } 
    else if(L->cursor != NULL && L->cursor != L->front){
        L->cursor = L->cursor -> after; 
        L -> index --; 
    }
    else if(L->cursor != NULL && L->cursor == L->front){
        L->cursor = NULL;
        L->index = -1;  
    }
}

void moveNext(List L){
    if(L == NULL){
        printf("List Error: calling moveNext() on NULL List reference\n");
        exit(1);

    } 
    else if(L->cursor != NULL && L->cursor != L->back){
        L->cursor = L->cursor -> before; 
        L -> index ++; 
    } 
    else if(L->cursor != NULL && L->cursor == L->back){
        L->cursor = NULL; 
        L->index = -1;
    }
} 

void prepend(List L, long data){
    if(L == NULL){
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(1);

    }

    Node Z = newNode(data);
    if(length(L) == 0){
        L->front = Z;
        L->back = Z;
    } else{
        L->front->after = Z; 
        Z->before = L-> front;
        L->front = Z; 

        if(L->index!= -1){
            L->index++;
        }
    } 
    L->totalItems ++; 

} 

void append(List L, long data){
    if(L == NULL){
        printf("List Error: calling append() on NULL List reference\n");
        exit(1);

    } 
    Node Z = newNode(data);
    if(length(L) == 0){
        L->front = Z;
        L->back = Z;
    } else{
        L->back-> before  = Z; 
        Z->after = L-> back;
        L->back= Z; 
    } 
    L->totalItems ++; 
} 

void insertBefore(List L, long data){
    if(L==NULL){
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(1);

    } 
    if(L->totalItems <=0 ){
        printf("List Error: calling insertBefore() on an empty List\n");
        exit(1);

    } 
    if(L->index < 0 ){
        printf("List Error: calling insertBefore() on NULL cursor reference\n");
        exit(1);

    } 
    else{ 
        Node Z = newNode(data);
        if(L->cursor == L->front){
            L->cursor->after = Z;
            Z->before = L->cursor; 
            L->front = Z; 
        } else{
            Node temp = L-> cursor-> after;
            L->cursor->after = Z; 
            Z->before = L->cursor; 
            Z->after = temp;
            temp->before = Z; 
        }
    }
    L-> index ++; 
    L-> totalItems ++; 
} 

void insertAfter(List L, long data){
    if(L==NULL){
        printf("List Error: calling insertAfter() on NULL List reference\n");
    exit(1);

    } 
    
    if(L->totalItems <=0 ){
        printf("List Error: calling insertAfter() on an empty List\n");
        exit(1);

    } 
    
    if(L->index < 0 ){
        printf("List Error: calling insertAfter() on NULL cursor reference\n");
        exit(1);

    } 
    
    else{
        Node N = newNode(data);
        if(L->cursor == L->back){
            L->cursor->before = N; 
            N->after = L->cursor; 
            L->back = N; 
        } else{
            Node temp = L->cursor->before;
            L->cursor -> before = N; 
            N-> after = L->cursor; 
            N->before = temp;
            temp->after = N;
        }
    }
    L->totalItems ++; 
}

void deleteFront(List L){
    if(L == NULL){
        printf("List Error: calling deleteFront() on NULL List reference\n");
       exit(1);

    }
    else if(length(L) <= 0){
        printf("List Error: calling deleteFront() on an empty List\n");
        exit(1);

    } 
    else{
        Node temp = L->front;
        if(L->totalItems == 1){
            L->front = L->back = NULL;
            L->cursor = NULL;
            L->index = -1;
        } else{
            L->front = L->front->before;
            L->front->after = NULL;
            if(L -> index == 0){
                L -> cursor = NULL;
            }
            L->index--; 
        }
        freeNode(&temp);
        L->totalItems --;    
    } 
}

void deleteBack(List L){
    if(L == NULL){
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(1);

    }
    else if(length(L) <= 0){
        printf("List Error: calling deleteBack() on an empty List\n");
        exit(1);

    }
    else{
        Node temp = L->back;
        if(L-> totalItems == 1){
            L->front = L->back = NULL;
            L->cursor = NULL;
            L->index = -1;
        } else{
            L->back = L->back->after;
            L->back->before = NULL;
            if(L -> cursor == temp){
                L->cursor = NULL; 
                L->index = -1;
            }
        }
        freeNode(&temp);
        L->totalItems--;
    } 
} 

void delete(List L) { 
    if (L == NULL) 
    {
        printf("List Error: calling delete() on NULL List reference\n");
        exit(1);

    }
    if (L->totalItems == 0) {
         printf("List Error: calling delete() on an empty List\n");
         exit(1);

    }
    if (L->index < 0) {
        printf("List Error: calling delete() on NULL cursor reference\n");
        exit(1);

    }
    if (L->index == 0) {
        deleteFront(L);

    } else if (L->index == L->totalItems - 1) {
        deleteBack(L);

    } else {
        Node pastPrev = L->cursor->after;
        Node pastbefore = L->cursor->before;
        pastPrev->before = pastbefore;
        pastbefore->after = pastPrev;

        freeNode(&(L->cursor));

        L->index = -1;
        L->cursor = NULL;
        L->totalItems -= 1;
    }
} 

void printList(FILE* out, List L){
    Node z = NULL;
    if(L==NULL){
        printf("List Error: calling printList() on NULL List reference\n");
        exit(1);
    } else{ 
        for(z = L->front; z != NULL; z = z->before){
            fprintf(out, "%ld ", z->data);
        }
    }
}

List copyList(List L){
    List c = newList();
    Node z = L-> front; 
    while(z != NULL){
        append(c, z->data);
        z= z->before;
    }
    return(c);
} 
