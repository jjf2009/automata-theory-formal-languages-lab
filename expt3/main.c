#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DELTA "\u03b4"
#define DSTAR "\u03b4*"
#define ARROW "\u2192"
#define EMPTY "\u2205"

/* builds "{q0, q2}" or "{∅}" from a bool array */
void build_set(bool *states, int num_states, char *buf) {
    strcpy(buf, "{");
    bool first = true;
    for (int i = 0; i < num_states; i++) {
        if (!states[i]) continue;
        if (!first) strcat(buf, ", ");
        char tmp[10];
        sprintf(tmp, "q%d", i);
        strcat(buf, tmp);
        first = false;
    }
    if (first) strcat(buf, EMPTY);
    strcat(buf, "}");
}

int sym_idx(char c, char *alphabet, int num_symbols) {
    for (int i = 0; i < num_symbols; i++)
        if (alphabet[i] == c) return i;
    return -1;
}

int is_final(int state, int *final_states, int num_final_states) {
    for (int i = 0; i < num_final_states; i++)
        if (final_states[i] == state) return 1;
    return 0;
}

void print_table(int ***table, char *alphabet, int num_symbols,
                 int num_states, int start_state,
                 int *final_states, int num_final_states) {
    printf("\n--- Transition Table ---\n");
    printf(DELTA "\t");
    for (int j = 0; j < num_symbols; j++) printf("%c\t\t", alphabet[j]);
    printf("\n");
    for (int j = 0; j < num_symbols * 10 + 8; j++) printf("-");
    printf("\n");

    for (int i = 0; i < num_states; i++) {
        bool is_start = (i == start_state);
        bool is_fin   = is_final(i, final_states, num_final_states);
        if      (is_start && is_fin) printf("*" ARROW "q%d\t", i);
        else if (is_start)           printf(ARROW "q%d\t", i);
        else if (is_fin)             printf("*q%d\t", i);
        else                         printf("q%d\t", i);

        for (int j = 0; j < num_symbols; j++) {
            printf("{ ");
            bool any = false;
            for (int k = 0; k < num_states; k++) {
                if (table[i][j][k]) { printf("q%d ", k); any = true; }
            }
            if (!any) printf(EMPTY " ");
            printf("}\t");
        }
        printf("\n");
    }
    printf(ARROW " = start    * = final\n");
}

void run(char *input, int start_state, int num_states,
         int ***table, char *alphabet, int num_symbols,
         int *final_states, int num_final_states) {
    bool *current = calloc(num_states, sizeof(bool));
    bool *next    = calloc(num_states, sizeof(bool));
    current[start_state] = true;

    char current_set[200], next_set[200];
    char prefix[100], prev_prefix[100];

    printf("\n--- " DSTAR " Trace ---\n");
    printf(DSTAR "(q%d, %s) = ?\n", start_state, input);

    bool valid = true;
    int i = 0;
    while (input[i] != '\0') {
        int si = sym_idx(input[i], alphabet, num_symbols);
        if (si == -1) {
            printf("Error: invalid symbol '%c'\n", input[i]);
            valid = false; break;
        }

        strncpy(prev_prefix, input, i);     prev_prefix[i]   = '\0';
        strncpy(prefix,      input, i + 1); prefix[i + 1]    = '\0';

        build_set(current, num_states, current_set);
        memset(next, 0, num_states * sizeof(bool));
        for (int s = 0; s < num_states; s++) {
            if (!current[s]) continue;
            for (int t = 0; t < num_states; t++)
                if (table[s][si][t]) next[t] = true;
        }
        build_set(next, num_states, next_set);

        if (i == 0)
            printf(DSTAR "(q%d, %s) = " DELTA "(q%d, %c) = %s\n",
                   start_state, prefix, start_state, input[i], next_set);
        else
            printf(DSTAR "(q%d, %s) = " DELTA "(" DSTAR "(q%d, %s), %c) = " DELTA "(%s, %c) = %s\n",
                   start_state, prefix, start_state, prev_prefix, input[i], current_set, input[i], next_set);

        memcpy(current, next, num_states * sizeof(bool));
        i++;
    }

    if (valid) {
        bool accepted = false;
        for (int k = 0; k < num_final_states; k++)
            if (current[final_states[k]]) { accepted = true; break; }

        if (accepted) {
            printf("\nAccepted! (final states reached: ");
            for (int f = 0; f < num_final_states; f++)
                if (current[final_states[f]]) printf("q%d ", final_states[f]);
            printf(")\n");
        } else {
            printf("\nRejected.\n");
        }
    }

    free(current);
    free(next);
}

int main() {
    int num_states, num_symbols, start_state, num_final_states;

    printf("Enter number of states: ");    scanf("%d", &num_states);
    printf("Enter number of symbols: ");   scanf("%d", &num_symbols);

    char *alphabet = malloc(num_symbols * sizeof(char));
    printf("Enter symbols (e.g. a b): ");
    for (int i = 0; i < num_symbols; i++) scanf(" %c", &alphabet[i]);

    int ***table = malloc(num_states * sizeof(int **));
    for (int i = 0; i < num_states; i++) {
        table[i] = malloc(num_symbols * sizeof(int *));
        for (int j = 0; j < num_symbols; j++)
            table[i][j] = calloc(num_states, sizeof(int));
    }

    printf("Enter start state: ");         scanf("%d", &start_state);
    printf("Enter number of final states: "); scanf("%d", &num_final_states);
    int *final_states = malloc(num_final_states * sizeof(int));
    printf("Enter final states: ");
    for (int i = 0; i < num_final_states; i++) scanf("%d", &final_states[i]);

    printf("\n--- Define Transitions ---\n");
    for (int i = 0; i < num_states; i++)
        for (int j = 0; j < num_symbols; j++) {
            int count;
            printf("How many transitions for " DELTA "(q%d, %c)? ", i, alphabet[j]);
            scanf("%d", &count);
            for (int t = 0; t < count; t++) {
                int target;
                printf("  " ARROW " q");
                scanf("%d", &target);
                if (target >= 0 && target < num_states)
                    table[i][j][target] = 1;
                else
                    printf("  Invalid state, ignored.\n");
            }
        }

    print_table(table, alphabet, num_symbols, num_states,
                start_state, final_states, num_final_states);

    int choice = 0;
    char input[100];
    while (choice != 2) {
        printf("\nMENU:\n1. Test String\n2. Exit\nChoice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Enter string: "); scanf("%s", input);
            run(input, start_state, num_states, table,
                alphabet, num_symbols, final_states, num_final_states);
        } else if (choice != 2) {
            printf("Invalid choice.\n");
        }
    }

    for (int i = 0; i < num_states; i++) {
        for (int j = 0; j < num_symbols; j++) free(table[i][j]);
        free(table[i]);
    }
    free(table); free(alphabet); free(final_states);
    return 0;
}