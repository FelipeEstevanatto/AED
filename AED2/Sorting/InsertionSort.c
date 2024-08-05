#include <stdio.h>

/**
 * Basically, the insertion sort algorithm works as follows:
 * We start with the second element (assuming the first is sorted)
 * Compare the current element with the previous elements
 * If the current element is smaller, we shift the previous elements to the right
 * We repeat the process until the current element is greater than the previous element
 * 
 * Time complexity: O(n^2) worst case, O(n) best case
 * Space complexity: O(1)
 * Stable
 */

void insertionSort(int arr[], int size) {
    for (int iter = 1; iter < size; iter++) {
        int currentValue = arr[iter];
        int currentIndex = iter - 1;

        while (currentIndex >= 0 && arr[currentIndex] > currentValue) {
            arr[currentIndex + 1] = arr[currentIndex];
            currentIndex--;
        }

        arr[currentIndex + 1] = currentValue;
    }
}

int main() {

    int arr[] = {5, 2, 4, 6, 1, 3};
    int size = 6;

    insertionSort(arr, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}