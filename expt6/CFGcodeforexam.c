#include <stdio.h>
#include <string.h>

#define MAX_PROD 20
#define MAX_LEN 100

typedef struct
{
    char lhs;
    char rhs[MAX_LEN];
} Production;

Production p[MAX_PROD];

int prodCount;
char startSymbol;

int derive(char current[], char target[])
{
    if(strcmp(current, target) == 0)
        return 1;

    if(strlen(current) > strlen(target))
        return 0;

    for(int i = 0; current[i] != '\0'; i++)
    {
        if(current[i] >= 'A' && current[i] <= 'Z')
        {
            for(int j = 0; j < prodCount; j++)
            {
                if(p[j].lhs == current[i])
                {
                    char newStr[MAX_LEN];

                    strncpy(newStr, current, i);
                    newStr[i] = '\0';

                    strcat(newStr, p[j].rhs);
                    strcat(newStr, current + i + 1);

                    if(derive(newStr, target))
                        return 1;
                }
            }

            return 0;
        }
    }

    return 0;
}

int main()
{
    int n;
    char target[MAX_LEN];

    printf("Enter start symbol: ");
    scanf(" %c", &startSymbol);

    printf("Enter number of productions: ");
    scanf("%d", &n);

    prodCount = n;

    for(int i = 0; i < n; i++)
    {
        printf("Production %d (A abc): ", i + 1);

        scanf(" %c %s",
              &p[i].lhs,
              p[i].rhs);
    }

    printf("Enter string: ");
    scanf("%s", target);

    char start[2];

    start[0] = startSymbol;
    start[1] = '\0';

    if(derive(start, target))
        printf("ACCEPTED\n");
    else
        printf("REJECTED\n");

    return 0;
}