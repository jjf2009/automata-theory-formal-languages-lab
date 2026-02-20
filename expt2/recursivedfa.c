#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int  id;
    int  is_accept;
    int *transitions;   // transitions[symbol_index] = next state id
} State;

typedef struct {
    int    num_states;
    int    num_symbols;
    int    start_state;
    char  *symbols;
    State *states;
} DFA;

// returns index of symbol c in alphabet, or -1 if not found
int symbol_index(DFA *dfa, char c) {
    for (int i = 0; i < dfa->num_symbols; i++)
        if (dfa->symbols[i] == c) return i;
    return -1;
}

DFA *build_dfa() {
    DFA *dfa = malloc(sizeof(DFA));

    printf("Number of states  : "); scanf("%d", &dfa->num_states);
    printf("Number of symbols : "); scanf("%d", &dfa->num_symbols);

    dfa->symbols = malloc(dfa->num_symbols * sizeof(char));
    printf("Symbols (space-separated): ");
    for (int i = 0; i < dfa->num_symbols; i++)
        scanf(" %c", &dfa->symbols[i]);

    printf("Start state ID    : "); scanf("%d", &dfa->start_state);

    dfa->states = malloc(dfa->num_states * sizeof(State));
    for (int i = 0; i < dfa->num_states; i++) {
        dfa->states[i].id        = i;
        dfa->states[i].is_accept = 0;
        dfa->states[i].transitions = malloc(dfa->num_symbols * sizeof(int));
    }

    int num_accept;
    printf("Number of accept states: "); scanf("%d", &num_accept);
    printf("Accept state IDs: ");
    for (int i = 0; i < num_accept; i++) {
        int a; scanf("%d", &a);
        dfa->states[a].is_accept = 1;
    }

    printf("\nTransition table (for each state, enter next state for: ");
    for (int i = 0; i < dfa->num_symbols; i++) printf(" '%c'", dfa->symbols[i]);
    printf(")\n");
    for (int s = 0; s < dfa->num_states; s++) {
        printf("  State %d: ", s);
        for (int sym = 0; sym < dfa->num_symbols; sym++)
            scanf("%d", &dfa->states[s].transitions[sym]);
    }

    return dfa;
}

void free_dfa(DFA *dfa) {
    for (int i = 0; i < dfa->num_states; i++)
        free(dfa->states[i].transitions);
    free(dfa->states);
    free(dfa->symbols);
    free(dfa);
}


// ── Recursive ────────────────────────────────
int run_recursive(DFA *dfa, int cur, const char *input, int pos) {
    if (!input[pos]) {
        printf("  Final: %d → %s\n", cur, dfa->states[cur].is_accept ? "ACCEPTED" : "REJECTED");
        return dfa->states[cur].is_accept;
    }

    int idx = symbol_index(dfa, input[pos]);
    if (idx == -1) { printf("  '%c' not in alphabet\n", input[pos]); return 0; }

    int next = dfa->states[cur].transitions[idx];
    printf("  d(%d,'%c') = %d\n", cur, input[pos], next);

    return run_recursive(dfa, next, input, pos + 1);
}

int main() {
    printf("=== DFA Simulator ===\n\n");
    DFA *dfa = build_dfa();

    char input[256];
    printf("\nString to test: ");
    scanf(" "); fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    printf("\nTesting: \"%s\"\n\n", input);
    printf("\n");
    printf("[Recursive] start=%d\n", dfa->start_state);
    int r2 = run_recursive(dfa, dfa->start_state, input, 0);


    printf("Recursive → %s\n", r2 ? "ACCEPTED" : "REJECTED");

    free_dfa(dfa);
    return 0;
}