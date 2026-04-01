#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* UTF-8 symbols */
#define DELTA  "\u03b4"   /* δ */
#define LAMBDA "\u03bb"   /* λ */

int get_symbol_index(char symbol, char *alphabet, int alphabet_size) {
    for (int i = 0; i < alphabet_size; i++)
        if (alphabet[i] == symbol) return i;
    return -1;
}

int is_final_state(int state, int *final_states, int num_final_states) {
    for (int i = 0; i < num_final_states; i++)
        if (state == final_states[i]) return 1;
    return 0;
}


void print_transition_table(
    int **transition,
    char *alphabet, int alphabet_size,
    int num_states, int start_state,
    int *final_states, int num_final_states
) {
    int col_w = 7;

    /* Helper to print one horizontal separator */
    #define SEP() do { \
        for (int _c = 0; _c < alphabet_size + 1; _c++) { \
            printf("+"); \
            for (int _w = 0; _w < col_w; _w++) printf("-"); \
        } \
        printf("+\n"); \
    } while(0)

    printf("\n  Transition Table:\n");
    SEP();

    /* Header */
    printf("| %-*s|", col_w - 1, " State");
    for (int j = 0; j < alphabet_size; j++)
        printf("  %-*c|", col_w - 3, alphabet[j]);
    printf("\n");
    SEP();

    /* State rows */
    for (int i = 0; i < num_states; i++) {
        bool is_start = (i == start_state);
        bool is_fin   = is_final_state(i, final_states, num_final_states);

        /* Build state label with marker prefix */
        char label[20];
        if      (is_start && is_fin) snprintf(label, sizeof(label), "*\u2192q%d", i);
        else if (is_start)           snprintf(label, sizeof(label), "\u2192q%d",  i);
        else if (is_fin)             snprintf(label, sizeof(label), "*q%d",        i);
        else                         snprintf(label, sizeof(label), "q%d",         i);

        /* UTF-8 arrow \u2192 is 3 bytes but 1 display column: correct padding */
        int byte_len    = strlen(label);
        int display_len = byte_len;
        for (int k = 0; k + 2 < byte_len; k++)
            if ((unsigned char)label[k]   == 0xE2 &&
                (unsigned char)label[k+1] == 0x86 &&
                (unsigned char)label[k+2] == 0x92)
                display_len -= 2;   /* 3 bytes printed as 1 char */

        int pad = (col_w - 1) - display_len;
        printf("| %s", label);
        for (int p = 0; p < pad; p++) printf(" ");
        printf("|");

        /* Transition cells */
        for (int j = 0; j < alphabet_size; j++) {
            char cell[10];
            snprintf(cell, sizeof(cell), "q%d", transition[i][j]);
            printf("  %-*s|", col_w - 3, cell);
        }
        printf("\n");
    }

    SEP();
    printf("  \u2192 = start state    * = final state\n\n");
    #undef SEP
}


int simulate(
    char *input, int len,
    int start_state,
    int **transition,
    char *alphabet, int alphabet_size,
    int *out_states
) {
    out_states[0] = start_state;
    for (int i = 0; i < len; i++) {
        int sym = get_symbol_index(input[i], alphabet, alphabet_size);
        if (sym == -1) return -1;
        out_states[i + 1] = transition[out_states[i]][sym];
    }
    return out_states[len];
}


void print_step(int curr, char *remaining) {
    int rem_len = strlen(remaining);
    printf("\t= ");

    /* Open one δ( for each char AFTER the first (those are the outer wrappers) */
    for (int i = 1; i < rem_len; i++) printf(DELTA "(");

    /* Innermost: δ*(qX, first_remaining_char) */
    printf(DELTA "*(q%d, %c)", curr, remaining[0]);

    /* Close with the rest of the chars left-to-right */
    for (int i = 1; i < rem_len; i++) printf(", %c)", remaining[i]);

    printf("\n");
}

void print_extended_function(
    char *input, int len,
    int start_state,
    int *out_states  /* out_states[i] = state after reading i chars */
) {
    /* Header */
    printf(DELTA "*(q%d, %s)\n", start_state, input);

    /* Steps: for each position i, show δ* with state out_states[i] and suffix input+i */
    for (int i = 0; i < len; i++)
        print_step(out_states[i], input + i);

    /* Final resolved state */
    printf("\t= q%d\n", out_states[len]);
}

void process_string(
    char *input,
    int start_state,
    int **transition,
    char *alphabet, int alphabet_size,
    int *final_states, int num_final_states
) {
    int len = strlen(input);
    int *out_states = malloc((len + 1) * sizeof(int));

    printf("\nEnter string: %s\nSteps:\n", input);

    int final_state = simulate(
        input, len, start_state,
        transition, alphabet, alphabet_size,
        out_states
    );

    if (final_state == -1) {
        printf("Rejected (invalid symbol)\n");
        free(out_states);
        return;
    }

    print_extended_function(input, len, start_state, out_states);

    printf("\n: %s\n",
        is_final_state(final_state, final_states, num_final_states)
            ? "Accepted" : "Rejected"
    );

    free(out_states);
}

int main() {
    int num_states, alphabet_size, start_state;
    int num_final_states, input_size;

    printf("Enter number of states: ");
    scanf("%d", &num_states);

    printf("Enter alphabet size: ");
    scanf("%d", &alphabet_size);

    char *alphabet = malloc((alphabet_size + 1) * sizeof(char));
    printf("Enter alphabet symbols (no spaces): ");
    scanf("%s", alphabet);

    /* Build transition table */
    int **transition = malloc(num_states * sizeof(int *));
    for (int i = 0; i < num_states; i++)
        transition[i] = malloc(alphabet_size * sizeof(int));

    printf("Enter transition table:\n");
    for (int i = 0; i < num_states; i++)
        for (int j = 0; j < alphabet_size; j++) {
            printf(DELTA "(q%d, %c) = ", i, alphabet[j]);
            scanf("%d", &transition[i][j]);
        }

    printf("Enter start state: ");
    scanf("%d", &start_state);

    printf("Enter number of final states: ");
    scanf("%d", &num_final_states);

    int *final_states = malloc(num_final_states * sizeof(int));
    printf("Enter final states: ");
    for (int i = 0; i < num_final_states; i++)
        scanf("%d", &final_states[i]);

    print_transition_table(
        transition, alphabet, alphabet_size,
        num_states, start_state,
        final_states, num_final_states
    );

    printf("Enter number of strings to test: ");
    scanf("%d", &input_size);

    char input[100];
    for (int i = 0; i < input_size; i++) {
        printf("%d) Enter an input string: ", i + 1);
        scanf("%s", input);

        process_string(
            input, start_state, transition,
            alphabet, alphabet_size,
            final_states, num_final_states
        );

        if (i < input_size - 1) {
            int cont;
            printf("\nContinue? (1=Yes, 0=No): ");
            scanf("%d", &cont);
            if (!cont) break;
        }
    }

    for (int i = 0; i < num_states; i++) free(transition[i]);
    free(transition);
    free(alphabet);
    free(final_states);

    return 0;
}