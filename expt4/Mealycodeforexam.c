#include <stdio.h>
#include <string.h>

#define MAX_STATES 20
#define MAX_SYMBOLS 10

int main()
{
    int states, symbols;
    char alphabet[MAX_SYMBOLS];

    int transition[MAX_STATES][MAX_SYMBOLS];
    char output[MAX_STATES][MAX_SYMBOLS];

    int startState;
    char input[100];
    char result[100];

    printf("Enter number of states: ");
    scanf("%d",&states);

    printf("Enter number of symbols: ");
    scanf("%d",&symbols);

    printf("Enter alphabet: ");
    for(int i=0;i<symbols;i++)
        scanf(" %c",&alphabet[i]);

    printf("Enter start state: ");
    scanf("%d",&startState);

    printf("\nEnter transitions and outputs:\n");

    for(int i=0;i<states;i++)
    {
        for(int j=0;j<symbols;j++)
        {
            printf("δ(q%d,%c)=q",i,alphabet[j]);
            scanf("%d",&transition[i][j]);

            printf("λ(q%d,%c)=",i,alphabet[j]);
            scanf(" %c",&output[i][j]);
        }
    }

    printf("Enter input string: ");
    scanf("%s",input);

    int currentState = startState;

    for(int i=0; input[i]!='\0'; i++)
    {
        int symbolIndex = -1;

        for(int j=0;j<symbols;j++)
        {
            if(input[i] == alphabet[j])
            {
                symbolIndex = j;
                break;
            }
        }

        if(symbolIndex == -1)
        {
            printf("Invalid Symbol\n");
            return 0;
        }

        result[i] =
            output[currentState][symbolIndex];

        currentState =
            transition[currentState][symbolIndex];
    }

    result[strlen(input)] = '\0';

    printf("Output String = %s\n",result);
    printf("Final State = q%d\n",currentState);

    return 0;
}