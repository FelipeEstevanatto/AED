// ATIVIDIDADE PRÁTICA 4 - AVALIAÇÃO DE EXPRESSÕES
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
int peek(Stack *);

int isOperator(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }

int applyOperator(char op, int a, int b) {
  switch (op) {
  case '+':
    return a + b;
  case '-':
    return a - b;
  case '*':
    return a * b;
  case '/':
	if (b == 0) {
		printf("Invalid Expression\n");
		exit(0);
	}
    return a / b;
  default:
    return 0;
  }
}

int evaluateRPN(char *expression) {
  Stack numbersStack;
  initializeStack(&numbersStack);

  int i = 0, result = 0;
  while (expression[i] != '\0') {
    if (isdigit(expression[i])) {
	  	// convert char to int
      push(&numbersStack, expression[i] - '0');
    } else if (isOperator(expression[i])) {
      int b = pop(&numbersStack);
      int a = pop(&numbersStack);

      result = applyOperator(expression[i], a, b);

      push(&numbersStack, result);
    }
    i++;
  }
  if (numbersStack.size > 1) {
    printf("Invalid Expression\n");
    exit(0);
  }

  return numbersStack.head->value;
}

int main(void) {
  char expression[1024];

  fgets(expression, 1024, stdin);

  printf("%d\n", evaluateRPN(expression));

  return 0;
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
		printf("Out of memory\n");
		exit(0);
	}
  newNode->value = data;
  newNode->next = stack->head;
  stack->head = newNode;
  stack->size++;
}

// Remove last element from the stack
int pop(Stack *stack) {
  if (stack->size == 0) {
    printf("Invalid Expression\n");
    exit(0);
  }
  Node *removeNode = stack->head;
  int value = removeNode->value;
  stack->head = stack->head->next;
  free(removeNode);
  stack->size--;
  return value;
}

// Look at the top of the stack
int peek(Stack *stack) {
  if (stack->size == 0) {
    printf("Invalid Expression\n");
    exit(0);
  } else {
    return stack->head->value;
  }
}
