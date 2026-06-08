#include <stdio.h>

#define MAX 100

typedef struct
{
    int from;
    char symbol;
    int to;
} Transition;

typedef struct
{
    int start;
    int end;
} NFA;

Transition trans[MAX];
NFA stack[MAX];

int tCount = 0;
int top = -1;
int state = 0;

void addTransition(int from, char symbol, int to)
{
    trans[tCount].from = from;
    trans[tCount].symbol = symbol;
    trans[tCount].to = to;
    tCount++;
}

void push(NFA x)
{
    stack[++top] = x;
}

NFA pop()
{
    return stack[top--];
}

int newState()
{
    return state++;
}

int main()
{
    char regex[50];

    printf("Enter postfix regex: ");
    scanf("%s", regex);

    for(int i=0; regex[i]!='\0'; i++)
    {
        char c = regex[i];

        if(c=='*')
        {
            NFA f = pop();

            int s = newState();
            int e = newState();

            addTransition(s,'E',f.start);
            addTransition(s,'E',e);
            addTransition(f.end,'E',f.start);
            addTransition(f.end,'E',e);

            push((NFA){s,e});
        }

        else if(c=='.')
        {
            NFA f2 = pop();
            NFA f1 = pop();

            addTransition(f1.end,'E',f2.start);

            push((NFA){f1.start,f2.end});
        }

        else if(c=='|')
        {
            NFA f2 = pop();
            NFA f1 = pop();

            int s = newState();
            int e = newState();

            addTransition(s,'E',f1.start);
            addTransition(s,'E',f2.start);

            addTransition(f1.end,'E',e);
            addTransition(f2.end,'E',e);

            push((NFA){s,e});
        }

        else
        {
            int s = newState();
            int e = newState();

            addTransition(s,c,e);

            push((NFA){s,e});
        }
    }

    NFA result = pop();

    printf("\nTransitions:\n");
    printf("From\tInput\tTo\n");

    for(int i=0;i<tCount;i++)
    {
        printf("q%d\t%c\tq%d\n",
               trans[i].from,
               trans[i].symbol,
               trans[i].to);
    }

    printf("\nStart State : q%d\n", result.start);
    printf("Final State : q%d\n", result.end);

    return 0;
}