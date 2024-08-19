#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
O mapa do tesouro é composto por vários caracteres. O “*” (sem as aspas duplas) indica a
posição de João, o “+” (sem as aspas duplas) indica a posição de Pedrinho, o “$” (sem as aspas duplas)
indica onde está o tesouro, espaços em branco indicam caminho livre e qualquer caractere não citado
anteriormente indica uma barreira. Em cada caso de teste, a barreira será representada por um mesmo
caractere e os limites do mapa terão barreiras, ou seja, as bordas do mapa são preenchidas de barreiras.
O pai dos meninos quer saber quem deverá encontrar o tesouro primeiro para um dado mapa
considerando que ambos partem rumo ao tesouro no mesmo instante. Considere que João e Pedrinho
percorrerão, quando houver, caminhos de distâncias mínimas e que ambos se deslocam na mesma
velocidade. A partir de uma dada posição (x,y), sendo x a linha e y a coluna no mapa, cada um dos
irmãos pode se mover para uma de quatro possíveis posições seguintes: (x-1,y), (x,y-1), (x,y+1) e (x+1,y).
Considere também que não há garantia de que o tesouro seja alcançável e os dois filhos podem chegar
ao mesmo tempo.
Entrada
A primeira linha é um número inteiro L (L ≤ 30) indicando o número de linhas do mapa. As
próximas L linhas contém os caracteres do mapa sendo que cada linha é composta por no máximo 80
caracteres.
Saída
A saída será composta por um único número inteiro: imprima 1 se João vencer, imprima 2 se
Pedrinho vencer, imprima 0 se houver empate e -1 se ninguém conseguir alcançar o tesouro.
 */

typedef struct {
    int x, y;
} Position;

#define MAX_LINES 30
#define MAX_COLS 80
#define INF 10000

// Breadth-first search to find the shortest path from start to end in the map
int bfs(char map[MAX_LINES][MAX_COLS], int rows, int cols, Position start, Position end) {
    int visited[MAX_LINES][MAX_COLS];
    int dist[MAX_LINES][MAX_COLS];

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            visited[i][j] = 0;
            dist[i][j] = INF;
        }
    }

    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    dist[start.x][start.y] = 0;
    visited[start.x][start.y] = 1;

    Position queue[MAX_LINES * MAX_COLS];
    int front = 0, back = 0;

    queue[back++] = start;

    // While there are elements in the queue
    while (front < back) {
        Position current = queue[front++];

        // Check all 4 directions
        for (int i = 0; i < 4; ++i) {
            Position next = (Position){current.x + dx[i], current.y + dy[i]};

            // If the next position is out of bounds or is a wall, skip it
            if (next.x < 0 || next.x >= rows || next.y < 0 || next.y >= cols) {
                continue;
            }

            // If the next position is a wall or has already been visited, skip it
            if ((map[next.x][next.y] != '$' && map[next.x][next.y] != '*' && map[next.x][next.y] != '+') || visited[next.x][next.y]) {
                continue;
            }

            visited[next.x][next.y] = 1;
            dist[next.x][next.y] = dist[current.x][current.y] + 1;

            if (next.x == end.x && next.y == end.y) {
                return dist[next.x][next.y];
            }

            queue[back++] = next;
        }
    }

    return INF;
}

int main() {
    int mapLines;

    scanf("%d", &mapLines);

    char map[MAX_LINES][MAX_COLS];
    Position joao, pedrinho, treasure;

    for (int i = 0; i < mapLines; ++i) {
        // Get the input until newline
        scanf(" %[^\n]", map[i]);

        for (int j = 0; j < strlen(map[i]); ++j) {
            if (map[i][j] == '*') {
                joao = (Position){i, j};
            } else if (map[i][j] == '+') {
                pedrinho = (Position){i, j};
            } else if (map[i][j] == '$') {
                treasure = (Position){i, j};
            }
        }
    }

    int joaoDist = bfs(map, mapLines, strlen(map[0]), joao, treasure);
    int pedrinhoDist = bfs(map, mapLines, strlen(map[0]), pedrinho, treasure);

    if (joaoDist == INF && pedrinhoDist == INF) {
        printf("-1\n");
    } else if (joaoDist < pedrinhoDist) {
        printf("1\n");
    } else if (pedrinhoDist < joaoDist) {
        printf("2\n");
    } else {
        printf("0\n");
    }

    return 0;
}
