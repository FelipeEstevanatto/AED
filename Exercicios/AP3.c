// ATIVIDADE PRATICA 3 - Polinômios
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int coeficiente;
    int expoente;
} Monomio;

// Estrutura de nó da lista
typedef struct Node {
    Monomio monomio;
    struct Node *next;
} Node;

typedef struct Lista {
    Node *head;
    int count;
} Lista;

// Retorna ponteiro para o novo nó
Node *createNode(Monomio monomio) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->monomio = monomio;
    newNode->next = NULL;
    return newNode;
}

// Retorna ponteiro para a nova lista
Lista *createList() {
    Lista *lista = (Lista *) malloc(sizeof(Lista));
    lista->head = NULL;
    lista->count = 0;
    return lista;
}

void insertAtEnd(Lista *lista, Monomio monomio) {
    Node *newNode = createNode(monomio);
    if (lista->head == NULL) {
        lista->head = newNode;
    } else {
        Node *current = lista->head;
        while (current->next != NULL) {   
            current = current->next;
        }
        current->next = newNode;
    }
    lista->count++;
}

void deleteNode(Lista *lista, int position) {
    Node *current = lista->head;
    Node *previous = NULL;
    for (int i = 0; i < position; i++) {
        previous = current;   
        current = current->next;
    }
    if (previous == NULL) {
        lista->head = current->next;
    } else {
        previous->next = current->next;
    }
    free(current);
    lista->count--;
}

void insertInOrder(Lista *lista, Monomio monomio) {
    Node *newNode = createNode(monomio);
    if (lista->head == NULL || lista->head->monomio.expoente < monomio.expoente) {
        newNode->next = lista->head;
        lista->head = newNode;
    } else {
        Node *current = lista->head;
        Node *previous = NULL;
        while (current != NULL && current->monomio.expoente >= monomio.expoente) {
            previous = current;
            current = current->next;
        }
        newNode->next = current;
        previous->next = newNode;
    }
    lista->count++;
}

Lista *simplify(Lista *original) {
    if (original->count == 0) {
        return createList();
    }
    int maxExponent = 0;
    Node *current = original->head;
    while (current != NULL) {
        if (current->monomio.expoente > maxExponent) {
            maxExponent = current->monomio.expoente;
        }
        current = current->next;
    }
    
    Monomio *monomios = (Monomio *) calloc(maxExponent + 1, sizeof(Monomio));
    current = original->head;
    while (current != NULL) {
        int exponent = current->monomio.expoente;
        monomios[exponent].coeficiente += current->monomio.coeficiente;
        monomios[exponent].expoente = exponent;
        current = current->next;
    }
    
    Lista *simplified = createList();
    for (int i = maxExponent; i >= 0; i--) {
        if (monomios[i].coeficiente != 0) {
            insertAtEnd(simplified, monomios[i]);
        }
    }
    
    free(monomios);
    return simplified;
}

void printList(Lista *lista) {
    Node *current = lista->head;
    if (lista->count == 0) printf("nulo");
    while (current != NULL) {
        printf("%d %d ", current->monomio.coeficiente, current->monomio.expoente);
        current = current->next;
    }
    printf("\n");
}

int main() {
    int elementos;
    // 1 <= X <= 1023
    scanf("%d", &elementos);
    
    Lista *lista = createList();
    
    Monomio novoMonomio;
    for (int i = 0; i < elementos; i++) {
        // -10000 <= coeficiente <= 10000
        // 0 <= expoente <= 1023
        int coeficiente, expoente;
        scanf("%d %d", &coeficiente, &expoente);
        
        novoMonomio.coeficiente = coeficiente;
        novoMonomio.expoente = expoente;
        
        insertInOrder(lista, novoMonomio);
    }
    
    Lista *simplified = simplify(lista);
    
    printList(simplified);
    printf("%d\n", simplified->count);
    
    return 0;
}
