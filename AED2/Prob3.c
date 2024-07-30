#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashNode {
    struct HashNode *next;
    char *key; /* defined name */
    char *value; /* replacement text */
} HashNode;

/* Create hash value from string (31 is an arbitraty value) */
unsigned hash(char *str, int hashSize)
{
    unsigned hashValue;
    for (hashValue = 0; *str != '\0'; str++)
      hashValue = *str + 31 * hashValue;
    return hashValue % hashSize;
}

/* Look for string in the hashTable */
HashNode *lookup(char *str, HashNode **hashTable, int hashSize)
{
    unsigned hashValue = hash(str, hashSize);
    HashNode *node = hashTable[hashValue];

    while (node != NULL) {
        if (strcmp(str, node->key) == 0) {
            return node; /* found */
        }
        node = node->next;
    }
    
    return NULL; /* not found */
}

/* Put (key, value) in hashTable, and return the node */
HashNode *insert(char *key, char *value, HashNode **hashTable, int hashSize)
{
    unsigned hashValue;
    HashNode *node = lookup(key, hashTable, hashSize);

    if (node != NULL) {
        /* Key found, update the value */
        free(node->value);
        node->value = strdup(value);
        if (node->value == NULL) return NULL;
        return node;
    }

    /* Key not found, create a new node */
    node = (HashNode *) malloc(sizeof(HashNode));
    if (node == NULL) return NULL;

    node->key = strdup(key);
    node->value = strdup(value);
    if (node->key == NULL || node->value == NULL) {
        free(node->key);
        free(node);
        return NULL;
    }

    /* Insert the node in the hashTable */
    hashValue = hash(key, hashSize);
    node->next = hashTable[hashValue];
    hashTable[hashValue] = node;

    return node;
}

void printDictionary(HashNode **hashTable, int hashSize) {
    HashNode *node;
    for (int i = 0; i < hashSize; i++) {
        for (node = hashTable[i]; node != NULL; node = node->next) {
            printf("Word: %s, Definition: %s\n", node->key, node->value);
        }
    }
}

int main() {

    int knownTerms = 0;
    int numberOfLines = 0;

    scanf("%d %d", &knownTerms, &numberOfLines);

    HashNode **hashTable = (HashNode **) malloc(knownTerms * sizeof(HashNode *));
    int hashSize = knownTerms;

    // Initialize the hash table
    for (int i = 0; i < hashSize; i++) {
        hashTable[i] = NULL;
    }

    char word[100];
    char translation[100];
    // get the words
    for (int i = 0; i < knownTerms; i++) {
        scanf("%s", word);
        // scanf accept spaces
        scanf(" %[^\n]s", translation);

        insert(word, translation, hashTable, hashSize);
    }

    char lines[numberOfLines][100];

    for (int i=0; i<numberOfLines; i++) {
        scanf(" %[^\n]s", lines[i]);
    }

    for (int i=0; i < numberOfLines; i++) {
        // break line into words with strtok
        char *word = strtok(lines[i], " ");

        while (word != NULL) {
            HashNode *entry = lookup(word, hashTable, hashSize);
            if (entry != NULL) {
                printf("%s ", entry->value);
            } else {
                printf("%s ", word);
            }
            word = strtok(NULL, " ");
        }
        printf("\n");
    }

    return 0;
}