/* For copyright information, see olden_v1.0/COPYRIGHT */

/* em3d.h - Header file for the electromagnetic problem in 3 dimensions
 *
 * By:  Martin C. Carlisle
 * Date: Feb. 23, 1994
 *
 */

#ifndef EM3D
#define EM3D

void dealwithargs(int argc, char *argv[]);
void printstats(void);
void srand48(long);
long lrand48(void);

#include <stdio.h>
#include <stdlib.h>

#include "safe_mm_checked.h"

#define chatting printf

extern char * min_ptr;
extern char * max_ptr;

extern int n_nodes; /* number of nodes (E and H) */
extern int d_nodes; /* degree of nodes */
extern int local_p; /* percentage of local edges */
#define PROCS 1

#define assert(a) if (!a) {printf("Assertion failure\n"); exit(-1);}

/* mmsafe pointer related typedef */
typedef mm_ptr<struct node_t> node_ptr;
typedef mm_ptr<struct graph_t> graph_ptr;
typedef mm_array_ptr<mm_ptr<struct node_t>> node_ptr_arr;
typedef mm_ptr<struct table_t> table_ptr;

typedef struct node_t {
  double *value;
  mm_ptr<struct node_t> next;
  node_ptr_arr to_nodes; /* array of nodes pointed to */
  /* double **from_values; /1* array of ptrs to vals where data comes from *1/ */
  mm_array_ptr<double *> from_values;
  /* double *coeffs; /1* array of coeffs on edges *1/ */
  mm_array_ptr<double> coeffs;
  int from_count;
  int from_length;
} node_t;

typedef struct graph_t {
  node_ptr e_nodes[PROCS];
  node_ptr h_nodes[PROCS];
} graph_t;

typedef struct table_t {
  node_ptr_arr e_table[PROCS];
  node_ptr_arr h_table[PROCS];
} table_t;

/* Perform 1 step for a nodelist */
void compute_nodes(mm_ptr<node_t> nodelist);
double gen_uniform_double(void);

#endif
