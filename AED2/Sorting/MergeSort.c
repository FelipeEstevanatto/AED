#include <stdio.h>

/**
 * Basically, the mergesort is a divide and conquer algorithm
 * We start by dividing the array into two halves until we have arrays of size 1
 * Then we merge the arrays in a sorted way
 * This works recursively until we have the original array sorted
 * 
 * Time complexity: O(n log n) all cases
 * Space complexity: O(1)
 * Stable
 */

void merge(int arr[], int left, int median, int right) {
    int n1 = median - left + 1;
    int n2 = right - median;

    int leftArr[n1], rightArr[n2];

    // Copy data to temp arrays leftArr[] and rightArr[]
    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightArr[i] = arr[median + 1 + i];
    }

    // Merge the temp arrays back into arr[l..r]
    int i = 0, j = 0, k = left;
    while(i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftArr[], if there are any
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightArr[], if there are any
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // Find the median point to divide the array into two halves
        int median = left + (right - left) / 2;

        // Recursively sort the first and second halves
        mergeSort(arr, left, median);
        mergeSort(arr, median + 1, right);

        merge(arr, left, median, right);
    }
}

int main() {

    int arr[] = {5, 2, 4, 6, 1, 3};
    int size = 6;

    mergeSort(arr, 0, size - 1);

    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}