#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

int main() {
	setlocale(LC_ALL, "");

	int numStates, numInputSymbols;
	int startState;
	char inputString[100];

	printf("Enter total number of states: ");
	scanf("%d", &numStates);

	printf("Enter number of input symbols: ");
	scanf("%d", &numInputSymbols);

	char *inputAlphabet = (char *)malloc(numInputSymbols * sizeof(char));
	printf("Enter the input symbols (e.g., 0 1): ");
	for (int i = 0; i < numInputSymbols; i++) {
		scanf(" %c", &inputAlphabet[i]);
	}

	int **transitionTable = (int **)malloc(numStates * sizeof(int *));
	char **outputTable = (char **)malloc(numStates * sizeof(char *));

	for (int i = 0; i < numStates; i++) {
		transitionTable[i] = (int *)malloc(numInputSymbols * sizeof(int));
		outputTable[i] = (char *)malloc(numInputSymbols * sizeof(char));
	}

	printf("Enter the start state (0 to %d): ", numStates - 1);
	scanf("%d", &startState);

	printf("\n--- Define Transitions (\u03b4) and Outputs (\u03bb) ---\n");
	for (int i = 0; i < numStates; i++) {
		for (int j = 0; j < numInputSymbols; j++) {
			printf("\u03b4(q%d, %c) = q", i, inputAlphabet[j]);
			scanf("%d", &transitionTable[i][j]);

			printf("\u03bb(q%d, %c) = ", i, inputAlphabet[j]);
			scanf(" %c", &outputTable[i][j]);
		}
	}

	printf("\nMealy Machine Ready: \n");
	printf("--- State Transition & Output Table ---\n");
	printf("State\t");
	for (int l = 0; l < numInputSymbols; l++) {
		printf("Input '%c'\t\t", inputAlphabet[l]);
	}

	printf("\n\t");
	for (int l = 0; l < numInputSymbols; l++) {
		printf("Next(\u03b4)\tOut(\u03bb)\t");
	}

	printf("\n----------------------------------------------------\n");
	for (int m = 0; m < numStates; m++) {
		printf("q%d\t", m);
		for (int n = 0; n < numInputSymbols; n++) {
			printf("q%d\t%c\t\t", transitionTable[m][n], outputTable[m][n]);
		}
		printf("\n");
	}

	int choice = 0;
	while (choice != 2) {
		printf("\nMENU:\n1. Process String\n2. Exit\n");
		printf("Enter Choice: ");
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				printf("\nEnter input string to process: ");
				scanf("%s", inputString);

				int currentState = startState;
				int i = 0;
				bool validSymbol = true;
				char generatedOutput[100] = {0};

				printf("\n--- Processing Trace ---\n");
				while (inputString[i] != '\0') {
					char currentSymbol = inputString[i];
					int symbolIndex = -1;

					for (int k = 0; k < numInputSymbols; k++) {
						if (inputAlphabet[k] == currentSymbol) {
							symbolIndex = k;
							break;
						}
					}

					if (symbolIndex == -1) {
						printf(" -> Error: Invalid symbol '%c' detected. Halting.\n", currentSymbol);
						validSymbol = false;
						break;
					}

					int nextState = transitionTable[currentState][symbolIndex];
					char outputSymbol = outputTable[currentState][symbolIndex];
					generatedOutput[i] = outputSymbol;

					printf(" Read: '%c' | \u03bb(q%d, %c) = %c | \u03b4(q%d, %c) = q%d\n",
						   currentSymbol, currentState, currentSymbol, outputSymbol, currentState,
						   currentSymbol, nextState);

					currentState = nextState;
					i++;
				}

				generatedOutput[i] = '\0';

				if (validSymbol) {
					printf("\nConclusion:\n");
					printf("Input String : %s\n", inputString);
					printf("Output String : %s\n", generatedOutput);
					printf("Final State : q%d\n", currentState);
				}
				break;

			case 2:
				printf("Exiting Program!\n");
				break;

			default:
				printf("Enter Valid Choice\n");
		}
	}

	free(inputAlphabet);
	for (int i = 0; i < numStates; i++) {
		free(transitionTable[i]);
		free(outputTable[i]);
	}
	free(transitionTable);
	free(outputTable);

	return 0;
}