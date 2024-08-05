#include <stdio.h>

/**
 * Basically, the quicksort is a divide and conquer algorithm too
 * We start by selecting a pivot element from the array (usually the last element)
 * Then we partition the array in a way that all elements smaller than the pivot are on the left
 * And all elements greater than the pivot are on the right
 * We repeat the process for the left and right subarrays
 * Then we have the original array sorted
 * 
 * Time complexity: O(n log n) best and average case, O(n^2) worst case
 * Space complexity: O(log n)
 * Not stable
 */

void swap(int* p1, int* p2)
{
    int temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int partition(int arr[], int low, int high)
{
    // choose the pivot
    int pivot = arr[high];

    // Index of smaller element and Indicate
    // the right position of pivot found so far
    int index = low - 1;

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            // Increment index of smaller element
            index++;
            swap(&arr[index], &arr[j]);
        }
    }
    swap(&arr[index + 1], &arr[high]);
    return (index + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // pi is the partition return index of pivot
        int pi = partition(arr, low, high);

        // Recursion Call
        // smaller element than pivot goes left and
        // higher element goes right
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {

    int arr[] = {5, 2, 4, 6, 1, 3};
    int size = 6;

    quickSort(arr, 0, size - 1);

    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}