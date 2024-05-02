/**
 * 
 * E N T R A D A:
A primeira linha da entrada consiste de uma lista de numeros inteiros positivos ´
separados por espac¸os. Esses numeros devem ser inseridos na ´ arvore. A sequ ´ encia ˆ
termina com um numero inteiro negativo que n ´ ao deve ser inserido. ˜
A segunda linha contem outra lista de n ´ umeros inteiros positivos separados por ´
espac¸os. Assim como na lista da primeira linha, um numero inteiro negativo marca o ´
final da lista. Cada um desses numeros, com excec¸ ´ ao do n ˜ umero negativo, deve-se ser ´
1
usado como chave de pesquisa na arvore. No caso de uma pesquisa sem sucesso, ou ´
seja, o numero n ´ ao est ˜ a na ´ arvore, o n ´ umero pesquisado dever ´ a ser inserido na ´ arvore. ´
Se a pesquisa for bem sucedida, ou seja, o numero est ´ a na ´ arvore, o n ´ umero dever ´ a ser ´
removido.
A terceira linha contem um ´ unico valor inteiro positivo a ser apenas ´ pesquisado na
arvore. Esse n ´ umero pode ou n ´ ao estar na ˜ arvore. ´
S A ´I D A:
A primeira linha da sa´ıda contem a altura m ´ axima da ABB a partir do seu n ´ o raiz ´
seguida da altura da sub-arvore da esquerda e da direita do n ´ o raiz. Esses valores ´
devem ser calculados considerando apenas a arvore constru ´ ´ıda com os numeros da ´
primeira linha da entrada.
Na segunda linha, deve ser impresso o valor da altura do no pesquisado (linha 03 ´
dos dados de entrada), seguido pela altura da sub-arvore da esquerda e direita. Caso ´
esse valor pesquisado nao seja encontrado, deve ser exibido ”Valor nao encontrado”

Implemente as operac¸oes b ˜ asicas de um algoritmo de pesquisa para ´ arvores do ´
tipo AVL. Seu programa deve conter os seguintes procedimentos: (1) inicializac¸ao, (2) ˜
pesquisa, (3) inserc¸ao, (4) remoc¸ ˜ ao e (5) calcular altura do n ˜ o. Para isso, considere: ´
• Na operac¸ao de remoc¸ ˜ ao, quando necess ˜ ario, d ´ e a prefer ˆ encia para a promoc¸ ˆ ao˜
da menor chave da subarvore ´ a direita, ou seja, o sucessor; `
• A altura de um no´ x em uma AVL e dada pela dist ´ ancia entre ˆ x e o seu descendente mais afastado, ou seja, a altura de x e o n ´ umero de passos no mais longo ´
caminho que leva x ate um n ´ o folha.

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

Node *newNode(int item) {
    Node *temp = (Node *) malloc(sizeof(Node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

Node *insert(Node *node, int key) {
    if (node == NULL) return newNode(key);
    if (key < node->key) node->left = insert(node->left, key);
    else if (key > node->key) node->right = insert(node->right, key);
    return node;
}

Node *minValueNode(Node *node) {
    Node *current = node;
    while (current && current->left != NULL) current = current->left;
    return current;
}

Node *deleteNode(Node *root, int key) {
    if (root == NULL) return root;
    if (key < root->key) root->left = deleteNode(root->left, key);
    else if (key > root->key) root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node *temp = root->left;
            free(root);
            return temp;
        }
        Node *temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

int height(Node *node) {
    if (node == NULL) return 0;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
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

int main() {
    Node *root = NULL;
    int key;
    // Get the numbers to store in the AVL tree
    while (1) {
        scanf("%d", &key);
        if (key < 0) break;
        root = insert(root, key);
    }


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
    printf("%d, %d, %d\n", height(root), height(root->left), height(root->right) );

    // Second line: Get the last number only to search in the AVL tree and store the height
    // of the AVL tree height of the left subtree and height of the right subtree of this node
    Node *node = search(root, key);
    if (node == NULL) {
        printf("Valor nao encontrado\n");
    } else {
        printf("%d, %d, %d\n", height(node), height(node->left), height(node->right));
    }

    return 0;
}

// Time complexity: O(n^2)