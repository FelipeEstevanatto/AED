// ATIVIDADE PRÁTICA 10 - Grafo Rede Social
// Deve-se utilizar uma TAD Grafos por Matriz de Adjacência.
// Grafo não direcionado
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 16
#define MAX_VERTICES 1024

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
    graph->adjMatrix[destiny][source] = 1;
}

int searchSecondDregreeFriends(Graph *graph, int personSelected) {
    int vertices = graph->vertices;
    int *firstDegreeFriends = calloc(vertices, sizeof(int));
    int *secondDegreeFriends = calloc(vertices, sizeof(int));
    int countSecondDegreeFriends = 0;

    // Find first-degree friends
    for (int i = 0; i < vertices; i++) {
        if (i != personSelected && graph->adjMatrix[personSelected][i] == 1) {
            firstDegreeFriends[i] = 1;
        }
    }

    // Find second-degree friends through first-degree friends
    for (int i = 0; i < vertices; i++) {
        if (firstDegreeFriends[i]) {
            for (int j = 0; j < vertices; j++) {
                if (j != personSelected && graph->adjMatrix[i][j] == 1 && !firstDegreeFriends[j] && !secondDegreeFriends[j]) {
                    secondDegreeFriends[j] = 1;
                    countSecondDegreeFriends++;
                }
            }
        }
    }

    free(firstDegreeFriends);
    free(secondDegreeFriends);

    return countSecondDegreeFriends;
}

int main() {
    char mainPersonName[MAX_SIZE];
    int totalVertices, totalEdges;
    int numPeople = 0;

    // Read the main person and number of vertices and edges
    scanf("%s", mainPersonName);
    scanf("%d %d", &totalVertices, &totalEdges);

    // Create the graph and the array of people (vertices)
    Graph graph = initializeGraph(totalVertices);
    char people[totalVertices][MAX_SIZE];
    
    for (int i = 0; i < totalEdges; i++) {
        char name1[MAX_SIZE], name2[MAX_SIZE];
        scanf("%s %s", name1, name2);

        int person1 = -1, person2 = -1;
        for (int j = 0; j < numPeople; j++) {
            if (strcmp(people[j], name1) == 0) {
                person1 = j;
            }
            if (strcmp(people[j], name2) == 0) {
                person2 = j;
            }
        }

        if (person1 == -1) {
            strcpy(people[numPeople], name1);
            person1 = numPeople;
            numPeople++;
        }

        if (person2 == -1) {
            strcpy(people[numPeople], name2);
            person2 = numPeople;
            numPeople++;
        }

        insertEdge(&graph, person1, person2);
    }

    int personSelected;
    for (int i = 0; i < totalVertices; i++) {
        if (strcmp(people[i], mainPersonName) == 0) {
            personSelected = i;
            break;
        }
    }

    int secondDegreeFriends = searchSecondDregreeFriends(&graph, personSelected);
    printf("%d\n", secondDegreeFriends);

    // Free the graph and the array of people (vertices)
    for (int i = 0; i < graph.vertices; i++) {
        free(graph.adjMatrix[i]);
    }
    free(graph.adjMatrix);

    return 0;
}
