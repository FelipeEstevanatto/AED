// Pilha dinâmica
// Funcionamento: LIFO (Last in, First out)

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value;         // stored value
  struct Node *next; // pointer to next element
} Node;

typedef struct Stack {
  int size;
  Node *head; // null if empty
} Stack;

void initializeStack(Stack *);
void push(Stack *, int);
int pop(Stack *);
void peek(Stack *);

// Print stack from top to bottom
void printStack(Stack *stack) {
  Node *nodeAtual = stack->head;
  while (nodeAtual != NULL) {
    printf("Valor: %d\n", nodeAtual->value);
    nodeAtual = nodeAtual->next;
  }
}

// Initialize head and size
void initializeStack(Stack *stack) {
  stack->head = NULL;
  stack->size = 0;
}

// Push data to stack
void push(Stack *stack, int data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL) {
    printf("ERROR: Out of memory\n");
    return;
  }
  newNode->value = data;
  newNode->next = stack->head;
  stack->head = newNode;
  stack->size++;
}

// Remove last element from the stack
int pop(Stack *stack) {
  if (stack->size == 0) {
    return -1;
  }
  Node *removeNode = stack->head;
  stack->head = stack->head->next;
  free(removeNode);
  stack->size--;
  return 1;
}

// Look at the top of the stack
void peek(Stack *stack) {
  if (stack->size == 0) {
    printf("Stack is empty\n");
  } else {
    printf("%d is the top element\n", stack->head->value);
  }
}

int main(void) {
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  initializeStack(stack);

  for (int i = 0; i <= 5; i++) {
    push(stack, i);
  }

  peek(stack);
  pop(stack);
  peek(stack);

  printStack(stack);

  free(stack);

  return 0;
}