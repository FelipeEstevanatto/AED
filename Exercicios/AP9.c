#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define MAX_SIZE 1024
 
typedef struct Node {
    char name[MAX_SIZE];
    struct Node *child;
    struct Node *sibling;
    struct Node *parent;
} Node;
 
Node *createNode(char name[MAX_SIZE]) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->child = NULL;
    newNode->sibling = NULL;
    newNode->parent = NULL;
    return newNode;
}
 
Node *search(Node *root, char nameSearch[MAX_SIZE]) {
    if (root == NULL) {
		return NULL;
	}
    Node *aux;

	if (strcmp(root->name, nameSearch) == 0) {
		return root;
	}
	if (root->name[0] == '\\') {
        aux = search(root->child, nameSearch);
    
        if (aux != NULL) {
            return aux;
        }
    }
    while (root->sibling != NULL) {
        root = root->sibling;
        if (strcmp(root->name, nameSearch) == 0)
            return root;
    
        if (root->name[0] == '\\') {
            aux = search(root->child, nameSearch);
            if (aux != NULL)
            return aux;
        }
    }

    return NULL;
}

int insertNode(Node *raiz, char nodeName[MAX_SIZE], char parentName[MAX_SIZE]) {
    Node *parent = search(raiz, parentName);
    if (parent == NULL)
        return 0;
 
    Node *newchild = createNode(nodeName);
    newchild->parent = parent;
 
    if (parent->child == NULL) {
        parent->child = newchild;
    } else {
        Node *current = parent->child;
        while (current->sibling != NULL) {
            current = current->sibling;
        }
        current->sibling = newchild;
    }
 
    return 1;
}

void removeNode(Node *root, char name[MAX_SIZE]) {
    Node *nodeToRemove = search(root, name);
    if (nodeToRemove == NULL || nodeToRemove->parent == NULL)
        return;
 
    Node *parentOfRemove = nodeToRemove->parent;
    
    if (parentOfRemove->child == nodeToRemove) {
        parentOfRemove->child = nodeToRemove->sibling;
    } else {
        Node *current = parentOfRemove->child;
        while (current->sibling != NULL && current->sibling != nodeToRemove) {
            current = current->sibling;
        }
        if (current->sibling == nodeToRemove) {
            current->sibling = nodeToRemove->sibling;
        }
    }
    free(nodeToRemove);
}

// Print path of a node
void printPath(Node *nodeSearch) {
    if (nodeSearch == NULL) {
        printf("Arquivo nao encontrado!\n");
        return;
    }
    while (nodeSearch != NULL) {
        printf("%s ", nodeSearch->name);
        nodeSearch = nodeSearch->parent;
    }
}

void freeTree(Node *node) {
    if (node == NULL) {
        return;
    }
    freeTree(node->child);
    freeTree(node->sibling);
    free(node);
}

int main() {
    Node *root = createNode("\\root");
    int nOfOperations;
    char searchFile[MAX_SIZE];
    
    // Read input
    scanf("%d", &nOfOperations);
    scanf("%s", searchFile);
    getchar();
    
    char operation[3], name[MAX_SIZE], parentName[MAX_SIZE];
 
    // Perform operations
    for (int i = 0; i < nOfOperations; i++) {
        scanf("%s %s", operation, name);
 
        if (operation[1] == 'a' || operation[1] == 'm') {
            scanf(" %s", parentName);
        }
        Node *node1 = NULL, *node2 = NULL;
        switch (operation[1]) {
            case 'a': {
                node1 = search(root, parentName);
                if (node1 != NULL)
                    insertNode(root, name, parentName);
                break;
            }
            case 'r': {
                node1 = search(root, name);
                if (node1 != NULL)
                    removeNode(root, name);
                break;
            }
            case 'm': {
                node1 = search(root, name);
                node2 = search(root, parentName);
                if (node1 != NULL && node2 != NULL) {
                    removeNode(root, name);
                    insertNode(root, name, parentName);
                }
                break;
            }
        }
    }
 
    Node *nodeSearch = search(root, searchFile);
    printPath(nodeSearch);

    freeTree(root);

    return 0;
}