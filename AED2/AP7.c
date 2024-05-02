#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int balance;
    struct Node *left, *right;
} Node;

int height(Node *node);

// Function prototypes
Node *newNode(int item) {
    Node *temp = (Node *) malloc(sizeof(Node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getBalance(Node *N) {
    if (N == NULL) return 0;
    return height(N->left) - height(N->right);
}

int height(Node *node) { 
    if (node == NULL) return 0;
    return 1 + max(height(node->left), height(node->right));
}

Node *rightRotate(Node *unbalancedNode) {   
    Node *newRoot = unbalancedNode->left;
    Node *subTree = newRoot->right;
    newRoot->right = unbalancedNode;
    unbalancedNode->left = subTree;
    return newRoot;
}

Node *leftRotate(Node *unbalancedNode) {
    Node *newRoot = unbalancedNode->right;
    Node *subTree = newRoot->left;
    newRoot->left = unbalancedNode;
    unbalancedNode->right = subTree;
    return newRoot;
}

Node *minValueNode(Node *node) {
    Node *current = node;
    while (current && current->left != NULL) current = current->left;
    return current;
}

Node *deleteNode(Node *root, int key) {
    if (root == NULL) return root;
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            Node *temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    if (root == NULL) return root;
    root->balance = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

// Search for a key in the AVL tree
Node* search(Node *node, int key) {
    if (node == NULL) {
        return NULL;
    }
    if (key < node->key) {
        return search(node->left, key);
    } else if (key > node->key) {
        return search(node->right, key);
    } else {
        return node;
    }
}

Node* insert(Node* node, int key) {
    if (node == NULL) return newNode(key);
    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node;
    }
    node->balance = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

int main() {
    Node *root = NULL;
    int key;
    // Get the numbers to store in the AVL tree
    while (1) {
        scanf("%d", &key);
        if (key < 0) break;
        root = insert(root, key);
    }

    int initialHeight = height(root) - 1;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    // Get the numbers to search in the AVL tree
    // If the number is found, remove it from the tree, if not, insert it
    while (1) {
        scanf("%d", &key);
        if (key < 0) break;
        if (search(root, key) != NULL) {
            root = deleteNode(root, key);
        } else {
            root = insert(root, key);
        }
    }

    scanf("%d", &key);
    // First line: height of the AVL tree, height of the left subtree and height of the right subtree
    printf("%d, %d, %d\n", initialHeight, leftHeight, rightHeight);

    // Second line: Get the last number only to search in the AVL tree and store the height
    // of the AVL tree height of the left subtree and height of the right subtree of this node
    Node *node = search(root, key);
    if (node == NULL) {
        printf("Valor nao encontrado\n");
    } else {
        printf("%d, %d, %d\n", height(node) - 1, height(node->left), height(node->right));
    }

    // Free the memory allocated for the AVL tree
    while (root != NULL) {
        root = deleteNode(root, root->key);
    }

    return 0;
}
