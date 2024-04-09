// ATIVIDADE PRÁTICA 5 - TEMPO DE CLIENTES NA FILA
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
 
typedef struct Node {
  int value; // Valor do tempo de atendimento
  int id;    // Identificador do cliente
  struct Node *next;
} Node;
 
typedef struct Queue {
  Node *front; // Começo da fila
  Node *rear;  // Fim da fila
} Queue;
 
void initializeQueue(Queue *queue) {
  queue->front = NULL;
  queue->rear = NULL;
}
 
bool isEmpty(Queue *queue) {
  return queue->front == NULL && queue->rear == NULL;
}
 
// Insere no final da fila
void insert(Queue *queue, int value, int id) {
  Node *temp = malloc(sizeof(Node));
  if (temp == NULL)
    printf("ERRO ABSURDO");
 
  temp->value = value;
  temp->id = id;
  temp->next = NULL;
  if (isEmpty(queue)) {
    queue->front = temp;
  } else {
    queue->rear->next = temp;
  }
  queue->rear = temp;
}
 
// Remove o primeiro da fila
void removeFirst(Queue *queue) {
  if (queue->front == NULL)
    return;
  Node *aux = queue->front;
 
  queue->front = queue->front->next;
  free(aux);
}
 
// Busca um valor da pdentro da fila
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
 
// Imprime fila
void printfQueue(Queue *queue) {
  Node *temp = queue->front;
  while (temp != NULL) {
    printf("%d ", temp->id);
    temp = temp->next;
  }
}
 
int main(void) {
  // 1 <= clientes <= 1023, 1 <= atendentes <= 25
  int quantClientes = 0, atendentes = 0;
  scanf("%d %d", &quantClientes, &atendentes);
 
  // Inicialização das filas
  Queue filaAtendentes[atendentes];
  Queue filaClientes;
  int tempoAtendimento[atendentes];
  for (int i = 0; i < atendentes; i++) {
    initializeQueue(&filaAtendentes[i]);
    tempoAtendimento[i] = 0;
  }
  initializeQueue(&filaClientes);
 
  // Preenchimento de tempo de atendimento 0 - 1000
  int valor;
  for (int i = 0; i < quantClientes; i++) {
    scanf("%d", &valor);
    insert(&filaClientes, valor, i + 1);
  }
 
  // Organização dos clientes nas filas dos atendentes
  Node *temp = filaClientes.front;
  while (temp != NULL) {
    // Busca o atendente com menor tempo de atendimento
    int menor = INT_MAX;
    int index = 0;
    for (int i = 0; i < atendentes; i++) {
      if (tempoAtendimento[i] < menor) {
        menor = tempoAtendimento[i];
        index = i;
      }
 
      if (menor == 0)
        break;
    }
    tempoAtendimento[index] += temp->value;
 
    // Insere o cliente na fila do atendente com menor tempo de atendimento
    insert(&filaAtendentes[index], temp->value, temp->id);
    temp = temp->next;
    removeFirst(&filaClientes);
  }
 
  // Imprime as filas dos atendentes
  for (int i = 0; i < atendentes; i++) {
    printf("%d : ", i + 1);
    printfQueue(&filaAtendentes[i]);
    printf("\n");
  }
 
  // Free memory and exit
  for (int i = 0; i < atendentes; i++) {
    deQueue(&filaAtendentes[i]);
  }
  deQueue(&filaClientes);
 
  return 0;
}