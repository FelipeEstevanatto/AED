#include <stdio.h>

/**
 * Basically, the radixSort is a non-comparative integer sorting algorithm that sorts data with integer keys by grouping keys
 * by individual digits which share the same significant position and value
 * 
 * First we find the largert number in the array to know how many digits it has
 * And then we do counting sort for every digit from the least significant to the most significant
 * 
 * Time complexity: O(nk) where n is the number of elements in the input array and k is the number of digits in the largest number
 * Space complexity: O(n + k)
 * Stable
 */

// Function to get the maximum value in the array
int getMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// A function to do counting sort of arr[] according to the digit represented by exp
void countingSort(int arr[], int size, int exp) {
    int output[size]; // Output array
    int count[10] = {0}; // Initialize count array as 0

    // Store count of occurrences in count[]
    for (int i = 0; i < size; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    // Change count[i] so that count[i] contains the actual position of this digit in output[]
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = size - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now contains sorted numbers according to the current digit
    for (int i = 0; i < size; i++) {
        arr[i] = output[i];
    }
}

// The main function to that sorts arr[] of size n using Radix Sort
void radixSort(int arr[], int size) {
    // Find the maximum number to know the number of digits
    int max = getMax(arr, size);

    // Do counting sort for every digit. Note that instead of passing the digit number, exp is passed. exp is 10^i where i is the current digit number
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSort(arr, size, exp);
    }
}

int main() {

    int arr[] = {5, 2, 4, 6, 1, 3};
    int size = 6;

    radixSort(arr, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}