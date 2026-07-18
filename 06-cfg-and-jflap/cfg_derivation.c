#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PROD 100
#define MAX_SYMBOLS 50
#define MAX_LEN 200
#define MAX_QUEUE 10000

typedef struct {
    char lhs;
    char rhs[MAX_LEN];
} Production;

typedef struct {
    char form[MAX_LEN];
    int parent;
} Node;

char variables[MAX_SYMBOLS];
char terminals[MAX_SYMBOLS];
char startSymbol;

int varCount, termCount;
int prodCount = 0;

Production productions[MAX_PROD];

int isVariable(char c) {
    for (int i = 0; i < varCount; i++) {
        if (variables[i] == c)
            return 1;
    }
    return 0;
}

int isTerminal(char c) {
    for (int i = 0; i < termCount; i++) {
        if (terminals[i] == c)
            return 1;
    }
    return 0;
}

int hasVariable(char str[]) {
    for (int i = 0; str[i]; i++) {
        if (isVariable(str[i]))
            return 1;
    }
    return 0;
}

int terminalCount(char str[]) {
    int count = 0;

    for (int i = 0; str[i]; i++) {
        if (!isVariable(str[i]))
            count++;
    }

    return count;
}

int validString(char str[]) {
    for (int i = 0; str[i]; i++) {
        if (!isTerminal(str[i]))
            return 0;
    }

    return 1;
}

void replaceAt(char result[], char form[], int pos, char rhs[]) {
    result[0] = '\0';

    strncat(result, form, pos);

    if (strcmp(rhs, "#") != 0) {
        strcat(result, rhs);
    }

    strcat(result, form + pos + 1);
}

int alreadyExists(Node queue[], int size, char form[]) {
    for (int i = 0; i < size; i++) {
        if (strcmp(queue[i].form, form) == 0)
            return 1;
    }

    return 0;
}

void printDerivation(Node queue[], int index) {
    int path[MAX_QUEUE];
    int count = 0;

    while (index != -1) {
        path[count++] = index;
        index = queue[index].parent;
    }

    for (int i = count - 1; i >= 0; i--) {
        printf("%s", queue[path[i]].form);

        if (i != 0)
            printf(" => ");
    }

    printf("\n");
}

int derive(char target[], int leftMost, Node answerQueue[], int *answerIndex) {
    Node queue[MAX_QUEUE];

    int front = 0;
    int rear = 0;
    int targetLen = strlen(target);

    queue[rear].form[0] = startSymbol;
    queue[rear].form[1] = '\0';
    queue[rear].parent = -1;
    rear++;

    while (front < rear) {
        Node current = queue[front];

        if (strcmp(current.form, target) == 0) {
            for (int i = 0; i < rear; i++) {
                answerQueue[i] = queue[i];
            }

            *answerIndex = front;
            return 1;
        }

        if (!hasVariable(current.form)) {
            front++;
            continue;
        }

        if (terminalCount(current.form) > targetLen) {
            front++;
            continue;
        }

        int pos = -1;

        if (leftMost) {
            for (int i = 0; current.form[i]; i++) {
                if (isVariable(current.form[i])) {
                    pos = i;
                    break;
                }
            }
        } else {
            for (int i = strlen(current.form) - 1; i >= 0; i--) {
                if (isVariable(current.form[i])) {
                    pos = i;
                    break;
                }
            }
        }

        char var = current.form[pos];

        for (int i = 0; i < prodCount; i++) {
            if (productions[i].lhs == var) {
                char newForm[MAX_LEN];

                replaceAt(newForm, current.form, pos, productions[i].rhs);

                if (strlen(newForm) <= targetLen + 10 &&
                    !alreadyExists(queue, rear, newForm)) {

                    strcpy(queue[rear].form, newForm);
                    queue[rear].parent = front;
                    rear++;

                    if (rear >= MAX_QUEUE) {
                        return 0;
                    }
                }
            }
        }

        front++;
    }

    return 0;
}

void addProduction(char lhs, char rhs[]) {
    productions[prodCount].lhs = lhs;
    strcpy(productions[prodCount].rhs, rhs);
    prodCount++;
}

void readProductionLine() {
    char input[MAX_LEN];
    char rhsPart[MAX_LEN];

    scanf("%s", input);

    char lhs = input[0];

    if (!isVariable(lhs)) {
        printf("Invalid LHS. LHS must be a variable.\n");
        return;
    }

    char *arrow = strstr(input, "->");

    if (arrow == NULL) {
        printf("Invalid format. Use A->aB|b\n");
        return;
    }

    strcpy(rhsPart, arrow + 2);

    char *token = strtok(rhsPart, "|");

    while (token != NULL) {
        addProduction(lhs, token);
        token = strtok(NULL, "|");
    }
}

void inputGrammar() {
    printf("Enter number of variables: ");
    scanf("%d", &varCount);

    printf("Enter variables one by one:\n");
    for (int i = 0; i < varCount; i++) {
        scanf(" %c", &variables[i]);
    }

    printf("Enter number of terminals: ");
    scanf("%d", &termCount);

    printf("Enter terminals one by one:\n");
    for (int i = 0; i < termCount; i++) {
        scanf(" %c", &terminals[i]);
    }

    printf("Enter start symbol: ");
    scanf(" %c", &startSymbol);

    if (!isVariable(startSymbol)) {
        printf("Invalid start symbol. It must be one of the variables.\n");
    }

    int lines;
    printf("Enter number of production lines: ");
    scanf("%d", &lines);

    printf("\nEnter productions like this:\n");
    printf("S->aSb|AB|#\n");
    printf("A->aA|a\n");
    printf("B->bB|b\n\n");

    for (int i = 0; i < lines; i++) {
        printf("Production line %d: ", i + 1);
        readProductionLine();
    }
}

void displayGrammar() {
    printf("\nG = (V, T, S, P)\n");

    printf("V = { ");
    for (int i = 0; i < varCount; i++) {
        printf("%c", variables[i]);
        if (i != varCount - 1)
            printf(", ");
    }
    printf(" }\n");

    printf("T = { ");
    for (int i = 0; i < termCount; i++) {
        printf("%c", terminals[i]);
        if (i != termCount - 1)
            printf(", ");
    }
    printf(" }\n");

    printf("S = %c\n", startSymbol);

    printf("P = {\n");
    for (int i = 0; i < prodCount; i++) {
        printf("  %c -> %s\n", productions[i].lhs, productions[i].rhs);
    }
    printf("}\n");
}

int main() {
    char str[MAX_LEN];

    inputGrammar();
    displayGrammar();

    while (1) {
        printf("\nEnter string to test or type exit: ");
        scanf("%s", str);

        if (strcmp(str, "exit") == 0) {
            break;
        }

        if (!validString(str)) {
            printf("\nString contains symbols not present in terminal set.\n");
            printf("String is REJECTED.\n");
            continue;
        }

        Node leftQueue[MAX_QUEUE], rightQueue[MAX_QUEUE];
        int leftIndex = -1, rightIndex = -1;

        int acceptedLeft = derive(str, 1, leftQueue, &leftIndex);
        int acceptedRight = derive(str, 0, rightQueue, &rightIndex);

        if (acceptedLeft) {
            printf("\nString is ACCEPTED by the grammar.\n");

            printf("\nLeftmost Derivation:\n");
            printDerivation(leftQueue, leftIndex);

            printf("\nRightmost Derivation:\n");
            if (acceptedRight) {
                printDerivation(rightQueue, rightIndex);
            } else {
                printf("Rightmost derivation not found within search limit.\n");
            }
        } else {
            printf("\nString is REJECTED by the grammar.\n");
        }
    }

    return 0;
}