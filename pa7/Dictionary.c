/****************************************************************************************
*  Cole Watts
*  comwatts
*  PA7
*  Dictionary.c
*  Client program for Dictionary ADT
*****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "Dictionary.h"

typedef struct NodeObj
{
    struct NodeObj *rightNode;
    struct NodeObj *leftNode;
    struct NodeObj *parentNode;

    KEY_TYPE key;
    VAL_TYPE value;
    char *color;

} NodeObj;

typedef NodeObj *Node;

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

typedef struct DictionaryObj
{
    int size;
    int unique;

    Node current;
    Node root;
    Node nil;
    
} DictionaryObj;

Dictionary newDictionary(int unique)
{
    Dictionary D = malloc(sizeof(DictionaryObj));

    D->size = 0;
    D->unique = unique;
 
    D->nil = newNode(KEY_UNDEF, VAL_UNDEF);
    D->current = D->nil;
    D->root = D->nil;
    D->nil->color = "b";

    return D;
}

void freeNode(Node *pN)
{
    if (pN == NULL)
    {
        printf("Error: Node pN is NULL\n");
        exit(EXIT_FAILURE);
    }
}

Node Search(Dictionary D, Node x, KEY_TYPE k)
{
    if (D == NULL)
    {
        printf("Error: Dictionary D is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (x < 0)
    {
        printf("Error: Node x is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (x == D->nil || KEY_CMP(x->key, k) == 0)
    {
        return x;
    }
    else if (KEY_CMP(k, x->key) < 0)
    {
        return Search(D, x->leftNode, k);
    }
    else
    {
        return Search(D, x->rightNode, k);
    }
}

Node Max(Dictionary D, Node x)
{
    if (D == NULL)
    {
        printf("Error: Dictionary D is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (x < 0)
    {
        printf("Error: Node x is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (x != D->nil)
    {
        while (x->rightNode != D->nil)
        {
            x = x->rightNode;
        }
    }
    return x;
}

Node Min(Dictionary D, Node x)
{
    if (D == NULL)
    {
        printf("Error: Dictionary D is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (x < 0)
    {
        printf("Error: Node x is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (x != D->nil)
    {
        while (x->leftNode != D->nil)
        {
            x = x->leftNode;
        }
    }
    return x;
}

Node Latter(Dictionary D, Node x)
{
    if (D == NULL)
    {
        printf("Error: Dictionary D is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (x < 0)
    {
        printf("Error: Node x is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (x == D->nil)
    {
        return D->nil;
    }
    else if (x->rightNode != D->nil)
    {
        x = Min(D, x->rightNode);
        return x;
    }
    else
    {
        Node y = x->parentNode;
        while (y != D->nil && x == y->rightNode)
        {
            x = y;
            y = y->parentNode;
        }
        return y;
    }
}

Node Former(Dictionary D, Node x)
{
    if (D == NULL)
    {
        printf("Error: Dictionary D is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (x < 0)
    {
        printf("Error: Node x is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (x == D->nil)
    {
        return D->nil;
    }

    else if (x->leftNode != D->nil)
    {
        x = Max(D, x->leftNode);
        return x;
    }

    else
    {
        Node y = x->parentNode;
        while (x == y->leftNode)
        {
            x = y;
            y = y->parentNode;
        }
        return y;
    }
}

void freeDictionary(Dictionary *pD)
{
    if (pD == NULL)
    {
        printf("Error: Dictionary pD is NULL\n");
        exit(EXIT_FAILURE);
    }
}

int getUnique(Dictionary D)
{
    if (D == NULL)
    {
        printf("Error: Dictionary D is NULL\n");
        exit(EXIT_FAILURE);
    }

    return D->unique;
}

int size(Dictionary D)
{
    if (D == NULL)
    {
        printf("Error: Dictionary D is NULL\n");
        exit(EXIT_FAILURE);
    }

    return D->size;
}

void Transplant(Dictionary D, Node u, Node v)
{
    if (D == NULL)
    {
        printf("Error: Dictionary D is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (u < 0)
    {
        printf("Error: Node u is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (v < 0)
    {
        printf("Error: Node v is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (u->parentNode == D->nil)
    {
        D->root = v;
    }
    else if (u == u->parentNode->leftNode)
    {
        u->parentNode->leftNode = v;
    }
    else
    {
        u->parentNode->rightNode = v;
    }
    v->parentNode = u->parentNode;
}

VAL_TYPE lookup(Dictionary D, KEY_TYPE k)
{
    if (D == NULL)
    {
        printf("Error: Dictionary D is NULL\n");
        exit(EXIT_FAILURE);
    }

    Node n = Search(D, D->root, k);

    if (n == D->nil)
    {
        return VAL_UNDEF;
    }

    return n->value;
}

void delete (Dictionary D, KEY_TYPE k)
{
    if (D == NULL)
    {
        printf("Error: Dictionary D is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (lookup(D, k) == VAL_UNDEF)
    {
        printf("ERROR: Cannot delete() non-existent key.\n");
        exit(EXIT_FAILURE);
    }

    Node searchNode = Search(D, D->root, k);
    Node x = NULL;

    if (searchNode == D->current)
    {
        D->current = D->nil;
    }

    Node newNode = searchNode;

    if (searchNode->leftNode == D->nil)
    {
        x = searchNode->rightNode;
        Transplant(D, searchNode, searchNode->rightNode);
    }

    else if (searchNode->rightNode == D->nil)
    {
        x = searchNode->leftNode;
        Transplant(D, searchNode, searchNode->leftNode);
    }

    else
    {
        newNode = Min(D, searchNode->rightNode);
        x = newNode->rightNode;

        if (newNode->parentNode == searchNode)
        {
            x->parentNode = newNode;
        }
        else
        {
            Transplant(D, newNode, newNode->rightNode);

            newNode->rightNode = searchNode->rightNode;
            newNode->rightNode->parentNode = newNode;
        }
        
        Transplant(D, searchNode, newNode);

        newNode->leftNode = searchNode->leftNode;
        newNode->leftNode->parentNode = newNode;
    }

    D->size -= 1;
}

void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v)
{
    if (D == NULL)
    {
        printf("Error: Dictionary D is NULL\n");
        exit(EXIT_FAILURE);
    }
    if (getUnique(D) == 1)
    {
        if (lookup(D, k) != VAL_UNDEF)
        {
            printf("ERROR: Cannot insert same key.\n");
            exit(EXIT_FAILURE);
        }
    }

    Node nilNode = D->nil;
    Node rootNode = D->root;
    Node z = newNode(k, v);
    
    while (rootNode != D->nil)
    {
        nilNode = rootNode;
        if (KEY_CMP(z->key, rootNode->key) < 0)
        {
            rootNode = rootNode->leftNode;
        }
        else
        {
            rootNode = rootNode->rightNode;
        }
    }
    z->parentNode = nilNode;

    if (nilNode == D->nil)
    {
        D->root = z;
    }
    else if (KEY_CMP(z->key, nilNode->key) < 0)
    {
        nilNode->leftNode = z;
    }
    else
    {
        nilNode->rightNode = z;
    }
    z->leftNode = D->nil;
    z->rightNode = D->nil;
    D->size += 1;
}

void makeEmpty(Dictionary D)
{
    if (D == NULL)
    {
        printf("Error: Dictionary D is NULL\n");
        exit(EXIT_FAILURE);
    }

    while (D->root != D->nil)
    {
        delete (D, D->root->key);
    }
}

VAL_TYPE currentVal(Dictionary D)
{
    if (D == NULL)
    {
        printf("Error: Dictionary D is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (D->current == D->nil)
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

    if (D->current == D->nil)
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

    if (D->current == D->nil)
    {
        return currentVal(D);
    }

    D->current = Former(D, D->current);

    return currentVal(D);
}

VAL_TYPE next(Dictionary D)
{
    if (D == NULL)
    {
        printf("Error: Dictionary D is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (D->current == D->nil)
    {
        return currentVal(D);
    }

    D->current = Latter(D, D->current);

    return currentVal(D);
}

VAL_TYPE beginReverse(Dictionary D)
{
    if (D == NULL)
    {
        printf("Error: Dictionary D is NULL\n");
        exit(EXIT_FAILURE);
    }

    D->current = Max(D, D->root);

    return currentVal(D);
}

VAL_TYPE beginForward(Dictionary D)
{
    if (D == NULL)
    {
        printf("Error: Dictionary D is NULL\n");
        exit(EXIT_FAILURE);
    }

    D->current = Min(D, D->root);

    return currentVal(D);
}

void printDictionary(FILE *out, Dictionary D, const char *ord)
{
    if (D == NULL)
    {
        printf("Error: Dictionary D is NULL\n");
        exit(EXIT_FAILURE);
    }

}