#include <stdio.h>

void insertionSort(int arr[], int n) {
    for (int i= 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j = j - 1;
        }

        arr[j+1] = key;
    }
}

int main() {

    int arr[] = {5, 2, 4, 6, 1, 3};

    insertionSort(arr, 6);

    for (int i = 0; i < 6; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}