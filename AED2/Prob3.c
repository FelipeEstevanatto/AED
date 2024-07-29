#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist { /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name; /* defined name */
    char *defn; /* replacement text */
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
      hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* lookup: look for string in hashtab */
struct nlist *lookup(char *string)
{
    struct nlist *np;
    for (np = hashtab[hash(string)]; np != NULL; np = np->next)
        if (strcmp(string, np->name) == 0)
          return np; /* found */
    return NULL; /* not found */
}

//char *strdup(char *);
/* insert: put (name, defn) in hashtab */
struct nlist *insert(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) { /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
          return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else /* already there */
        free((void *) np->defn); /*free previous defn */
    if ((np->defn = strdup(defn)) == NULL)
       return NULL;
    return np;
}

// char *strdup(char *s) /* make a duplicate of s */
// {
//     char *p;
//     p = (char *) malloc(strlen(s)+1); /* +1 for ’\0’ */
//     if (p != NULL)
//        strcpy(p, s);
//     return p;
// }

void printDictionary() {
    struct nlist *entry;
    for (int i = 0; i < HASHSIZE; i++) {
        entry = hashtab[i];
        while (entry != NULL) {
            printf("%s: %s\n", entry->name, entry->defn);
            entry = entry->next;
        }
    }
}

int main() {

    int knowTerms = 0;
    int nOfLines = 0;

    scanf("%d %d", &knowTerms, &nOfLines);

    // Initialize the hash table
    for (int i = 0; i < HASHSIZE; i++) {
        hashtab[i] = NULL;
    }

    char word[100];
    char translation[100];
    for (int i=0; i< knowTerms; i++) {
        scanf("%s", word);
        // scanf accept spaces
        scanf(" %[^\n]s", translation);

        insert(word, translation);
    }

    char lines[nOfLines][100];

    for (int i=0; i<nOfLines; i++) {
        scanf(" %[^\n]s", lines[i]);
    }

    for (int i=0; i<nOfLines; i++) {
        // break line into words with strtok
        char *word = strtok(lines[i], " ");
        while (word != NULL) {
            struct nlist *entry = lookup(word);
            if (entry != NULL) {
                printf("%s ", entry->defn);
            } else {
                printf("%s ", word);
            }
            word = strtok(NULL, " ");
        }
        printf("\n");
    }

    return 0;
}