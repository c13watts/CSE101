#define INF -1
#define NIL 0
#define WHITE 0
#define GREY 1
#define BLACK 2

#include"List.h"

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getSource(Graph newG);
int getOrder(Graph newG);
int getSize(Graph newG);
int getParent(Graph newG, int u);
int getDist(Graph newG, int u);
void getPath(List newL, Graph newG, int u);
/*** Manipulation procedures ***/
void addArc(Graph newG, int u, int v);
void addEdge(Graph newG, int u, int v);
void makeNull(Graph newG);
void BFS(Graph newG, int s);
/*** Other operations ***/
void printGraph(FILE* out, Graph newG);