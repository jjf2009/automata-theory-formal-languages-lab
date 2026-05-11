#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include <locale.h>

int main() {
    
    setlocale(LC_ALL, ""); 
    int numStates, numSymbols, numFinalStates;
    int startState;
    int* finalStates;
    char* alphabet;
    char inputString[100];
    
    printf("Enter total number of states: ");
    scanf("%d", &numStates);

    printf("Enter number of symbols in alphabet: ");
    scanf("%d", &numSymbols);
    alphabet = (char *)malloc(numSymbols * sizeof(char));

    int** transitionTable = (int **)malloc(numStates * sizeof(int*));
    for(int i = 0; i < numStates; i++){
        transitionTable[i] = (int *)malloc(numSymbols * sizeof(int));
    }
    
    printf("Enter the input symbols (e.g., 0 1): ");
    for(int i = 0; i < numSymbols; i++) {
        scanf(" %c", &alphabet[i]); 
    }

    printf("Enter the start state (0 to %d): ", numStates - 1);
    scanf("%d", &startState);

    printf("Enter number of final states: ");
    scanf("%d", &numFinalStates);
    finalStates = (int *)malloc(numFinalStates * sizeof(int));
    
    printf("Enter the final states: ");
    for(int i = 0; i < numFinalStates; i++) {
        scanf("%d", &finalStates[i]);
    }

    printf("\n--- Define Transitions ---\n");
    for(int i = 0; i < numStates; i++) {
        for(int j = 0; j < numSymbols; j++) {
            printf("\u03b4(q%d, %c) = q", i, alphabet[j]);
            scanf("%d", &transitionTable[i][j]);
        }
    }

   
    printf("DFA Machine Components M = (Q, \u03A3, \u03b4, q0, F)\n"); 
    
    
    printf("Q  = { ");
    for(int m = 0; m < numStates; m++) printf("q%d ", m);
    printf("}\n");
    
    printf("\u03A3  = { ");
    for(int l = 0; l < numSymbols; l++) printf("%c ", alphabet[l]);
    printf("}\n");
    
    printf("q0 = q%d\n", startState);
    
    printf("F  = { ");
    for(int k = 0; k < numFinalStates; k++) printf("q%d ", finalStates[k]);
    printf("}\n");

    printf("\nTransition Table (\u03b4):\n");
    printf("\u03b4\t");
    for(int l=0; l < numSymbols; l++){
        printf("%c\t",alphabet[l]);
    }
    printf("\n------------------\n");
    for(int m=0; m < numStates; m++){
        printf("q%d\t",m);
        for(int a = 0; a < numSymbols; a++){
            printf("q%d\t",transitionTable[m][a]);
        }
        printf("\n");
    }

    int choice = 0;
    while(choice != 2){
        printf("\nMENU:\n1. Test String\n2. Exit!\n");
        printf("Enter Choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                printf("\nEnter input string to validate: ");
                scanf("%s", inputString);

                int currentState = startState;
                int i = 0;
                bool validSymbol = true;
                
                char prefix[100] = {0};
                char prev_prefix[100] = {0};

                printf("\n--- Extended Transition Function (\u03b4*) Trace ---\n");
                
               
                if (strlen(inputString) > 1) {
                    printf("\u03b4*(q%d, %s) = ?\n", startState, inputString);
                } else {
                    printf("\u03b4(q%d, %s) = ?\n", startState, inputString);
                }

                while(inputString[i] != '\0') {
                    char currentSymbol = inputString[i];
                    int symbolIndex = -1;

                    for(int k = 0; k < numSymbols; k++) {
                        if(alphabet[k] == currentSymbol) {
                            symbolIndex = k;
                            break;
                        }
                    }

                    if(symbolIndex == -1) {
                        printf("Error: Invalid symbol '%c' detected. Halting.\n", currentSymbol);
                        validSymbol = false;
                        break;
                    }
                    
                    strncpy(prev_prefix, inputString, i);
                    prev_prefix[i] = '\0'; 
                    strncpy(prefix, inputString, i + 1);
                    prefix[i + 1] = '\0';  

                    int prevState = currentState;
                    int nextState = transitionTable[currentState][symbolIndex];
                    
                  
                    if (i == 0) {
                       
                        printf("\u03b4(q%d, %s) = q%d\n", startState, prefix, nextState);
                    } else {
                       
                        const char* star_prev = (strlen(prev_prefix) > 1) ? "*" : "";
                        
                        printf("\u03b4*(q%d, %s) = \u03b4(\u03b4%s(q%d, %s), %c) = \u03b4(q%d, %c) = q%d\n", 
                               startState, prefix, star_prev, startState, prev_prefix, currentSymbol, prevState, currentSymbol, nextState);
                    }
                    
                    currentState = nextState;
                    i++;
                }

                if (validSymbol) {
                    bool isAccepted = false;
                    for(int k = 0; k < numFinalStates; k++) {
                        if(currentState == finalStates[k]) {
                            isAccepted = true;
                            break;
                        }
                    }

                    
                    printf("\n--- Conclusion ---\n");
                    printf("Ending State        : q%d\n", currentState);
                    
                    printf("Final States (F)    : { ");
                    for(int k = 0; k < numFinalStates; k++) {
                        printf("q%d ", finalStates[k]);
                    }
                    printf("}\n");

                    if(isAccepted) {
                       
                        printf("Condition           : q%d \u2208 F\n", currentState);
                        printf("Result              : String '%s' is ACCEPTED!\n", inputString);
                    } else {
                        
                        printf("Condition           : q%d \u2209 F\n", currentState);
                        printf("Result              : String '%s' is REJECTED.\n", inputString);
                    }
                }
                break;

            case 2:
                printf("Exiting Program!\n");
                break;

            default:
                printf("Enter Valid Choice\n");
        }
    }

    // Free memory
    free(alphabet);
    free(finalStates);
    for(int i = 0; i < numStates; i++){
        free(transitionTable[i]);
    }
    free(transitionTable);

    return 0;
}