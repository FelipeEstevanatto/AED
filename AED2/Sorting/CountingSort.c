#include <stdio.h>

/**
 * Basically, the countingSort is a sorting algorithm that sorts the elements of an array by counting the number of occurrences of each unique element in the array
 * and storing the count of each element in an auxiliary array by mapping its value as an index and it's count as a quantity
 * 
 * Because of that, it only works for positive integers
 * 
 * We first find the maximum element in the input array and create a count array of size max + 1 to store the count of each element
 * 
 * Time complexity: O(n + k) where n is the number of elements in the input array and k is the range of the input
 * Space complexity: O(n + k)
 * Stable
 */

void countingSort(int arr[], int size) {
    int output[size];
    int max = arr[0];

    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    // Create the count array and initialize it with 0
    int count[max + 1];

    for (int i = 0; i <= max; i++) {
        count[i] = 0;
    }

    // Store the count of each element
    for (int i = 0; i < size; i++) {
        count[arr[i]]++;
    }

    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = size - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = output[i];
    }
}

int main() {

    int arr[] = {5, 2, 4, 6, 1, 3};
    int size = 6;

    countingSort(arr, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}