// ATIVIDADE PRÁTICA 6 - COMPRESSÃO DE DADOS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char letter;
  int counter;
  struct Node *next;
  struct Node *previous;
} Node;

typedef struct List {
  Node *front; // Começo da fila
  Node *tail;  // Fim da fila
} List;

void initializeLinkedList(List *list) {
  list->front = NULL;
  list->tail = NULL;
}

bool isEmpty(List *list) {
  if (list->front == NULL && list->tail == NULL)
    return true;
  else
    return false;
}

// Insere no final da fila
void insert(List *list, char letter, int counter) {
  Node *temp = malloc(sizeof(Node));

  // Inicializar alores
  temp->letter = letter;
  temp->counter = counter;
  temp->previous = NULL;
  temp->next = NULL;

  if (isEmpty(list)) {
    list->front = temp;
  } else {
    temp->previous = list->tail;
    list->tail->next = temp;
  }
  list->tail = temp;
}

// Imprime fila
void printfLinkedList(List *list) {
  Node *temp = list->front;
  while (temp != NULL) {
    printf("%d%c\n", temp->counter, temp->letter);
    temp = temp->next;
  }
}

// Remove Node from list
void removeNode(List *list, Node *node) {
  if (node == NULL)
    return;

  // Está na frente
  if (node == list->front) {
    list->front = node->next;
    if (list->front != NULL)
      list->front->previous = NULL;
    
  } // esta no final
  else if (node == list->tail) {
    list->tail = node->previous;
    if (list->tail != NULL)
      list->tail->next = NULL;

  } // esta no meio
  else {
    node->previous->next = node->next;
    node->next->previous = node->previous;
  }
  free(node);
}

// Limpa a fila
void freeLinkedList(List *list) {
  if (isEmpty(list))
    return;

  Node *aux = list->front;
  while (aux != NULL) {
    aux = list->front->next;
    free(list->front);
    list->front = aux;
  }
}

char* parseQueueToString(char *string, List *list) {
  Node *temp = list->front;
  while (temp != NULL) {
    char tempString[10];
    snprintf(tempString, sizeof(tempString), "%d%c", temp->counter, temp->letter);
    strncat(string, tempString, sizeof(tempString));
    temp = temp->next;
  }
  return string;
}

int main(void) {
  // Entrada de 2 até 1023 apenas de maiusculas
  char string[1024];
  scanf("%[^\n]", string);

  List *linkedList = malloc(sizeof(List));
  initializeLinkedList(linkedList);

  // Conta a quantidade de letras iguais e insere na fila
  int i = 0;
  while (string[i] != '\0') {
    int counter = 1;
    while (string[i] == string[i + 1]) {
      counter++;
      i++;
    }
    insert(linkedList, string[i], counter);
    i++;
  }

  // Allocate memory for string and set to 0
  char *compressedString = calloc(2048, sizeof(char));
  compressedString = parseQueueToString(compressedString, linkedList);
  // Linha 1 e 2
  printf("%d\n", strlen(compressedString));
  puts(compressedString);

  // Remove noise from the list
  Node *temp = linkedList->front;
  while (temp != NULL) {
    if (temp->counter == 1) {
      // If the node is the first one
      if (temp->previous == NULL && temp->next != NULL) {
        if (temp->next->counter > 1) {
          temp->next->counter++;
          temp = temp->next;
          removeNode(linkedList, temp->previous);
        }
      } // If the node is the last one
      else if (temp->next == NULL && temp->previous != NULL) {
        if (temp->previous->counter > 1) {
          temp->previous->counter++;
          temp = temp->previous;
          removeNode(linkedList, temp->next);
        }
      } // If the node is in the middle
      else {
        if (temp->previous->counter > 1) {
          // next is bigger than previous (>1)
          if (temp->next->counter > temp->previous->counter) {
            temp->next->counter++;
            temp = temp->previous;
            removeNode(linkedList, temp->next);
          } // next > 1 but smaller than previous
          else if (temp->next->counter > 1) {
            temp->previous->counter++;
            temp = temp->previous;
            removeNode(linkedList, temp->next);
          }
        } else if (temp->next->counter > 1) {
          // previous is bigger than next (>1)
          if (temp->previous->counter > temp->next->counter) {
            temp->previous->counter++;
            temp = temp->previous;
            removeNode(linkedList, temp->next);
          } // previous > 1 but smaller than next
          else if (temp->previous->counter > 1) {
            temp->next->counter++;
            temp = temp->next;
            removeNode(linkedList, temp->previous);
          }
        }
      }
    } 
    temp = temp->next;
  };

  char *compressedWithoutNoise = calloc(2048, sizeof(char));
  compressedWithoutNoise = parseQueueToString(compressedWithoutNoise, linkedList);

  // Linha 3 e 4
  printf("%d\n", strlen(compressedWithoutNoise));
  puts(compressedWithoutNoise);

  // Libera a fila
  freeLinkedList(linkedList);
  free(linkedList);
  free(compressedString);
  free(compressedWithoutNoise);

  return 0;
}