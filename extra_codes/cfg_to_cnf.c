#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct
{
    char lhs;
    char rhs[20];
} Production;

Production p[MAX];
int count = 0;

void addProduction(char lhs, char rhs[])
{
    p[count].lhs = lhs;
    strcpy(p[count].rhs, rhs);
    count++;
}

void printGrammar()
{
    printf("\nGrammar:\n");

    for(int i = 0; i < count; i++)
        printf("%c -> %s\n", p[i].lhs, p[i].rhs);
}

int main()
{
    int n;
    char nextVar = 'Z';

    printf("Enter number of productions: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        char lhs;
        char rhs[20];

        printf("Production %d (A abc): ", i + 1);
        scanf(" %c %s", &lhs, rhs);

        addProduction(lhs, rhs);
    }

    printf("\nOriginal Grammar:\n");
    printGrammar();

    /* STEP 1: Replace terminals in long productions */

    for(int i = 0; i < count; i++)
    {
        if(strlen(p[i].rhs) > 1)
        {
            for(int j = 0; p[i].rhs[j]; j++)
            {
                if(islower(p[i].rhs[j]))
                {
                    char tempVar = nextVar--;

                    char temp[2];
                    temp[0] = p[i].rhs[j];
                    temp[1] = '\0';

                    addProduction(tempVar, temp);

                    p[i].rhs[j] = tempVar;
                }
            }
        }
    }

    /* STEP 2: Break long productions */

    int originalCount = count;

    for(int i = 0; i < originalCount; i++)
    {
        int len = strlen(p[i].rhs);

        if(len > 2)
        {
            char current = p[i].lhs;

            for(int j = 0; j < len - 2; j++)
            {
                char newVar = nextVar--;

                char rhs[3];
                rhs[0] = p[i].rhs[j];
                rhs[1] = newVar;
                rhs[2] = '\0';

                addProduction(current, rhs);

                current = newVar;
            }

            char rhs[3];
            rhs[0] = p[i].rhs[len - 2];
            rhs[1] = p[i].rhs[len - 1];
            rhs[2] = '\0';

            addProduction(current, rhs);

            p[i].lhs = '#';  // mark old production
        }
    }

    printf("\nCNF Grammar:\n");

    for(int i = 0; i < count; i++)
    {
        if(p[i].lhs != '#')
            printf("%c -> %s\n", p[i].lhs, p[i].rhs);
    }

    return 0;
}

// 3
// S aBC
// B b
// C c