// Lista encadeada simples
// Propriedades: Nó com valor e ponteiro para o próximo elemento, Lista tem cabeça e cauda
// Funcionamento: Inserção e remoção de qualquer posição

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *next; // pointer to next element
} Node;

typedef struct LinkedList {
  int size; // optional
  Node *head;
  Node *tail;
} LinkedList;

// Initialize head and size
void initializeLinkedList(LinkedList *list) {
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
}

// Print list from top to bottom
void printLinkedList(LinkedList *list) {
  Node *currentNode = list->head;
  while (currentNode != NULL) {
    printf("Valor: %d\n", currentNode->value);
    currentNode = currentNode->next;
  }
}

// Push data to tail of linked list
void insertTail(LinkedList *list, int data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->value = data;
  newNode->next = NULL;
  if (list->size == 0) {
    list->head = newNode;
    list->tail = newNode;
  } else {
    list->tail->next = newNode;
    list->tail = newNode;
  }
  list->size++;
}

// Push data to head of linked list
void insertHead(LinkedList *list, int data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->value = data;
  newNode->next = list->head;
  list->head = newNode;
  list->size++;
}

// Push data to specific position of linked list
void insertAt(LinkedList *list, int data, int position) {
  if (position < 0 || position > list->size) {
    printf("Invalid position\n");
    return;
  }
  if (position == 0) {
    insertHead(list, data);
    return;
  }
  if (position == list->size) {
    insertTail(list, data);
    return;
  }
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->value = data;
  Node *currentNode = list->head;
  Node *previousNode = NULL;
  for (int i = 0; i < position; i++) {
    previousNode = currentNode;
    currentNode = currentNode->next;
  }
  previousNode->next = newNode;
  newNode->next = currentNode;
  list->size++;
}

// Remove specific element from the list
int removeNode(LinkedList *list, Node *node) {
  if (list->size == 0) {
    return -1;
  }
  Node *currentNode = list->head;
  Node *previousNode = NULL;
  while (currentNode != node) {
    previousNode = currentNode;
    currentNode = currentNode->next;
  }
  if (currentNode == list->head) {
    list->head = currentNode->next;
  } else {
    previousNode->next = currentNode->next;
  }
  free(currentNode);
  list->size--;
  return 1;
}

int main(void) {
  LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
  initializeLinkedList(list);

  for (int i = 0; i <= 5; i++) {
    insertTail(list, i);
  }
  for (int i = 5; i <= 10; i++) {
    insertHead(list, i);
  }

  // Remove the third element (8);
  removeNode(list, list->head->next->next);

  // Insert 8 at the third position
  insertAt(list, 8, 3);

  printLinkedList(list);

  free(list);

  return 0;
}