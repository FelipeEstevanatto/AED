#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 500
/**
 * A primeira linha de um caso de teste contém três inteiros N (1 ≤ N ≤ 500),
M(0 ≤ M ≤ 60. 000) e I(1 ≤ I ≤ 500), indicando respectivamente o número de membros da
facção, o número de relações de comando direta e o número de instruções. Membros são
identificados unicamente por números de 1 a N. A segunda linha contém N inteiros
T , onde indica o tempo total em prisões do membro .
 */

// Node, value of the member and the next node
typedef struct Node {
    int value;
    struct Node* next;
} Node;

// Faction structure, with the heads of the hierarchy and the prison times of each member
typedef struct {
    Node* heads[MAX_N + 1];
    int prison_times[MAX_N + 1];
} Faction;

void init_faction(Faction* faction, int nOfMembers, int prison_times[]);
void free_faction(Faction* faction, int size);

void add_hierarchy(Faction* faction, int x, int y) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = x;
    node->next = faction->heads[y];
    faction->heads[y] = node;
}

// Swap the positions of two members
// ** Multiple nodes can commands the same member, so the swap has to be fully transactional and update all nodes pointing to a or b
void swap_positions(Faction* faction, int a, int b, int n) {
    // Temporarily store the heads to safely swap
    Node* tempA = faction->heads[a];
    Node* tempB = faction->heads[b];

    // Swap the head pointers
    faction->heads[a] = tempB;
    faction->heads[b] = tempA;

    // Update all nodes pointing to a or b
    for (int y = 1; y <= n; ++y) {
        Node* current = faction->heads[y];
        while (current != NULL) {
            if (current->value == a) {
                current->value = b;
            } else if (current->value == b) {
                current->value = a;
            }
            current = current->next;
        }
    }
}

// Search for the maximum prison time of a faction member using DFS (Depth First Search)
// ** The search is done using a stack to avoid recursion
int max_prison_time(Faction* faction, int member) {
    int visited[MAX_N + 1] = {0};
    int max_time = -1;
    int stack[MAX_N];
    int stack_size = 0;

    stack[stack_size++] = member;
    visited[member] = 1;

    while (stack_size > 0) {
        int current = stack[--stack_size];
        Node* head = faction->heads[current];

        // Visit all members that the current member commands
        while (head != NULL) {
            int leader = head->value;
            if (!visited[leader]) {
                visited[leader] = 1;
                if (faction->prison_times[leader] > max_time) {
                    max_time = faction->prison_times[leader];
                }
                stack[stack_size++] = leader;
            }
            head = head->next;
        }
    }

    return max_time == -1 ? -1 : max_time;
}

int main() {
    int nOfMembers, nOfRelations, nOfInstructions;
    
    // Input number of members, number of commands, and number of instructions
    scanf("%d %d %d", &nOfMembers, &nOfRelations, &nOfInstructions);

    int prison_times[MAX_N];
    // Enter the prison times
    for (int j = 0; j < nOfMembers; ++j) {
        scanf("%d", &prison_times[j]);
    }

    Faction faction;
    init_faction(&faction, nOfMembers, prison_times);

    // Enter the commands (x y)
    for (int j = 0; j < nOfRelations; ++j) {
        int x, y;
        scanf("%d %d", &x, &y);
        add_hierarchy(&faction, x, y);
    }

    // Enter the instructions
    for (int j = 0; j < nOfInstructions; ++j) {
        char instruction[2];
        int a, b;
        scanf("%s", instruction);
        if (strcmp(instruction, "P") == 0) {
            scanf("%d", &a);
            int result = max_prison_time(&faction, a);
            if (result == -1) {
                printf("*\n");
            } else {
                printf("%d\n", result);
            }
        } else if (strcmp(instruction, "T") == 0) {
            scanf("%d %d", &a, &b);
            swap_positions(&faction, a, b, nOfMembers);
        }
    }

    // Free allocated memory
    free_faction(&faction, nOfMembers);

    return 0;
}

void free_faction(Faction* faction, int size) {
    for (int i = 1; i <= size; ++i) {
        Node* current = faction->heads[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
        faction->heads[i] = NULL;
    }
}

// Initialize the faction with the prison times and the heads of the hierarchy
void init_faction(Faction* faction, int nOfMembers, int prison_times[]) {
    for (int i = 1; i <= nOfMembers; ++i) {
        faction->heads[i] = NULL;
        faction->prison_times[i] = prison_times[i - 1];
    }
}