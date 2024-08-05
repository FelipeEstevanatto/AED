/**
 * Binary Search Tree
 * Search, Insertion and Delete are O(log n) time complexity at best and average case, and O(n) at worst case.
 */

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *newNode(int data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

// function to search a key in a BST
struct Node* search(struct Node* root, int key)
{
    // Base Cases: root is null or key is
    // present at root
    if (root == NULL || root->data == key)
        return root;

    // Key is greater than root's key
    if (root->data < key)
        return search(root->right, key);

    // Key is smaller than root's key
    return search(root->left, key);
}

struct Node *insert(struct Node *node, int data)
{
    if (node == NULL) return newNode(data);

    if (data < node->data) 
        node->left = insert(node->left, data);
    else
        node->right = insert(node->right, data);

    return node;
}

// Find the inorder successor
struct Node *minValueNode(struct Node *node) {
  struct Node *current = node;

  // Find the leftmost leaf
  while (current && current->left != NULL)
    current = current->left;

  return current;
}

// Remove a node from the tree
struct Node *delete(struct Node *node, int data)
{
    if (node == NULL) return node;

    // Find the node to be deleted
    if (data < node->data)
        node->left = delete(node->left, data);
    else if (data > node->data)
        node->right = delete(node->right, data);
    else {
        // If node has one child or no child
        if (node->left == NULL) {
            struct Node *temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == NULL) {
            struct Node *temp = node->left;
            free(node);
            return temp;
        }

        // Node has two children
        struct Node *temp = node->right;
        while (temp->left != NULL) temp = temp->left;

        // Place the inorder successor in position of the node to be delete
        node->data = temp->data;

        // Delete the inorder successor
        node->right = delete(node->right, temp->data);
    }

    return node;
}

void inorder(struct Node *node)
{
    if (node != NULL) {
        inorder(node->left);
        printf("%d ", node->data);
        inorder(node->right);
    }
}

int main()
{
    struct Node *root = NULL;

    root = insert(root, 50);
    insert(root, 30);
    insert(root, 40);
    insert(root, 70);
    insert(root, 20);

    delete(root, 30);

    printf("Inorder traversal of the given tree: ");
    inorder(root);

    return 0;
}