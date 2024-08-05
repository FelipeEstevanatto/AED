/**
 * Red Black Tree
 * Self-Balancing is provided by painting each node with two colors(Red or Black).
 * When the Tree is modified, a new tree is subsequently rearranged and repainted.
 * It requires 1 bit of color information for each node in the tree.
 * Time complexity: O(logn).
 * 
 * 1 - Root is always black.
 * 2 - All NULL leaves are black, and both children of a red node are black.
 * 3 - Every simple path from a given node to any of its descendant leaves contains the same number of black nodes.
 * 4 - Path from root to farthest leaf is no more than twice as long as the path from the root to nearest leaf.
 * 5 - Time complexity: O(logn).
 * 
 * Searchs are slower and AVL trees, but insertions and deletions are faster (less rotating).
 * An Red Black tree CAN be a valid AVL tree
 */

#include <stdio.h>
#include <stdlib.h>

enum Color { RED, BLACK };

struct Node {
    int data;
    enum Color color;
    struct Node *left, *right, *parent;
};

struct Node *newNode(int data) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->color = RED;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;

    return node;
}

// Function to perform left rotation
struct Node *leftRotate(struct Node *node) {
    struct Node *rightChild = node->right;
    node->right = rightChild->left;

    if (rightChild->left != NULL) {
        rightChild->left->parent = node;
    }

    rightChild->parent = node->parent;

    if (node->parent == NULL) {
        node = rightChild;
    } else if (node == node->parent->left) {
        node->parent->left = rightChild;
    } else {
        node->parent->right = rightChild;
    }

    rightChild->left = node;
    node->parent = rightChild;

    return rightChild;
}

// Function to perform right rotation
struct Node *rightRotate(struct Node *node) {
    struct Node *leftChild = node->left;
    node->left = leftChild->right;

    if (leftChild->right != NULL) {
        leftChild->right->parent = node;
    }

    leftChild->parent = node->parent;

    if (node->parent == NULL) {
        node = leftChild;
    } else if (node == node->parent->left) {
        node->parent->left = leftChild;
    } else {
        node->parent->right = leftChild;
    }

    leftChild->right = node;
    node->parent = leftChild;

    return leftChild;
}

// Function to fix the red-red violation
struct Node *fixViolation(struct Node *root, struct Node *node) {
    struct Node *parent = NULL;
    struct Node *grandParent = NULL;

    while ((node != root) && (node->color != BLACK) && (node->parent->color == RED)) {
        parent = node->parent;
        grandParent = node->parent->parent;

        // Case A: Parent is the left child of Grandparent
        if (parent == grandParent->left) {
            struct Node *uncle = grandParent->right;

            // Case 1: The uncle of node is also red
            if (uncle != NULL && uncle->color == RED) {
                grandParent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandParent;
            } else {
                // Case 2: node is the right child of its parent
                if (node == parent->right) {
                    node = parent;
                    leftRotate(node);
                }

                // Case 3: node is the left child of its parent
                parent->color = BLACK;
                grandParent->color = RED;
                rightRotate(grandParent);
            }
        } else { // Case B: Parent is the right child of Grandparent
            struct Node *uncle = grandParent->left;

            // Case 1: The uncle of node is also red
            if (uncle != NULL && uncle->color == RED) {
                grandParent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandParent;
            } else {
                // Case 2: node is the left child of its parent
                if (node == parent->left) {
                    node = parent;
                    rightRotate(node);
                }

                // Case 3: node is the right child of its parent
                parent->color = BLACK;
                grandParent->color = RED;
                leftRotate(grandParent);
            }
        }
    }

    root->color = BLACK;
    return root;
}

// Function to insert a node in the tree
struct Node *insert(struct Node *root, int data) {
    struct Node *node = newNode(data);

    if (root == NULL) {
        node->color = BLACK;
        return node;
    }

    struct Node *current = root;
    struct Node *parent = NULL;

    while (current != NULL) {
        parent = current;

        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    node->parent = parent;

    if (data < parent->data) {
        parent->left = node;
    } else {
        parent->right = node;
    }

    return fixViolation(root, node);
}

// Function to fix double black violation
void fixDoubleBlack(struct Node *root, struct Node *node) {
    if (node == root) return;

    struct Node *sibling = NULL;
    struct Node *parent = node->parent;

    if (node == parent->left) {
        sibling = parent->right;
    } else {
        sibling = parent->left;
    }

    if (sibling == NULL) {
        fixDoubleBlack(root, parent);
    } else {
        if (sibling->color == RED) {
            parent->color = RED;
            sibling->color = BLACK;
            if (sibling == parent->left) {
                rightRotate(parent);
            } else {
                leftRotate(parent);
            }
            fixDoubleBlack(root, node);
        } else {
            if ((sibling->left != NULL && sibling->left->color == RED) || 
                (sibling->right != NULL && sibling->right->color == RED)) {
                if (sibling->left != NULL && sibling->left->color == RED) {
                    if (sibling == parent->left) {
                        sibling->left->color = sibling->color;
                        sibling->color = parent->color;
                        rightRotate(parent);
                    } else {
                        sibling->left->color = parent->color;
                        rightRotate(sibling);
                        leftRotate(parent);
                    }
                } else {
                    if (sibling == parent->left) {
                        sibling->right->color = parent->color;
                        leftRotate(sibling);
                        rightRotate(parent);
                    } else {
                        sibling->right->color = sibling->color;
                        sibling->color = parent->color;
                        leftRotate(parent);
                    }
                }
                parent->color = BLACK;
            } else {
                sibling->color = RED;
                if (parent->color == BLACK) {
                    fixDoubleBlack(root, parent);
                } else {
                    parent->color = BLACK;
                }
            }
        }
    }
}

// Function to replace a node with its child
void replaceNode(struct Node *node, struct Node *child) {
    if (node->parent == NULL) {
        node = child;
    } else {
        if (node == node->parent->left) {
            node->parent->left = child;
        } else {
            node->parent->right = child;
        }
    }
    if (child != NULL) {
        child->parent = node->parent;
    }
}

// Function to delete a node from the tree
void removeNode(struct Node **root, int data) {
    struct Node *node = *root;
    struct Node *toDelete = NULL;
    struct Node *child = NULL;

    while (node != NULL) {
        if (data == node->data) {
            toDelete = node;
            break;
        } else if (data < node->data) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    if (toDelete == NULL) return;

    if (toDelete->left == NULL || toDelete->right == NULL) {
        if (toDelete->left != NULL) {
            child = toDelete->left;
        } else {
            child = toDelete->right;
        }
        replaceNode(toDelete, child);
        if (toDelete->color == BLACK) {
            if (child != NULL && child->color == RED) {
                child->color = BLACK;
            } else {
                fixDoubleBlack(*root, child);
            }
        }
        free(toDelete);
    } else {
        struct Node *successor = toDelete->right;
        while (successor->left != NULL) {
            successor = successor->left;
        }
        toDelete->data = successor->data;
        removeNode(&(toDelete->right), successor->data);
    }
}

// Function to print the tree in-order
void inorder(struct Node *node) {
    if (node == NULL) return;

    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

int main() {
    struct Node *root = NULL;

    root = insert(root, 7);
    root = insert(root, 3);
    root = insert(root, 18);
    root = insert(root, 10);
    root = insert(root, 22);
    root = insert(root, 8);
    root = insert(root, 11);
    root = insert(root, 26);

    printf("In-order before deletion: ");
    inorder(root);
    printf("\n");

    removeNode(&root, 18);

    printf("In-order after deletion: ");
    inorder(root);
    printf("\n");

    return 0;
}