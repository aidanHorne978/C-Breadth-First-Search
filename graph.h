#ifndef GRAPH_H_
#define GRAPH_H_

typedef enum { UNVISITED, VISITED_SELF, VISITED_DESCENDANTS } state_t;

typedef struct graphrec *graph;

extern graph   graph_new(int v);
extern graph   graph_free(graph g);
extern graph   graph_add_edge(graph g, int u, int v);
extern graph   graph_add_2edges(graph g, int u, int v);
extern void    graph_print_list(graph g);
extern void    graph_print_state(graph g);
extern void   graph_bfs(graph g, int source);

#endif
