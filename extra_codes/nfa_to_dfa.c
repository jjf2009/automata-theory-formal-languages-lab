#include <stdio.h>

#define MAX 20

int trans[MAX][MAX][MAX];
int dfa[MAX][MAX];
int dfaStates[100];

int main()
{
    int nStates, nSymbols;
    char symbols[10];

    printf("Number of states: ");
    scanf("%d", &nStates);

    printf("Number of symbols: ");
    scanf("%d", &nSymbols);

    printf("Enter symbols: ");
    scanf("%s", symbols);

    int t;
    printf("Number of transitions: ");
    scanf("%d", &t);

    for(int i=0;i<t;i++)
    {
        int from,to;
        char sym;

        printf("Transition (from symbol to): ");
        scanf("%d %c %d",&from,&sym,&to);

        int index;

        for(index=0;index<nSymbols;index++)
        {
            if(symbols[index]==sym)
                break;
        }

        trans[from][index][to]=1;
    }

    int start;
    printf("Start state: ");
    scanf("%d",&start);

    int dfaCount=0;

    dfaStates[dfaCount++] = (1<<start);

    for(int i=0;i<dfaCount;i++)
    {
        int current = dfaStates[i];

        for(int s=0;s<nSymbols;s++)
        {
            int next=0;

            for(int q=0;q<nStates;q++)
            {
                if(current & (1<<q))
                {
                    for(int r=0;r<nStates;r++)
                    {
                        if(trans[q][s][r])
                            next |= (1<<r);
                    }
                }
            }

            int found=-1;

            for(int k=0;k<dfaCount;k++)
            {
                if(dfaStates[k]==next)
                {
                    found=k;
                    break;
                }
            }

            if(found==-1 && next!=0)
            {
                found=dfaCount;
                dfaStates[dfaCount++]=next;
            }

            dfa[i][s]=found;
        }
    }

    printf("\nDFA Transition Table\n");

    printf("State\t");
    for(int i=0;i<nSymbols;i++)
        printf("%c\t",symbols[i]);

    printf("\n");

    for(int i=0;i<dfaCount;i++)
    {
        printf("S%d\t",i);

        for(int j=0;j<nSymbols;j++)
        {
            if(dfa[i][j]==-1)
                printf("-\t");
            else
                printf("S%d\t",dfa[i][j]);
        }

        printf("\n");
    }

    return 0;
}

// Number of states: 3
// Number of symbols: 2
// Enter symbols: ab

// Number of transitions: 4

// 0 a 0
// 0 a 1
// 0 b 0
// 1 b 2

// Start state: 0