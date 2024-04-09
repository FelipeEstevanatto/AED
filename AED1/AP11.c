// ATIVIDADE PRÁTICA 10 - Lista de Adjacência em Grafos
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int vertices;
    int **adjMatrix;
} Graph;

Graph initializeGraph(int vertices) {
    Graph graph;
    graph.vertices = vertices;

    graph.adjMatrix = (int **)malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; i++) {
        graph.adjMatrix[i] = (int *)calloc(vertices, sizeof(int));
    }

    return graph;
}

void insertEdge(Graph *graph, int source, int destiny) {
    graph->adjMatrix[source][destiny] = 1;
}

int main(void) {

    int startVertice, totalVertices, totalEdges;

    scanf("%d", &startVertice);
    scanf("%d %d", &totalVertices, &totalEdges);

    Graph graph = initializeGraph(totalVertices);

    for (int i = 0; i < totalEdges; i++) {
        int source, destiny;
        scanf("%d %d", &source, &destiny);
        insertEdge(&graph, source, destiny);
    }

    // print all adjacents of startVertice  
    for (int i = 0; i < totalVertices; i++) {
        if (graph.adjMatrix[startVertice][i] == 1) {
            printf("%d ", i);
        }
    }

    return 0;
}