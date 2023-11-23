// ATIVIDADE PRÁTICA 8 - Criptografia de Dados
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
	char letter;
	int frequency;
	struct Node *left, *right;
} Node;

typedef struct Tree {
	Node *root;
} Tree;

// Insert node to tree, 
void insert(Tree *tree, int frequency, char letter) {
	Node *node = (Node *) malloc(sizeof(Node));
	node->frequency = frequency;
	node->letter = letter;
	node->left = node->right = NULL;
	
	if (tree->root == NULL) {
		tree->root = node;
		return;
	}

	Node *current = tree->root;
	// Descend the tree until leaf
	while (1) {
		// If frequency is less than current node frequency, go left
		if (frequency < current->frequency) {
			if (current->left == NULL) {
				current->left = node;
				return;
			}
			current = current->left;
		// If frequency is greater or equal than current node frequency, go right
		} else {
			if (current->right == NULL) {
				current->right = node;
				return;
			}
			current = current->right;
		}
	}
}

// Print tree in order (ascending order)
void inOrder(Node *node) {
  if (node == NULL) {
    return;
  }
  inOrder(node->left);
  printf("%c", node->letter);
  inOrder(node->right);
}

// Get minimum node from tree
Node* getMinimumNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Remove node from tree
Node* removeNode(Node *root, char letter, int frequency) {
    if (root == NULL) return root;

    if (root->letter == letter && root->frequency == frequency) {
        // If node has no children
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        // If node has one child
        } else if (root->left == NULL) {
            Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node *temp = root->left;
            free(root);
            return temp;
        // If node has two children
        } else {
            Node *temp = getMinimumNode(root->right);
            root->letter = temp->letter;
            root->frequency = temp->frequency;
            root->right = removeNode(root->right, temp->letter, temp->frequency);
        }
    } else if (frequency < root->frequency) {
        root->left = removeNode(root->left, letter, frequency);
    } else {
        root->right = removeNode(root->right, letter, frequency);
    }
    return root;
}

void freeTree(Node *node) {
	if (node == NULL) {
		return;
	}
	freeTree(node->left);
	freeTree(node->right);
	free(node);
}

int main(void) {
	Tree *tree = malloc(sizeof(Tree));
	tree->root = NULL;

	// Encripted string and letters to remove
	char inputString[1025], remove1, remove2;
	int remove [2][2] = {{0, 0}, {0, 0}};
	scanf("%c %c ", &remove[0][0], &remove[0][1]);
	scanf("%s", inputString);

	// Count frequency of each letter
	int frequencyMap[26] = {0};
	for (int i = 0; i < strlen(inputString); i++) {
		frequencyMap[toupper(inputString[i]) - 'A']++;
		if (inputString[i] == remove[0][0]) {
			remove[1][0]++;
		} else if (inputString[i] == remove[0][1]) {
			remove[1][1]++;
		}
	}

	// Insert each letter in tree, assume we only have uppercase chars
	for (int i=0; i < 26; i++) {
		if (frequencyMap[i] > 0) {
			insert(tree, frequencyMap[i], i + 'A' );
		}
	}

	inOrder(tree->root);
	printf("\n");

	// Remove letters
	removeNode(tree->root, remove[0][0], remove[1][0]);
	removeNode(tree->root, remove[0][1], remove[1][1]);

	inOrder(tree->root);
	printf("\n");

	freeTree(tree->root);
	
	return 0;
}