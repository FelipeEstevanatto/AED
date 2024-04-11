#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000000

// Average complexity: O(n^2)
// Worst case complexity: O(n^2)

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
    executionTime = clock();
    int currentIndex, currentValue;
    for (int sortedIndex = 1; sortedIndex < arraySize; sortedIndex++) {
        currentIndex = sortedIndex - 1;
        currentValue = array[sortedIndex];
    
        while (currentIndex >= 0 && currentValue < array[currentIndex]) {
            array[currentIndex + 1] = array[currentIndex];
            currentIndex--;
        }
        array[currentIndex + 1] = currentValue;
    }

    executionTime = clock() - executionTime;
    printf("Tempo de execucao: %lf ms\n", ((double)executionTime) / ((CLOCKS_PER_SEC / 1000)));
    
    free(vetor);
    return 0;
}