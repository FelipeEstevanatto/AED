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

#define MAX_STRING_LENGTH 15
#define CHAR_RANGE 27
#define ASCII_OFFSET 97

int getMaxLen(char arr[][MAX_STRING_LENGTH], int arrSize) {
    int maxLen = 0;
    int len;
    for (int i = 0; i < arrSize; i++) {
        len = strlen(arr[i]);
        if (len > maxLen) {
            maxLen = len;
        }
    }
    return maxLen;
}

// Counting sort for strings
void countingSort(char inputArray[][MAX_STRING_LENGTH], char sortedArray[][MAX_STRING_LENGTH], int numberOfNames, int index) {
    int count[CHAR_RANGE]; // 26 letters + 1 for spaces
    for (int i = 0; i < CHAR_RANGE; i++) {
        count[i] = 0;
    }

    // Count the occurrence of each character at position index
    int characterIndex;
    for (int j = 0; j < numberOfNames; j++) {
        if (inputArray[j][index] == ' ') {
            characterIndex = 0; // Use the first position for spaces
        } else {
            characterIndex = tolower(inputArray[j][index]) - ASCII_OFFSET + 1; // Letters start from index 1
        }
        count[characterIndex]++;
    }

    // Calculate the cumulative count
    for (int j = 1; j < CHAR_RANGE; j++) {
        count[j] += count[j - 1];
    }
    // Cumulative of space to a-z
    printf("%d ", count[0]);
    for (int j = 1; j < CHAR_RANGE; j++) {
        printf("%d ", count[j]);
    }
    printf("\n");
    // Loop the input array in reverse order
    for (int j = numberOfNames - 1; j >= 0; j--) {
        if (inputArray[j][index] == ' ') {
            characterIndex = 0;
        } else {
            characterIndex = tolower(inputArray[j][index]) - ASCII_OFFSET + 1;
        }
        strcpy(sortedArray[count[characterIndex] - 1], inputArray[j]);
        count[characterIndex]--;
    }
}

void radixSort(char namesArray[][MAX_STRING_LENGTH], int numberOfNames, int maxLength) {
    char output[numberOfNames][MAX_STRING_LENGTH];

    // Start from the last character and move to the first
    for (int i = maxLength - 1; i >= 0; i--) {
        countingSort(namesArray, output, numberOfNames, i);

        // Copy the output array to arr so that the next iteration
        // can sort the strings according to the next character
        for (int j = 0; j < numberOfNames; j++) {
            strcpy(namesArray[j], output[j]);
        }
    }
}

int main() {

    int numberOfNames;

    scanf("%d", &numberOfNames);

    char names[numberOfNames][MAX_STRING_LENGTH];
    for (int i = 0; i < numberOfNames; i++) {
        scanf("%s", names[i]);
        for(int j = 0; names[i][j]; j++){
            names[i][j] = tolower(names[i][j]);
        }
    }
    int maxLength = getMaxLen(names, numberOfNames);

    // fill the strings with spaces
    for (int i = 0; i < numberOfNames; i++) {
        for (int j = strlen(names[i]); j < maxLength; j++) {
            names[i][j] = ' ';
        }
        names[i][maxLength] = '\0';
    }

    int searchIndex, limit;
    scanf("%d", &searchIndex);
    scanf("%d", &limit);

    radixSort(names, numberOfNames, maxLength);

    for (int i = searchIndex - 1; i < searchIndex + limit - 1; i++) {
        printf("%s\n", names[i]);
    }

    return 0;
}