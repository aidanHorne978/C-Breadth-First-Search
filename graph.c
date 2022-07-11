#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "mylib.h"
#include "queue.h"

struct graphrec{
    int capacity;
    struct vertexrec *verticies;
    int **edges;
};

struct vertexrec{
    int predecessor;
    int distance;
    state_t state;
};

graph graph_new(int v){
    int i, j;
    graph result = emalloc(sizeof * result);
    result->capacity = v;
    result->verticies = emalloc(result->capacity * sizeof result->verticies[0]);
    result->edges = emalloc(result->capacity * sizeof result->edges[0]);
    for (i = 0; i < result->capacity; i++){
        result->edges[i] = emalloc(result->capacity *
                                   sizeof result->edges[i][0]);
        for (j = 0; j < result->capacity; j++){
            result->edges[i][j] = 0;
        }
    }
    for (i = 0; i < result->capacity; i++){
        result->verticies[i].state = UNVISITED;
    }
    return result;
}

graph graph_free(graph g){
    int i;
    for (i = 0; i < g->capacity; i++){
        free(g->edges[i]);
    }
    free(g->edges);
    free(g->verticies);
    free(g);
    return g;
}

graph graph_add_edge(graph g, int u, int v){
    g->edges[u][v] = 1;
    return g;
}

graph graph_add_2edges(graph g, int u, int v){
    g->edges[v][u] = 1;
    g->edges[u][v] = 1;
    return g;
}

void graph_print_list(graph g){
   int i;
   int j = 0;
   int count = 0;
   printf("adjacency list:\n");
   for (i = 0; i < g->capacity; i++) {
       printf("%d |", i);
       count = 0;
       for (j = 0; j < g->capacity; j++) {
           if (g->edges[i][j] == 1) {
               if (count == 0) {
                   printf(" %d", j);
                   count++;
               }else {
                   printf(", %d", j);
               }
           }
       }
       printf("\n");
   }
}

void graph_print_state(graph g){
    int i;
    printf("vertex distance pred\n");
    for (i = 0; i < g->capacity; i++){
        printf("%5d %6d %5d\n", i, g->verticies[i].distance,
               g->verticies[i].predecessor);
    }
}

void graph_bfs(graph g, int source){
    int i, u, v;
    queue q = queue_new(g->capacity);

    for (i = 0; i < g->capacity; i++){
        g->verticies[i].distance = -1;
        g->verticies[i].predecessor = -1;
    }
    g->verticies[source].state = VISITED_SELF;
    g->verticies[source].distance = 0;
    enqueue(q, source);
    while (queue_size(q) != 0){
        u = dequeue(q);
        for (v = 0; v < g->capacity; v++){
            if (g->edges[v][u] == 1 && g->verticies[v].state == UNVISITED){
                g->verticies[v].state = VISITED_DESCENDANTS;
                g->verticies[v].distance = 1 + g->verticies[u].distance;
                g->verticies[v].predecessor = u;
                enqueue(q, v);
            }
        
        }
        g->verticies[u].state = VISITED_DESCENDANTS;
    }
    queue_free(q);
}
