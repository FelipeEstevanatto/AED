// ATIVIDADE PRÁTICA 7 - ARVORE BINÁRIA
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *left, *right;
} Node;

typedef struct Tree {
  Node *root;
} Tree;

// Insert node to tree, 
void insert(Tree *tree, int value) {
  Node *node = (Node *) malloc(sizeof(Node));
  node->value = value;
  node->left = node->right = NULL;
  
  if (tree->root == NULL) {
    tree->root = node;
    return;
  }

  Node *current = tree->root;
  // Descend the tree until leaf
  while (1) {
    // If value is less than current node value, go left
    if (value < current->value) {
      if (current->left == NULL) {
        current->left = node;
        return;
      }
      current = current->left;
    // If value is greater or equal than current node value, go right
    } else if (value >= current->value) {
      if (current->right == NULL) {
        current->right = node;
        return;
      }
      current = current->right;
    // If hell freezes over
    } else {
      free(node);
      return;
    }
  }
}

// Search node in tree, printing the path if found
void search(Tree *tree, int value) {
  Node *path[1024]; // Assuming the tree height will not exceed 1024
  int pathLen = 0;
  Node *current = tree->root;
  while (current != NULL) {
    // Add current node to path
    path[pathLen] = current;
    pathLen++;
    // Navigate tree
    if (value < current->value) {
      current = current->left;
    } else if (value > current->value) {
      current = current->right;
    } else {
      // Print path
      for (int i = 0; i < pathLen; i++) {
        printf("%d ", path[i]->value);
      }
      return;
    }
  }
  printf("-1");
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

// Print tree pre order (ascending order)
void preOrder(Node *node) {
  if (node == NULL) {
    return;
  }
  printf("%d ", node->value);
  preOrder(node->left);
  preOrder(node->right);
}

// Print tree in order (ascending order)
void inOrder(Node *node) {
  if (node == NULL) {
    return;
  }
  inOrder(node->left);
  printf("%d ", node->value);
  inOrder(node->right);
}

// Print tree post order (descending order)
void postOrder(Node *node) {
  if (node == NULL) {
    return;
  }
  postOrder(node->left);
  postOrder(node->right);
  printf("%d ", node->value);
}

// Get height of tree (number of edges in longest path from root to leaf)
int height(Node* node) {
  if (node == NULL) {
    return 0;
  } else {
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
  }
}

int main(void) {

  Tree *tree = malloc(sizeof(Tree));
  tree->root = NULL;

  int numberElements, value, element;
  scanf("%d", &numberElements);
  scanf("%d", &value);

  for (int i = 0; i < numberElements; i++) {
    scanf("%d", &element);
    insert(tree, element);
  }

  // 1º linha - Pré-Ordem
  preOrder(tree->root);
  printf("\n");
  // 2º linha - Em-Ordem
  inOrder(tree->root);
  printf("\n");
  // 3º linha - Pós-Ordem
  postOrder(tree->root);
  printf("\n");
  // 4º linha - Sequência de busca
  search(tree, value);
  printf("\n");
  // 5º linha - Altura da árvore
  printf("%d", height(tree->root)-1);
  printf("\n");

  return 0;
}