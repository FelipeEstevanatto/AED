#include <stdio.h>
#include <stdbool.h>

/**
 * Basically, the  bubble sort algorithm works as follows:
 * We start by comparing the first two elements
 * If the first element is greater than the second, we swap them
 * We repeat the process for the next two elements and so on
 * This way, the largest element will "bubble" to the end of the array
 * We repeat the process for the remaining elements minus the last one
 * 
 * Time complexity: O(n^2) worst case, O(n) best case
 * Space complexity: O(1)
 * Stable
 */

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int arr[], int size) {
    bool swapped;
    for (int iter = 1; iter < size - 1; iter++) {
        swapped = false;
    
        for (int j = 0; j < size - iter; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;
    }
}

int main() {

    int arr[] = {5, 2, 4, 6, 1, 3};
    int size = 6;

    bubbleSort(arr, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}