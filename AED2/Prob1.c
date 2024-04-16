/*
O Radix sort, por outro lado, pode ser aplicado para ordenação de strings utilizando o
Counting sort para ordenar a entrada em relação a apenas uma posição das strings por vez,
sendo que cada caractere seria considerado como um “dígito” do algoritmo. Considerando que
strings podem ter comprimentos diferentes, um caractere adicional (espaço em branco ou 32 em
decimal, por exemplo) pode ser utilizado para preencher posições vazias de strings mais curtas,
para que todas strings tenham o mesmo comprimento d (tamanho da maior string).
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING 15
#define CHAR_RANGE 27
#define CHAR_OFFSET 97

int getMaxLen(char arr[][MAX_STRING], int arrSize) {
    int maxLen = 0;
    for (int i = 0; i < arrSize; i++) {
        if (strlen(arr[i]) > maxLen) {
            maxLen = strlen(arr[i]);
        }
    }
    return maxLen;
}

void countingSort(char arr[][MAX_STRING], char output[][MAX_STRING], int arrSize, int index) {
    int *count = (int *)calloc(27, sizeof(int)); // 26 letters + 1 for spaces

    // Count the occurrence of each character at position index
    for (int j = 0; j < arrSize; j++) {
        int idx;
        if (arr[j][index] == ' ') {
            idx = 0; // Use the first position for spaces
        } else {
            idx = arr[j][index] - 'a'; // Letters start from index 1
        }
        printf("AAA: %c %d ", arr[j][index], idx);
        count[idx]++;
    }

    // Calculate the cumulative count
    for (int j = 1; j < 27; j++) {
        count[j] += count[j - 1];
        printf("%c %d ", j, count[j]);
    }
    printf("Espaco: %d ", count[0]);
    //printf("\n");

    // Build the output array
    for (int j = arrSize - 1; j >= 0; j--) {
        int idx;
        if (arr[j][index] == ' ') {
            idx = 0;
        } else {
            idx = arr[j][index] - 'a';
        }
        strcpy(output[count[idx] - 1], arr[j]);
        count[idx]--;
    }

    free(count);
}

void radixSort(char arr[][MAX_STRING], int arrSize, int maxLen) {
    char output[arrSize][MAX_STRING];

    // Start from the last character and move to the first
    for (int i = maxLen; i >= 0; i--) {
        countingSort(arr, output, arrSize, i);

        // Copy the output array to arr so that the next iteration
        // can sort the strings according to the next character
        for (int j = 0; j < arrSize; j++) {
            strcpy(arr[j], output[j]);
        }
    }
}

int main() {

    int nOfNames;

    scanf("%d", &nOfNames);

    char names[nOfNames][MAX_STRING];
    for (int i = 0; i < nOfNames; i++) {
        scanf("%s", names[i]);
    }
    maxLen = getMaxLen(names, nOfNames);

    int searchIndex, limit;
    scanf("%d", &searchIndex);
    scanf("%d", &limit);
    printf("maxLen: %d\n", maxLen);
    radixSort(names, nOfNames, maxLen);

    for (int i = searchIndex - 1; i < searchIndex + limit - 1; i++) {
        for (int j = 0; j < 15; j++) {
            if (names[i][j] != ' ') {
                printf("%c", names[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}