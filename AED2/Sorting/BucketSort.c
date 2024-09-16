#include <stdio.h>
#include <stdlib.h>

/**
 * Basically, the bucket sort algorithm works as follows:
 * We divide the array into buckets
 * We sort the elements of each bucket
 * We merge the buckets
 * 
 * Time complexity: O(n^2) worst case, O(n+k) best case, where k is the number of buckets
 * Space complexity: O(n)
 * Stable
 */

// Function to find the maximum value in the array
int getMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// Function to find the minimum value in the array
int getMin(int arr[], int size) {
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

// Function to perform insertion sort on an array
void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Function to perform bucket sort
void bucketSort(int arr[], int size) {
    if (size <= 0) return;

    int min = getMin(arr, size);
    int max = getMax(arr, size);

    int bucketSize = 5;
    int bucketCount = (max - min) / bucketSize + 1;

    // Allocate memory for buckets
    int** buckets = (int**)malloc(bucketCount * sizeof(int*));
    int* bucketIndex = (int*)malloc(bucketCount * sizeof(int));

    for (int i = 0; i < bucketCount; i++) {
        buckets[i] = (int*)malloc(size * sizeof(int));
        bucketIndex[i] = 0;
    }

    // Distribute array elements into buckets
    for (int i = 0; i < size; i++) {
        int bucket = (arr[i] - min) / bucketSize;
        buckets[bucket][bucketIndex[bucket]++] = arr[i];
    }

    // Sort individual buckets and concatenate the result
    int index = 0;
    for (int i = 0; i < bucketCount; i++) {
        insertionSort(buckets[i], bucketIndex[i]);
        for (int j = 0; j < bucketIndex[i]; j++) {
            arr[index++] = buckets[i][j];
        }
        free(buckets[i]); // Free memory for each bucket
    }

    // Free allocated memory
    free(buckets);
    free(bucketIndex);
}

int main() {

    int arr[] = {5, 2, 4, 6, 1, 3};
    int size = 6;

    bucketSort(arr, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}