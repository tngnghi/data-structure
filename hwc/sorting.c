#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*SortAlgorithm)(int[], int);

void selectionSort(int arr[], int n, int i) {
    int minIndex = i;
    if (i >= n - 1) {
        return;
    }
    else {
        for (int j = i + 1; j < n; j++) {
            if (arr[j]<= arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
        selectionSort(arr, n, i+1);
    }
}

void bubbleSort(int arr[], int n, int sortedIndex) {
    if (sortedIndex <=1) {
        return;
    }
    else {
        for (int i = 0; i < sortedIndex - 1; i++) {
            if (arr[i] > arr[i+1]) {
                int temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
            }
            
        }
        bubbleSort(arr, n, sortedIndex - 1);
    }
}

void insertionSort(int arr[], int n, int key) {
    if (key >= n) {
        return;
    }
    else {
        int key_val = arr[key];
        int j = key - 1;
        while (j >= 0 && arr[j] > key_val) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        
        arr[j + 1] = key_val;
        insertionSort(arr, n, key + 1);
    }
}

void selectionSort_wrapper(int arr[], int n) {
    printf("Sorting using: Recursive Selection Sort\n");
    selectionSort(arr, n, 0); 
}

void bubbleSort_wrapper(int arr[], int n) {
    printf("Sorting using: Recursive Bubble Sort\n");
    bubbleSort(arr, n, n); 
}

void insertionSort_wrapper(int arr[], int n) {
    printf("Sorting using: Recursive Insertion Sort\n");
    insertionSort(arr, n, 1); 
}

void printArray(int arr[], int size) {
    printf("Sorted Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int data[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(data) / sizeof(data[0]);
    int choice;
    
    SortAlgorithm chosenSort = NULL; 

    printf("Original Array: 64, 34, 25, 12, 22, 11, 90\n");
    printf("Select a sorting algorithm:\n");
    printf("1. Selection Sort\n");
    printf("2. Bubble Sort\n");
    printf("3. Insertion Sort\n");
    printf("Enter choice (1 or 2 or 3): ");
    
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    switch (choice) {
        case 1:
            chosenSort = selectionSort_wrapper;
            break;
        case 2:
            chosenSort = bubbleSort_wrapper;
            break;
        case 3:
            chosenSort = insertionSort_wrapper;
            break;
        default:
            printf("Invalid choice. Exiting.\n");
            return 1;
    }

    if (chosenSort != NULL) {
        int arr_copy[n];
        memcpy(arr_copy, data, n * sizeof(int)); 

        chosenSort(arr_copy, n);
        printArray(arr_copy, n);
    }

    return 0;
}