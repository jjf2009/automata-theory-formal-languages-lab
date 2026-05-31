

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

#define MAX_STATES      20
#define MAX_SYMBOLS     20
#define MAX_STACK_SYM   20
#define MAX_TRANS       200
#define MAX_STRING      100
#define MAX_STACK_DEPTH 500
#define EPSILON         '$'   /* use '$' to denote ε (epsilon) in input */

/* ─── Transition record ──────────────────────────────────────────────────── */
typedef struct {
    int  from_state;
    char input_symbol;   /* EPSILON ('$') means ε-transition on input */
    char stack_top;      /* symbol that must be on top of stack        */
    int  to_state;
    char push_str[MAX_STACK_SYM]; /* string to push (leftmost = new top)
                                     use "$" to mean ε (pop, push nothing) */
} Transition;

/* ─── Stack ──────────────────────────────────────────────────────────────── */
typedef struct {
    char data[MAX_STACK_DEPTH];
    int  top;  /* index of topmost element; -1 = empty */
} Stack;

void  stack_init (Stack *s)                { s->top = -1; }
bool  stack_empty(const Stack *s)          { return s->top == -1; }
char  stack_top  (const Stack *s)          { return s->data[s->top]; }
void  stack_pop  (Stack *s)                { if (!stack_empty(s)) s->top--; }
void  stack_push (Stack *s, char c)        { s->data[++s->top] = c; }

/* Push a whole string so that push_str[0] ends up on top */
void stack_push_str(Stack *s, const char *str) {
    int len = (int)strlen(str);
    for (int i = len - 1; i >= 0; i--)
        stack_push(s, str[i]);
}

/* Print stack from top to bottom */
void stack_print(const Stack *s) {
    if (stack_empty(s)) { printf("\u03b5"); return; }   /* ε */
    for (int i = s->top; i >= 0; i--)
        printf("%c", s->data[i]);
}

/* ─── Globals ────────────────────────────────────────────────────────────── */
int        numStates, numInputSymbols, numStackSymbols;
int        startState, numFinalStates;
int        numTransitions;
char       inputAlphabet[MAX_SYMBOLS];
char       stackAlphabet[MAX_STACK_SYM];
int        finalStates[MAX_STATES];
Transition transitions[MAX_TRANS];
char       initialStackSymbol;

/* ─── Helpers ────────────────────────────────────────────────────────────── */
bool is_final(int state) {
    for (int i = 0; i < numFinalStates; i++)
        if (finalStates[i] == state) return true;
    return false;
}

bool valid_input_symbol(char c) {
    if (c == EPSILON) return true;
    for (int i = 0; i < numInputSymbols; i++)
        if (inputAlphabet[i] == c) return true;
    return false;
}

/* Find a matching transition; returns index or -1 */
int find_transition(int state, char in_sym, char stk_top) {
    for (int i = 0; i < numTransitions; i++) {
        Transition *t = &transitions[i];
        if (t->from_state == state &&
            t->input_symbol == in_sym &&
            t->stack_top == stk_top)
            return i;
    }
    return -1;
}

/* ─── Simulate ───────────────────────────────────────────────────────────── */
void simulate(const char *inputString) {
    Stack stk;
    stack_init(&stk);
    stack_push(&stk, initialStackSymbol);

    int currentState = startState;
    int pos = 0;
    int len = (int)strlen(inputString);
    bool error = false;

    /* validate all symbols first */
    for (int i = 0; i < len; i++) {
        if (!valid_input_symbol(inputString[i])) {
            printf("Error: '%c' is not in the input alphabet \u03a3.\n", inputString[i]);
            return;
        }
    }

    printf("\n--- Instantaneous Description (ID) Trace ---\n");
    printf("Format: (state, remaining_input, stack) where stack is printed top-first\n\n");

    /* Print initial ID */
    printf("(q%d, %s, ", currentState, (len == 0) ? "\u03b5" : inputString);
    stack_print(&stk);
    printf(")");

    while (pos <= len) {
        char in_sym = (pos < len) ? inputString[pos] : EPSILON;
        char stk_sym = stack_empty(&stk) ? '\0' : stack_top(&stk);

        if (stk_sym == '\0') {
            /* stack is empty – try epsilon on stack? PDA halts */
            break;
        }

        /* 1. Try exact match (current input symbol + stack top) */
        int ti = -1;
        if (pos < len)
            ti = find_transition(currentState, in_sym, stk_sym);

        /* 2. Try epsilon transition on input */
        if (ti == -1)
            ti = find_transition(currentState, EPSILON, stk_sym);

        if (ti == -1) {
            /* No transition found */
            if (pos == len) break;   /* may still accept if final */
            printf("\n  \u22a2  [No transition for \u03b4(q%d, %c, %c)]",
                   currentState, in_sym, stk_sym);
            error = true;
            break;
        }

        Transition *t = &transitions[ti];
        bool consumed = (t->input_symbol != EPSILON);

        /* Apply transition */
        stack_pop(&stk);
        if (strcmp(t->push_str, "$") != 0)   /* "$" means push nothing (ε) */
            stack_push_str(&stk, t->push_str);

        if (consumed) pos++;
        currentState = t->to_state;

        const char *remaining = (pos < len) ? inputString + pos : "\u03b5";

        printf("\n  \u22a2  (q%d, %s, ", currentState, remaining);
        stack_print(&stk);
        printf(")");
    }

    printf("\n\n--- Conclusion ---\n");
    printf("Ending State        : q%d\n", currentState);
    printf("Final States (F)    : { ");
    for (int k = 0; k < numFinalStates; k++) printf("q%d ", finalStates[k]);
    printf("}\n");

    bool accepted = !error && (pos == len) && is_final(currentState);
    if (accepted) {
        printf("Condition           : q%d \u2208 F\n", currentState);
        printf("Result              : String '%s' is ACCEPTED!\n", inputString);
    } else {
        printf("Condition           : q%d \u2209 F  (or no valid path)\n", currentState);
        printf("Result              : String '%s' is REJECTED.\n", inputString);
    }
}

/* ─── Main ───────────────────────────────────────────────────────────────── */
int main(void) {
    setlocale(LC_ALL, "");

    printf("╔══════════════════════════════════════════╗\n");
    printf("║   Pushdown Automaton (PDA) Simulator     ║\n");
    printf("║   Acceptance : by Final State            ║\n");
    printf("║   Use '$' to denote ε (epsilon)          ║\n");
    printf("╚══════════════════════════════════════════╝\n\n");

    /* ── States ── */
    printf("Enter total number of states: ");
    scanf("%d", &numStates);

    /* ── Input alphabet ── */
    printf("Enter number of input symbols (excluding \u03b5): ");
    scanf("%d", &numInputSymbols);
    printf("Enter input symbols (e.g., a b): ");
    for (int i = 0; i < numInputSymbols; i++)
        scanf(" %c", &inputAlphabet[i]);

    /* ── Stack alphabet ── */
    printf("Enter number of stack symbols: ");
    scanf("%d", &numStackSymbols);
    printf("Enter stack symbols (e.g., A Z0): ");
    /* Stack symbols are single chars; read as chars */
    char stackSymArr[MAX_STACK_SYM];
    for (int i = 0; i < numStackSymbols; i++)
        scanf(" %c", &stackSymArr[i]);
    memcpy(stackAlphabet, stackSymArr, numStackSymbols);

    /* ── Start state ── */
    printf("Enter start state (0 to %d): ", numStates - 1);
    scanf("%d", &startState);

    /* ── Initial stack symbol ── */
    printf("Enter initial stack symbol (e.g., Z): ");
    scanf(" %c", &initialStackSymbol);

    /* ── Final states ── */
    printf("Enter number of final states: ");
    scanf("%d", &numFinalStates);
    printf("Enter final states: ");
    for (int i = 0; i < numFinalStates; i++)
        scanf("%d", &finalStates[i]);

    /* ── Transitions ── */
    printf("Enter number of transitions: ");
    scanf("%d", &numTransitions);

    printf("\n--- Define Transitions ---\n");
    printf("For each transition enter: from_state  input_symbol  stack_top  to_state  push_string\n");
    printf("  Use '$' for \u03b5 in input_symbol or push_string\n");
    printf("  push_string is pushed so that the FIRST character is the NEW top\n");
    printf("  Example: 0 a Z 1 AZ   means \u03b4(q0, a, Z) = (q1, AZ)  \u2192 A on top\n\n");

    for (int i = 0; i < numTransitions; i++) {
        printf("Transition %d : ", i + 1);
        scanf("%d %c %c %d %s",
              &transitions[i].from_state,
              &transitions[i].input_symbol,
              &transitions[i].stack_top,
              &transitions[i].to_state,
               transitions[i].push_str);
    }

    /* ── Print PDA Tuple ── */
    printf("\n══════════════════════════════════════════════\n");
    printf("PDA Machine Components M = (Q, \u03a3, \u0393, \u03b4, q0, Z0, F)\n");
    printf("══════════════════════════════════════════════\n");

    printf("Q   = { ");
    for (int i = 0; i < numStates; i++) printf("q%d ", i);
    printf("}\n");

    printf("\u03a3   = { ");
    for (int i = 0; i < numInputSymbols; i++) printf("%c ", inputAlphabet[i]);
    printf("}\n");

    printf("\u0393   = { ");
    for (int i = 0; i < numStackSymbols; i++) printf("%c ", stackAlphabet[i]);
    printf("}\n");

    printf("q0  = q%d\n", startState);
    printf("Z0  = %c\n", initialStackSymbol);

    printf("F   = { ");
    for (int i = 0; i < numFinalStates; i++) printf("q%d ", finalStates[i]);
    printf("}\n");

    /* ── Print transition table ── */
    printf("\nTransition Function (\u03b4):\n");
    printf("%-6s %-8s %-10s %-8s %s\n",
           "\u03b4", "Input", "Stack Top", "To State", "Push (top\u2192bottom)");
    printf("----------------------------------------------\n");
    for (int i = 0; i < numTransitions; i++) {
        Transition *t = &transitions[i];
        char in_disp[4], push_disp[MAX_STACK_SYM + 4];

        if (t->input_symbol == EPSILON) strcpy(in_disp, "\u03b5");
        else { in_disp[0] = t->input_symbol; in_disp[1] = '\0'; }

        if (strcmp(t->push_str, "$") == 0) strcpy(push_disp, "\u03b5");
        else strcpy(push_disp, t->push_str);

        printf("\u03b4(q%d, %s, %c)  =  (q%d, %s)\n",
               t->from_state, in_disp, t->stack_top,
               t->to_state, push_disp);
    }

    /* ── Menu ── */
    char inputStr[MAX_STRING];
    int choice = 0;
    while (choice != 2) {
        printf("\nMENU:\n1. Test String\n2. Exit!\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter input string to validate (use '$' for \u03b5 / empty): ");
                scanf("%s", inputStr);
                /* treat lone '$' as empty string */
                if (strcmp(inputStr, "$") == 0) inputStr[0] = '\0';
                simulate(inputStr);
                break;
            case 2:
                printf("Exiting Program!\n");
                break;
            default:
                printf("Enter Valid Choice\n");
        }
    }

    return 0;
}