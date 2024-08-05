/**
 * AVL(Adelson-Velskii and Landis) Tree implementation
 * 
 * 1 - Height difference of the left and right subtree of the node should be less than 2.
 * 2 - Re-balancing is done when the heights of two child subtrees of a node differ by more than one.
 * 3 - Faster retrievals as strictly balanced.
 */

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int num;
    int height;
    int balance_value;
    struct Node *left;
    struct Node *right;
};

typedef struct Node Node;

Node *newNode(int num)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->num = num;
    node->height = 1;
    node->balance_value = 0;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void fix_height(Node *node)
{
    int left_height = (node->left) ? node->left->height : 0;
    int right_height = (node->right) ? node->right->height : 0;

    node->height = (left_height > right_height ? left_height : right_height) + 1;
    node->balance_value = left_height - right_height;
}

Node *leftRotate(Node *v)
{
    Node *root = v->right;
    v->right = root->left;
    root->left = v;

    // Update heights
    fix_height(v);
    fix_height(root);

    // Return new root
    return root;
}

Node *rightRotate(Node *v)
{
    Node *root = v->left;
    v->left = root->right;
    root->right = v;

    // Update heights
    fix_height(v);
    fix_height(root);

    // Return new root
    return root;
}

// If the balance factor of a node is not between -1 and 1, the tree is unbalanced
int getBalance(Node *node) {
    if (node == NULL) return 0;
    return node->balance_value;
}

// Helper function to handle rotations
Node* balanceNode(Node *node, int num) {
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && num < node->left->num)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && num > node->right->num)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && num > node->left->num) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && num < node->right->num) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Insertion
Node *insert(Node *node, int num)
{
    if (node == NULL) return newNode(num);

    if (num < node->num) 
        node->left = insert(node->left, num);
    else
        node->right = insert(node->right, num);

    fix_height(node);

    return balanceNode(node, num);
}

void inorder(Node *node)
{
    if (node != NULL) {
        inorder(node->left);
        printf("%d ", node->num);
        inorder(node->right);
    }
}

int main()
{
    Node *root = NULL;

    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 20);

    printf("Inorder traversal of the given tree: ");
    inorder(root);

    return 0;
}