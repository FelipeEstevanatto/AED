#include <stdio.h>

/**
 * Basically, the heapsort algorithm works as follows:
 * Almost complete binary tree - until the last level, all levels are completely filled
 * Rules for each A[i] node:
 * Left child: A[2*i + 1]
 * Right child: A[2*i + 2]
 * Father: A[(i-1)/2]
 * 
 * Time complexity: O(n log n) all cases
 * Space complexity: O(1)
 * Not stable
 */

void swap(int* p1, int* p2) {
    int temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

// Ensure the subtree rooted at index i is a max heap (change second > to < for min heap)
void heapify(int arr[], int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // If the left child is larger than the root
    if (left < size && arr[left] > arr[largest]) {
        largest = left;
    }

    // If the right child is larger than the root
    if (right < size && arr[right] > arr[largest]) {
        largest = right;
    }

    // If the largest is not the root
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        // Recursively heapify the affected sub-tree
        heapify(arr, size, largest);
    }
}

void heapSort(int arr[], int size) {
    // Build the heap
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(arr, size, i);
    }

    // Extract elements from the heap
    for (int i = size - 1; i > 0; i--) {
        // Move the root element to the end
        swap(&arr[0], &arr[i]);
        // Heapify the reduced heap
        heapify(arr, i, 0);
    }
}

int main() {

    int arr[] = {5, 2, 4, 6, 1, 3};
    int size = 6;

    heapSort(arr, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}