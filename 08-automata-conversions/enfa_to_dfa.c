#include <stdio.h>

#define MAX 20

int states, symbols;
char alpha[MAX];

int trans[MAX][MAX][MAX];
int eps[MAX][MAX];

int finals[MAX];
int finalCount;

int eClosure(int mask)
{
    int closure = mask;
    int changed = 1;

    while(changed)
    {
        changed = 0;

        for(int i=0;i<states;i++)
        {
            if(closure & (1<<i))
            {
                for(int j=0;j<states;j++)
                {
                    if(eps[i][j] && !(closure & (1<<j)))
                    {
                        closure |= (1<<j);
                        changed = 1;
                    }
                }
            }
        }
    }

    return closure;
}

int main()
{
    printf("States: ");
    scanf("%d",&states);

    printf("Symbols: ");
    scanf("%d",&symbols);

    printf("Alphabet: ");
    scanf("%s",alpha);

    int t;
    printf("Transitions: ");
    scanf("%d",&t);

    for(int i=0;i<t;i++)
    {
        int from,to;
        char ch;

        scanf("%d %c %d",&from,&ch,&to);

        if(ch=='E')
            eps[from][to]=1;
        else
        {
            for(int s=0;s<symbols;s++)
            {
                if(alpha[s]==ch)
                    trans[from][s][to]=1;
            }
        }
    }

    int start;
    printf("Start state: ");
    scanf("%d",&start);

    printf("Final states count: ");
    scanf("%d",&finalCount);

    for(int i=0;i<finalCount;i++)
        scanf("%d",&finals[i]);

    int dfa[100];
    int dfaCount = 0;

    dfa[dfaCount++] = eClosure(1<<start);

    int dfaTrans[100][MAX];

    for(int d=0; d<dfaCount; d++)
    {
        int current = dfa[d];

        for(int s=0; s<symbols; s++)
        {
            int next = 0;

            for(int i=0;i<states;i++)
            {
                if(current & (1<<i))
                {
                    for(int j=0;j<states;j++)
                    {
                        if(trans[i][s][j])
                            next |= (1<<j);
                    }
                }
            }

            next = eClosure(next);

            int found = -1;

            for(int k=0;k<dfaCount;k++)
            {
                if(dfa[k]==next)
                {
                    found = k;
                    break;
                }
            }

            if(found==-1 && next!=0)
            {
                found = dfaCount;
                dfa[dfaCount++] = next;
            }

            dfaTrans[d][s] = found;
        }
    }

    printf("\nDFA Table\n");

    printf("State");
    for(int s=0;s<symbols;s++)
        printf("\t%c",alpha[s]);

    printf("\n");

    for(int i=0;i<dfaCount;i++)
    {
        printf("D%d",i);

        for(int s=0;s<symbols;s++)
        {
            if(dfaTrans[i][s]==-1)
                printf("\t-");
            else
                printf("\tD%d",dfaTrans[i][s]);
        }

        printf("\n");
    }

    return 0;
}
// 3
// 2
// ab
// 3
// 0 E 1
// 1 a 1
// 1 b 2
// 0
// 1
// 2