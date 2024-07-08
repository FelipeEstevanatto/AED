#include <stdio.h>
#include <stdlib.h>

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

MinHeap* createMinHeap(int capacity) {
    MinHeap *heap = (MinHeap *) malloc(sizeof(MinHeap));
    heap->nodes = (HeapNode *) malloc(capacity * sizeof(HeapNode));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyDown(MinHeap *heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    
    if (left < heap->size && heap->nodes[left].value < heap->nodes[smallest].value)
        smallest = left;
    
    if (right < heap->size && heap->nodes[right].value < heap->nodes[smallest].value)
        smallest = right;
    
    if (smallest != idx) {
        swap(&heap->nodes[idx], &heap->nodes[smallest]);
        heapifyDown(heap, smallest);
    }
}

void heapifyUp(MinHeap *heap, int idx) {
    int parent = (idx - 1) / 2;
    
    if (idx && heap->nodes[idx].value < heap->nodes[parent].value) {
        swap(&heap->nodes[idx], &heap->nodes[parent]);
        heapifyUp(heap, parent);
    }
}

void insertHeap(MinHeap *heap, HeapNode node) {
    heap->nodes[heap->size] = node;
    heap->size++;
    heapifyUp(heap, heap->size - 1);
}

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
    
    for (int j = 0; j < nOfSequences; j++) {
        int size;
        scanf("%d", &size);
        sizes[j] = size;
        vectors[j] = (int *) malloc(size * sizeof(int));
        for (int k = 0; k < size; k++) {
            scanf("%d", &vectors[j][k]);
        }
        if (size > 0) {
            HeapNode node = {vectors[j][0], j, 0};
            insertHeap(heap, node);
        }
    }
    
    for (int iter = 1; iter <= iterations; iter++) {
        if (iter == iterations) {
            int *remainingValues = (int *) malloc(heap->size * sizeof(int));
            for (int j = 0; j < heap->size; j++) {
                remainingValues[j] = heap->nodes[j].value;
            }
            // Sort the remaining values
            for (int j = 0; j < heap->size - 1; j++) {
                for (int k = j + 1; k < heap->size; k++) {
                    if (remainingValues[j] > remainingValues[k]) {
                        int temp = remainingValues[j];
                        remainingValues[j] = remainingValues[k];
                        remainingValues[k] = temp;
                    }
                }
            }
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
    
    for (int j = 0; j < nOfSequences; j++) {
        free(vectors[j]);
    }
    free(vectors);
    free(sizes);
    free(heap->nodes);
    free(heap);
    
    return 0;
}
