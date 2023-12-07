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
    // If value is greater or equal than current node value, go right
    } else {
      if (current->right == NULL) {
        current->right = node;
        tree->size++;
        return;
      }
      current = current->right;
    }
  }
}

// Recursive search node in tree
Node* search(Node* node, int value) {
  if (node == NULL || node->value == value)
    return node;

  if (value < node->value)
    return search(node->left, value);

  return search(node->right, value);
}

// Remove node from tree
void removeNode(Tree *tree, int value) {
  Node *current = tree->root;
  Node *parent = NULL;
  while (current != NULL) {
    if (value < current->value) {
      parent = current;
      current = current->left;
    } else if (value > current->value) {
      parent = current;
      current = current->right;
    } else {
      // Case 1: no children
      if (current->left == NULL && current->right == NULL) {
        if (parent == NULL) {
          tree->root = NULL;
        } else if (parent->left == current) {
          parent->left = NULL;
        } else {
          parent->right = NULL;
        }
        free(current);
        tree->size--;
        return;
      }
      // Case 2: one child
      if (current->left == NULL || current->right == NULL) {
        Node *child = current->left != NULL ? current->left : current->right;
        if (parent == NULL) {
          tree->root = child;
        } else if (parent->left == current) {
          parent->left = child;
        } else {
          parent->right = child;
        }
        free(current);
        tree->size--;
        return;
      }
      // Case 3: two children
      Node *successor = current->right;
      Node *successorParent = current;
      while (successor->left != NULL) {
        successorParent = successor;
        successor = successor->left;
      }
      current->value = successor->value;
      if (successorParent->left == successor) {
        successorParent->left = successor->right;
      } else {
        successorParent->right = successor->right;
      }
      free(successor);
      tree->size--;
      return;
    }
  }
}

// Print tree
void printTree(Node *node, int space) {
  // Base case: if the node is null, don't print anything
  if (node == NULL) {
    return;
  }
  
  // Increase distance between levels
  space += 10;

  // Print right child first (right subtree is on top)
  printTree(node->right, space);

  // Print current node
  // printf the amount of spaces - 10
  printf("%*s", space - 10, " ");
  printf("%d\n", node->value);

  // Print left child
  printTree(node->left, space);
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
  insert(tree, 22);
  insert(tree, 6);
  insert(tree, 6);
  insert(tree, 6);
  insert(tree, 6);
  insert(tree, 6);

  printTree(tree->root, 0);
  printf("\n");

  Node *node = search(tree->root, 7);
  if (node != NULL) {
    printf("Valor encontrado: %d\n", node->value);
  } else {
    printf("Valor nao encontrado\n");
  }

  node = search(tree->root, 20);
  if (node != NULL) {
    printf("Valor encontrado: %d\n", node->value);
  } else {
    printf("Valor nao encontrado\n");
  }

  return 0;
}