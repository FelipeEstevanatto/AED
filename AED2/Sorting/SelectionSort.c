#include <stdio.h>

/**
 * Basically, the selection sort algorithm works as follows:
 * We loop through the array and select the smallest element.
 * Then we swap the smallest element with the first element of the array.
 * We repeat the process for the remaining elements.
 * Example:
 * [0] - 3, [1] - 2, [2] - 1, [3] - 5, [4] - 4
 * [0] - 1, [1] - 2, [2] - 3, [3] - 5, [4] - 4
 * [0] - 1, [1] - 2, [2] - 3, [3] - 5, [4] - 4
 * [0] - 1, [1] - 2, [2] - 3, [3] - 4, [4] - 5
 * Time complexity: O(n^2) all cases
 * Space complexity: O(1)
 * Not stable
 */

void selectionSort(int arr[], int size) {
    for (int index = 0; index < size - 1; index++) {
        int minIndex = index;
        for (int searchIndex = index + 1; searchIndex < n; searchIndex++) {
            if (arr[searchIndex] < arr[minIndex]) {
                minIndex = searchIndex;
            }
        }
        int temp = arr[index];
        arr[index] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

int main() {

    int arr[] = {5, 2, 4, 6, 1, 3};
    int size = 6;

    selectionSort(arr, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}