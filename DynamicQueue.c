// Fila dinâmica
// Funcionamento: FIFO (First in, First out)

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Estrutura de Nó
typedef struct Node {
  int value;
  struct Node *next;
} Node;

typedef struct Queue {
  Node *front; // Começo da fila
  Node *tail;  // Fim da fila
} Queue;

void initializeQueue(Queue *queue) {
  queue->front = NULL;
  queue->tail = NULL;
}

bool isEmpty(Queue *queue) {
  if (queue->front == NULL && queue->tail == NULL)
    return true;
  else
    return false;
}

// Insere no final da fila
void insert(Queue *queue, int value) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL){
    printf("ERROR: Out of memory\n");
    return;
  }

  newNode->value = value;
  newNode->next = NULL;
  if (isEmpty(queue)) {
    queue->front = newNode;
  } else {
    queue->tail->next = newNode;
  }
  queue->tail = newNode;
}

// Imprime fila
void printfQueue(Queue *queue) {
  Node *temp = queue->front;
  while (temp != NULL) {
    printf("%d\n", temp->value);
    temp = temp->next;
  }
}

// Remove o primeiro da fila
void removeFirst(Queue *queue) {
  if (queue->front == NULL)
    return;
  Node *aux = queue->front;

  queue->front = queue->front->next;
  free(aux);
}

// Busca um valor dentro da fila
Node *search(Queue *queue, int value) {
  Node *search = queue->front;
  while (search != NULL) {
    if (search->value == value)
      break;
    else
      search = search->next;
  }

  return search;
}

// Limpa a fila
void deQueue(Queue *queue) {
  if (isEmpty(queue))
    return;

  Node *aux = queue->front;
  while (aux != NULL) {
    aux = queue->front->next;
    free(queue->front);
    queue->front = aux;
  }
}

int main(void) {
  Queue *fila = (Queue *)malloc(sizeof(Queue));
  initializeQueue(fila);

  for (int i = 0; i <= 10; i++) {
    insert(fila, i);
  }
  removeFirst(fila);

  Node *result = search(fila, 9);

  if (result != NULL)
    printf("%d encontrado!\n", result->value);
  else
    printf("Não encontrado!\n");

  printfQueue(fila);
  deQueue(fila);
  free(fila);

  return 0;
}