#define INF -1
#define NIL 0
#define UNDEF -2
#define WHITE 0
#define GREY 1
#define BLACK 2

#include"List.h"

typedef struct GraphObj* Graph;

// Constructors-Destructors
Graph newGraph(int n);
void freeGraph(Graph* pG);
// Access functions
int getSize(Graph newG);
int getOrder(Graph newG);
int getFinish(Graph newG, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph newG, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getParent(Graph newG, int u); /* Pre: 1<=u<=n=getOrder(G) */
// Manipulation procedures
void addArc(Graph newG, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph newG, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void DFS(Graph newG, List S); /* Pre: length(S)==getOrder(G) */

// Other Functions
void visit(Graph G, List S, int *time, int x);

Graph transpose(Graph newG);
Graph copyGraph(Graph newG);
void printGraph(FILE* out , Graph newG);
