#include <stdio.h>
#include <string.h>

#define MAX_STATES 20
#define MAX_SYMBOLS 10

int main()
{
    int states, symbols;
    char alphabet[MAX_SYMBOLS];

    int startState;

    int finalCount;
    int finalStates[MAX_STATES];

    int transition[MAX_STATES][MAX_SYMBOLS][MAX_STATES] = {0};

    char str[100];

    printf("Enter number of states: ");
    scanf("%d", &states);

    printf("Enter number of symbols: ");
    scanf("%d", &symbols);

    printf("Enter alphabet: ");
    for(int i = 0; i < symbols; i++)
        scanf(" %c", &alphabet[i]);

    printf("Enter start state: ");
    scanf("%d", &startState);

    printf("Enter number of final states: ");
    scanf("%d", &finalCount);

    printf("Enter final states: ");
    for(int i = 0; i < finalCount; i++)
        scanf("%d", &finalStates[i]);

    printf("\nEnter transitions:\n");

    for(int i = 0; i < states; i++)
    {
        for(int j = 0; j < symbols; j++)
        {
            int count;

            printf("Number of transitions from q%d on %c: ",
                   i, alphabet[j]);
            scanf("%d", &count);

            for(int k = 0; k < count; k++)
            {
                int nextState;
                scanf("%d", &nextState);

                transition[i][j][nextState] = 1;
            }
        }
    }

    printf("Enter input string: ");
    scanf("%s", str);

    int current[MAX_STATES] = {0};
    int next[MAX_STATES] = {0};

    current[startState] = 1;

    for(int i = 0; str[i] != '\0'; i++)
    {
        int symbolIndex = -1;

        for(int j = 0; j < symbols; j++)
        {
            if(str[i] == alphabet[j])
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

        for(int j = 0; j < states; j++)
            next[j] = 0;

        for(int s = 0; s < states; s++)
        {
            if(current[s])
            {
                for(int t = 0; t < states; t++)
                {
                    if(transition[s][symbolIndex][t])
                        next[t] = 1;
                }
            }
        }

        for(int j = 0; j < states; j++)
            current[j] = next[j];
    }

    int accepted = 0;

    for(int i = 0; i < finalCount; i++)
    {
        if(current[finalStates[i]])
        {
            accepted = 1;
            break;
        }
    }

    if(accepted)
        printf("String Accepted\n");
    else
        printf("String Rejected\n");

    return 0;
}