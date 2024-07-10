#include <stdio.h>
#include <stdlib.h>

// Node of the heap
typedef struct {
    int value;
    int vector_idx;
    int element_idx;
} HeapNode;

typedef struct {
    HeapNode *nodes;
    int size;
    int capacity;
} MinHeap;

// Create a min heap
MinHeap* createMinHeap(int capacity) {
    MinHeap *heap = (MinHeap *) malloc(sizeof(MinHeap));
    heap->nodes = (HeapNode *) malloc(capacity * sizeof(HeapNode));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Swap two nodes
void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify the heap from the given index
void heapifyDown(MinHeap *heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    
    if (left < heap->size && heap->nodes[left].value < heap->nodes[smallest].value)
        smallest = left;
    
    if (right < heap->size && heap->nodes[right].value < heap->nodes[smallest].value)
        smallest = right;
    
    // If the smallest node is not the current node, swap them and heapify the new node
    if (smallest != index) {
        swap(&heap->nodes[index], &heap->nodes[smallest]);
        heapifyDown(heap, smallest);
    }
}

// Heapify the heap from the given index
void heapifyUp(MinHeap *heap, int index) {
    int parent = (index - 1) / 2;
    
    if (index && heap->nodes[index].value < heap->nodes[parent].value) {
        swap(&heap->nodes[index], &heap->nodes[parent]);
        heapifyUp(heap, parent);
    }
}

// Insert a node in the heap and heapify it up
void insertHeap(MinHeap *heap, HeapNode node) {
    heap->nodes[heap->size] = node;
    heap->size++;
    heapifyUp(heap, heap->size - 1);
}

// Extract the minimum node from the heap and heapify it down
HeapNode extractMin(MinHeap *heap) {
    HeapNode root = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
    return root;
}

int main() {
    int nOfSequences, iterations;
    scanf("%d %d", &nOfSequences, &iterations);
    
    int **vectors = (int **) malloc(nOfSequences * sizeof(int *));
    int *sizes = (int *) malloc(nOfSequences * sizeof(int));
    
    MinHeap *heap = createMinHeap(nOfSequences);
    
    // Read the sequences and insert the first element of each sequence in the heap
    for (int sequenceIndex = 0; sequenceIndex < nOfSequences; sequenceIndex++) {
        int size;
        scanf("%d", &size);
        sizes[sequenceIndex] = size;
        vectors[sequenceIndex] = (int *) malloc(size * sizeof(int));
        for (int k = 0; k < size; k++) {
            scanf("%d", &vectors[sequenceIndex][k]);
        }
        if (size > 0) {
            HeapNode node = {vectors[sequenceIndex][0], sequenceIndex, 0};
            insertHeap(heap, node);
        }
    }
    
    for (int iter = 1; iter <= iterations; iter++) {
        if (iter == iterations) {
            int *remainingValues = (int *) malloc(heap->size * sizeof(int));
            for (int j = 0; j < heap->size; j++) {
                remainingValues[j] = heap->nodes[j].value;
            }
            // Sort the remaining values with a simple bubble sort
            for (int j = 0; j < heap->size - 1; j++) {
                for (int k = j + 1; k < heap->size; k++) {
                    if (remainingValues[j] > remainingValues[k]) {
                        int temp = remainingValues[j];
                        remainingValues[j] = remainingValues[k];
                        remainingValues[k] = temp;
                    }
                }
            }
            // Print the remaining values
            for (int j = 0; j < heap->size; j++) {
                if (j > 0) printf(" ");
                printf("%d", remainingValues[j]);
            }
            printf("\n");
            free(remainingValues);
        }
        
        HeapNode minNode = extractMin(heap);
        
        if (minNode.element_idx + 1 < sizes[minNode.vector_idx]) {
            minNode.element_idx++;
            minNode.value = vectors[minNode.vector_idx][minNode.element_idx];
            insertHeap(heap, minNode);
        }
    }
    
    // Free the allocated memory
    for (int j = 0; j < nOfSequences; j++) {
        free(vectors[j]);
    }
    free(vectors);
    free(sizes);
    free(heap->nodes);
    free(heap);
    
    return 0;
}
