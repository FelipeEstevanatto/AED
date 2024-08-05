/**
 * Problem 4: Group Quantities
 * 
 * A store has a list of clients, products and their quantities.
 * The store wants to organize the data in groups and search them.
 * 
 * First input will be the value of m, the number of buckets.
 * The following inputs will be operations:
 * @int operation
 * @char[] name
 * @int quantity
 * 
 * Operation 1: Insert a new quantity for a client
 * Operation 2: Search for a client and return the group of clients and their quantities
 * 
 * TEST 5, 6 and 7 HAVE nOfBuckets = 99999
 * TEST 12 has strings that sum of to 610 characters
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 16

// Node of each customer
typedef struct Node {
    char name[MAX_NAME_LENGTH];
    int *quantities;
    int size;
    // Capacity of the quantities array
    int capacity;
    struct Node* next;
} Node;

// Hash table of customers (buckets)
typedef struct {
    Node** buckets;
    int numBuckets;
} HashTable;


typedef struct SearchResult {
    char* group;
    char* quantities;
    struct SearchResult* next;
} SearchResult;

// List of search results
typedef struct {
    SearchResult* head;
    SearchResult* tail;
} SearchResultList;

// Hash function based on strings converted to numbers (ASCI up to 128)
unsigned long hash(char *string, int constrain) {
    unsigned long hash = 0;
    while (*string)
        hash = (hash * 128 + *string++) % constrain;
    return hash % constrain;
}

Node* createNode(char *name, int quantity) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->quantities = (int*)malloc(2 * sizeof(int));
    newNode->quantities[0] = quantity;
    newNode->size = 1;
    newNode->capacity = 2;
    newNode->next = NULL;
    return newNode;
}

// Insert a quantity in the node
void insertQuantity(Node* node, int quantity) {
    if (node->size == node->capacity) {
        node->capacity *= 2;
        node->quantities = (int*)realloc(node->quantities, node->capacity * sizeof(int));
    }
    node->quantities[node->size++] = quantity;
}

// Create a hash table with a given number of buckets
HashTable* createHashTable(int numBuckets) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->numBuckets = numBuckets;
    table->buckets = (Node**)calloc(numBuckets, sizeof(Node*));

    return table;
}

// Insert or update a node in the hash table
void insertOrUpdate(HashTable* table, char* name, int quantity) {
    unsigned long index = hash(name, table->numBuckets);
    Node* current = table->buckets[index];

    while (current) {
        if (strcmp(current->name, name) == 0) {
            insertQuantity(current, quantity);
            return;
        }
        current = current->next;
    }

    Node* newNode = createNode(name, quantity);
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
}

// Search for a node in the hash table
Node* search(HashTable* table, char* name) {
    unsigned long index = hash(name, table->numBuckets);
    Node* current = table->buckets[index];
    while (current) {
        if (strcmp(current->name, name) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

// Collect the group of names in a given index
void collectGroup(HashTable* table, unsigned long index, char* groupResult) {
    Node* current = table->buckets[index];
    char* names[1000];
    int count = 0;

    while (current != NULL) {
        names[count++] = current->name;
        current = current->next;
    }

    // Sort names in ascending order with bubble sort
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(names[i], names[j]) > 0) {
                char* temp = names[i];
                names[i] = names[j];
                names[j] = temp;
            }
        }
    }

    groupResult[0] = '\0';
    for (int i = 0; i < count; i++) {
        strcat(groupResult, names[i]);
        if (i < count - 1) strcat(groupResult, " ");
    }
}

// Collect the quantities of a node
void collectQuantities(Node* node, char* quantityResult) {
    if (!node) {
        strcpy(quantityResult, "0");
        return;
    }
    
    quantityResult[0] = '\0';
    for (int i = 0; i < node->size; i++) {
        char buf[10];
        sprintf(buf, "%d", node->quantities[i]);
        strcat(quantityResult, buf);
        if (i < node->size - 1) strcat(quantityResult, " ");
    }
}

// Add a search result to the list
void addSearchResult(SearchResultList* results, char* group, char* quantities) {
    SearchResult* newResult = (SearchResult*)malloc(sizeof(SearchResult));
    newResult->group = (char*)malloc(strlen(group) + 1);
    newResult->quantities = (char*)malloc(strlen(quantities) + 1);
    
    strcpy(newResult->group, group);
    strcpy(newResult->quantities, quantities);
    newResult->next = NULL;

    if (results->tail == NULL) {
        results->head = newResult;
    } else {
        results->tail->next = newResult;
    }
    results->tail = newResult;
}

void printSearchResults(SearchResultList* results) {
    SearchResult* current = results->head;
    while (current) {
        printf("%s\n%s\n", current->group, current->quantities);
        current = current->next;
    }
}

void freeHashTable(HashTable* table) {
    for (int i = 0; i < table->numBuckets; i++) {
        Node* current = table->buckets[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp->quantities);
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}

int main() {
    // Read number of buckets (m)
    int nOfBuckets;
    scanf("%d", &nOfBuckets);

    HashTable* table = createHashTable(nOfBuckets);
    SearchResultList results = {NULL, NULL};

    int operation;
    char name[MAX_NAME_LENGTH];
    int quantity;

    while (scanf("%d", &operation) && operation != 0) {
        if (operation == 1) {
            scanf("%s %d", name, &quantity);
            insertOrUpdate(table, name, quantity);
        } else if (operation == 2) {
            scanf("%s", name);
            unsigned long index = hash(name, nOfBuckets);
            char groupResult[MAX_NAME_LENGTH * 610];
            char quantityResult[MAX_NAME_LENGTH * 610];
            collectGroup(table, index, groupResult);
            Node* node = search(table, name);
            collectQuantities(node, quantityResult);
            addSearchResult(&results, groupResult, quantityResult);
        }
    }

    printSearchResults(&results);
    // Free memory
    freeHashTable(table);
    // Free search results
    SearchResult* current = results.head;
    while (current) {
        SearchResult* temp = current;
        current = current->next;
        free(temp->group);
        free(temp->quantities);
        free(temp);
    }

    return 0;
}