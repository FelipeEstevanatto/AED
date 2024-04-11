#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000000

int main() {
    FILE *arquivo;
    int* vetor = malloc(MAX * sizeof(int));
    int tamanho = 0;
    clock_t executionTime;
    if (vetor == NULL) {
        perror("Erro ao alocar memoria");
        return 0;
    }

    arquivo = fopen("./dados_semi_ordenados.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 0;
    }

    while (!feof(arquivo) && tamanho < MAX) {
        fscanf(arquivo, "%d", &vetor[tamanho]);
        tamanho++;
    }

    fclose(arquivo);

    executionTime = clock();
    int j, aux;
    for (int i = 1; i < tamanho; i++) {
        j = i - 1;
        aux = vetor[i];

        while (j >= 0 && aux < vetor[j]) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = aux;
    }

    executionTime = clock() - executionTime;
    printf("Tempo de execucao: %lf ms\n", ((double)executionTime) / ((CLOCKS_PER_SEC / 1000)));
    
    free(vetor);
    return 0;
}