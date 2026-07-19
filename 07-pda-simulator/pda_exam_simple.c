#include <stdio.h>
#include <string.h>

struct Rule {
    int from; char in; char pop;
    int to; char push[10];
};

int main() {
    int num_rules, num_finals, start_state;
    struct Rule rules[50];
    int finals[20];
    char input[100], stack[100], init_stack;
    int top = -1;

    // 1. Setup
    printf("Enter Start State, Num Final States, and Initial Stack Symbol (e.g., 0 1 Z): ");
    scanf("%d %d %c", &start_state, &num_finals, &init_stack);

    printf("Enter the final states: ");
    for(int i=0; i<num_finals; i++) scanf("%d", &finals[i]);

    printf("Enter number of rules: ");
    scanf("%d", &num_rules);

    printf("Format: FromState Input StackTop ToState Push (use $ for empty)\n");
    for(int i = 0; i < num_rules; i++) {
        printf("Rule %d: ", i + 1);
        scanf("%d %c %c %d %s", &rules[i].from, &rules[i].in, &rules[i].pop, &rules[i].to, rules[i].push);
    }

    // 2. Processing
    printf("\nEnter string to test: ");
    scanf("%s", input);

    int curr = start_state;
    int i = 0;
    stack[++top] = init_stack;

    while(i <= strlen(input)) {
        char curr_in = (i < strlen(input)) ? input[i] : '$';
        char curr_top = (top >= 0) ? stack[top] : '$';
        int found = -1;
        
        for(int r = 0; r < num_rules; r++) {
            if(rules[r].from == curr && rules[r].pop == curr_top) {
                if(rules[r].in == curr_in) { found = r; break; } 
                if(rules[r].in == '$') { found = r; }            
            }
        }

        if(found == -1) break; 

        top--; 
        if(strcmp(rules[found].push, "$") != 0) {
            for(int p = strlen(rules[found].push) - 1; p >= 0; p--) {
                stack[++top] = rules[found].push[p];
            }
        }
        
        curr = rules[found].to;
        if(rules[found].in != '$') i++; 
    }

    // 3. Acceptance Check
    int accepted = 0;
    if(i == strlen(input)) {
        for(int f = 0; f < num_finals; f++) {
            if(curr == finals[f]) accepted = 1;
        }
    }

    if(accepted) printf("\nString ACCEPTED!\n");
    else printf("\nString REJECTED!\n");

    return 0;
}