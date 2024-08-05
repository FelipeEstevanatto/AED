#include <stdio.h>

/**
 * Basically, the shell sort is a variation of the insertion sort algorithm
 * 
 * Step 1 − Start
Step 2 − Initialize the value of gap size, say h.
Step 3 − Divide the list into smaller sub-part. Each must have equal intervals to h.
Step 4 − Sort these sub-lists using insertion sort.
Step 5 – Repeat this step 2 until the list is sorted.
 * 
 * Time complexity: O(n^2) worst case, O(n log n) best case
 * Space complexity: O(1)
 * Not stable
 */

void shellSort(int arr[], int size) {
    // Start with a big gap, then reduce the gap
    for (int gap = size / 2; gap > 0; gap /= 2) {
        // Perform a gapped insertion sort for this gap size
        for (int i = gap; i < size; i++) {
            int temp = arr[i];
            int j;
            // Shift earlier gap-sorted elements up until the correct location for arr[i] is found
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            // Put temp (the original arr[i]) in its correct location
            arr[j] = temp;
        }
    }
}

int main() {

    int arr[] = {5, 2, 4, 6, 1, 3};
    int size = 6;

    shellSort(arr, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}