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

// Counting sort for strings
void countingSort(char arr[][MAX_STRING], char output[][MAX_STRING], int arrSize, int index) {
    int count[CHAR_RANGE]; // 26 letters + 1 for spaces
    for (int i = 0; i < CHAR_RANGE; i++) {
        count[i] = 0;
    }

    // Count the occurrence of each character at position index
    int idx;
    for (int j = 0; j < arrSize; j++) {
        if (arr[j][index] == ' ') {
            idx = 0; // Use the first position for spaces
        } else {
            idx = tolower(arr[j][index]) - CHAR_OFFSET + 1; // Letters start from index 1
        }
        count[idx]++;
    }

    // Calculate the cumulative count
    for (int j = 1; j < CHAR_RANGE; j++) {
        count[j] += count[j - 1];
    }
    // Cumulativo de ESPAÇO até a-z
    printf("%d ", count[0]);
    for (int j = 1; j < CHAR_RANGE; j++) {
        printf("%d ", count[j]);
    }
    printf("\n");
    // Loop the input array in reverse order
    for (int j = arrSize - 1; j >= 0; j--) {
        if (arr[j][index] == ' ') {
            idx = 0;
        } else {
            idx = tolower(arr[j][index]) - CHAR_OFFSET + 1;
        }
        strcpy(output[count[idx] - 1], arr[j]);
        count[idx]--;
    }
}

void radixSort(char arr[][MAX_STRING], int arrSize, int maxLen) {
    char output[arrSize][MAX_STRING];

    // Start from the last character and move to the first
    for (int i = maxLen - 1; i >= 0; i--) {
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
    int maxLen = getMaxLen(names, nOfNames);

    // fill the strings with spaces
    for (int i = 0; i < nOfNames; i++) {
        for (int j = strlen(names[i]); j < maxLen; j++) {
            names[i][j] = ' ';
        }
        names[i][maxLen] = '\0';
    }

    int searchIndex, limit;
    scanf("%d", &searchIndex);
    scanf("%d", &limit);

    radixSort(names, nOfNames, maxLen);

    for (int i = searchIndex - 1; i < searchIndex + limit - 1; i++) {
        char lowerName[256];
        strcpy(lowerName, names[i]);
        for(int j = 0; lowerName[j]; j++){
            lowerName[j] = tolower(lowerName[j]);
        }
        printf("%s\n", lowerName);
    }

    return 0;
}