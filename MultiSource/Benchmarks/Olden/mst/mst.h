/* For copyright information, see olden_v1.0/COPYRIGHT */

#include <stdlib.h>
#include "hash.h"
#define MAXPROC 1

#include "safe_mm_checked.h"

#define chatting printf
extern int NumNodes;

typedef struct vert_st {
  int mindist;
  mm_array_ptr<struct vert_st> next;
  Hash edgehash;
};

typedef mm_array_ptr<struct vert_st> Vertex;

typedef struct graph_st {
  Vertex vlist[MAXPROC];
};

typedef mm_ptr<struct graph_st> Graph;

Graph MakeGraph(int numvert, int numproc);
int dealwithargs(int argc, char *argv[]);

int atoi(const char *);
