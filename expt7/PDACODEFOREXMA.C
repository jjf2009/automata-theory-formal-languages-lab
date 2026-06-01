#include <stdio.h>
#include <string.h>

#define MAX 20

typedef struct
{
    int from;
    char input;
    char stackTop;
    int to;
    char push[10];
} Transition;

Transition t[MAX];

int main()
{
    int states, transitions;
    int startState;
    int finalState;

    printf("Enter number of transitions: ");
    scanf("%d", &transitions);

    printf("Enter start state: ");
    scanf("%d", &startState);

    printf("Enter final state: ");
    scanf("%d", &finalState);

    printf("\nEnter transitions:\n");
    printf("from input stackTop to push\n");

    for(int i=0;i<transitions;i++)
    {
        scanf("%d %c %c %d %s",
              &t[i].from,
              &t[i].input,
              &t[i].stackTop,
              &t[i].to,
              t[i].push);
    }

    char str[100];

    printf("Enter string: ");
    scanf("%s", str);

    char stack[100];
    int top = 0;

    stack[top] = 'Z';      // Initial stack symbol

    int currentState = startState;
    int pos = 0;

    while(str[pos] != '\0')
    {
        char input = str[pos];
        char stk = stack[top];

        int found = 0;

        for(int i=0;i<transitions;i++)
        {
            if(t[i].from == currentState &&
               t[i].input == input &&
               t[i].stackTop == stk)
            {
                top--; // pop

                if(strcmp(t[i].push,"$") != 0)
                {
                    int len = strlen(t[i].push);

                    for(int j=len-1;j>=0;j--)
                        stack[++top] = t[i].push[j];
                }

                currentState = t[i].to;
                pos++;
                found = 1;

                break;
            }
        }

        if(!found)
        {
            printf("REJECTED\n");
            return 0;
        }
    }

    if(currentState == finalState)
        printf("ACCEPTED\n");
    else
        printf("REJECTED\n");

    return 0;
}