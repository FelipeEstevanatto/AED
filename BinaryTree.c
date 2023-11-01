// Arvore binária de busca
// Propriedades: Nó com valor e ponteiro para o elemento da esquerda e da direita, árvore tem raiz e tamanho
// Funcionamento: Inserção e busca

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *left, *right;
} Node;

typedef struct Tree {
  Node *root;
  int size; // optional
} Tree;

// Insert node to tree
void insert(Tree *tree, int value) {
  Node *node = (Node *) malloc(sizeof(Node));
  node->value = value;
  node->left = node->right = NULL;
  
  if (tree->root == NULL) {
    tree->root = node;
    tree->size++;
    return;
  }

  Node *current = tree->root;
  // Descend the tree until leaf
  while (1) {
    // If value is less than current node value, go left
    if (value < current->value) {
      if (current->left == NULL) {
        current->left = node;
        tree->size++;
        return;
      }
      current = current->left;
    // If value is greater than current node value, go right
    } else if (value > current->value) {
      if (current->right == NULL) {
        current->right = node;
        tree->size++;
        return;
      }
      current = current->right;
    // If value is equal to current node value, do nothing
    } else {
      free(node);
      return;
    }
  }
}

// Search node in tree
Node* search(Tree *tree, int value) {
  Node *current = tree->root;
  while (current != NULL) {
    if (value < current->value) {
      current = current->left;
    } else if (value > current->value) {
      current = current->right;
    } else {
      return current;
    }
  }
  return NULL;
}

// Print tree
void print(Node *node) {
  if (node == NULL) {
    return;
  }
  print(node->left);
  printf("%d ", node->value);
  print(node->right);
}

int main(void) {

  Tree *tree = malloc(sizeof(Tree));
  tree->root = NULL;
  tree->size = 0;

  insert(tree, 10);
  insert(tree, 5);
  insert(tree, 15);
  insert(tree, 3);
  insert(tree, 7);
  insert(tree, 12);

  print(tree->root);
  printf("\n");

  Node *node = search(tree, 7);
  if (node != NULL) {
    printf("Valor encontrado: %d\n", node->value);
  } else {
    printf("Valor nao encontrado\n");
  }

  node = search(tree, 20);
  if (node != NULL) {
    printf("Valor encontrado: %d\n", node->value);
  } else {
    printf("Valor nao encontrado\n");
  }

  return 0;
}