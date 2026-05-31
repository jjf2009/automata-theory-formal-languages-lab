#include <stdio.h>
#include <string.h>

int main()
{
    int states, symbols;
    char alphabet[10];

    int startState;

    int finalCount;
    int finalStates[10];

    int transition[20][10];

    char str[100];

    printf("Enter number of states: ");
    scanf("%d", &states);

    printf("Enter number of symbols: ");
    scanf("%d", &symbols);

    printf("Enter alphabet: ");
    for(int i=0;i<symbols;i++)
        scanf(" %c",&alphabet[i]);

    printf("Enter start state: ");
    scanf("%d",&startState);

    printf("Enter number of final states: ");
    scanf("%d",&finalCount);

    printf("Enter final states: ");
    for(int i=0;i<finalCount;i++)
        scanf("%d",&finalStates[i]);

    printf("Enter transition table:\n");

    for(int i=0;i<states;i++)
    {
        for(int j=0;j<symbols;j++)
        {
            printf("δ(q%d,%c)=q",i,alphabet[j]);
            scanf("%d",&transition[i][j]);
        }
    }

    printf("Enter input string: ");
    scanf("%s",str);

    int currentState = startState;

    for(int i=0; str[i]!='\0'; i++)
    {
        int symbolIndex = -1;

        for(int j=0;j<symbols;j++)
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

        currentState =
            transition[currentState][symbolIndex];
    }

    int accepted = 0;

    for(int i=0;i<finalCount;i++)
    {
        if(currentState == finalStates[i])
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