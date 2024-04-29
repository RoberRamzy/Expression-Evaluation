#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    float val;
    struct node* next;
} node;

typedef struct stack
{
    node* top;
    int count;
} stack;

node* newnode(float val)
{
    node* n = malloc(sizeof(node));
    if (n != NULL)
    {
        n->val = val;
        n->next = NULL;
    }
    return n;
}

stack* init()
{
    stack* s = malloc(sizeof(stack));
    if (s != NULL)
    {
        s->top = NULL;
        s->count = 0;
    }
    return s;
}

void push(stack* s, float val)
{
    node* n = newnode(val);
    if (n != NULL)
    {
        n->next = s->top;
        s->top = n;
        s->count++;
    }
}

int isEmpty(stack* s)
{
    return (s->count == 0);
}

float peek(stack* s)
{
    if (isEmpty(s))
    {
        return 0.0; // or any other appropriate error handling
    }
    return s->top->val;
}

float pop(stack* s)
{
    if (isEmpty(s))
    {
        return 0.0; // or any other appropriate error handling
    }
    node* temp = s->top;
    float val = temp->val;
    s->top = temp->next;
    free(temp);
    s->count--;
    return val;
}
int getPrecedence(char c)
{
    switch (c)
    {
    case '^':
        return 3;
    case '*':
    case '%':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return 0;
    }
}
int isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^'|| c == '%');
}
int isOperand(char c)
{
    return isdigit(c) || c == '.';
}
char* infixToPostfix(char* infix)
{
    int infixLength = strlen(infix);
    stack* ex = init();
    char* postfix = malloc((infixLength + 1) * sizeof(char));
    int j = 0;

    for (int i = 0; i < infixLength; i++)
    {
        if (isOperand(infix[i]))
        {
            while (isOperand(infix[i]) || infix[i] == '.')
            {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            i--;
        }
        else if (infix[i] == '(')
        {
            push(ex, infix[i]);
        }
        else if (infix[i] == ')')
        {
            while (!isEmpty(ex) && peek(ex) != '(')
            {
                postfix[j++] = pop(ex);
            }
            if (!isEmpty(ex) && peek(ex) == '(')
            {
                pop(ex);
            }
        }
        else if (isOperator(infix[i]))
        {
            while (!isEmpty(ex) && isOperator(peek(ex)) &&
                    getPrecedence(infix[i]) <= getPrecedence(peek(ex)))
            {
                postfix[j++] = pop(ex);
            }
            push(ex, infix[i]);
        }
    }

    while (!isEmpty(ex))
    {
        postfix[j++] = pop(ex);
    }

    postfix[j] = '\0';

    free(ex);

    return postfix;
}
char* infixToPostfixtest(char* infix)
{
    int infixLength = strlen(infix);
    stack* ex = init();
    char* postfix = malloc((infixLength + 1) * sizeof(char));
    int j = 0;

    for (int i = 0; i < infixLength; i++)
    {

        if(infix[i]=='-'&&infix[i+1]!=' ')
        {
            if(i==0||infix[i-1]=='('||infix[i-1]==' ')
            {
                postfix[j++]='-';
                i++;
                while (isOperand(infix[i]) || infix[i] == '.')
                {
                    postfix[j++] = infix[i++];
                }
                postfix[j++] = ' ';
                i--;
            }


        }
        else if (isOperand(infix[i]))
        {

            while (isOperand(infix[i]) || infix[i] == '.')
            {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            i--;

        }
        else if (infix[i] == '(')
        {
            push(ex, infix[i]);
        }
        else if (infix[i] == ')')
        {
            while (!isEmpty(ex) && peek(ex) != '(')
            {
                postfix[j++] = pop(ex);
            }
            if (!isEmpty(ex) && peek(ex) == '(')
            {
                pop(ex);
            }
        }
        else if (isOperator(infix[i]))
        {
            while (!isEmpty(ex) && isOperator(peek(ex)) &&
                    getPrecedence(infix[i]) <= getPrecedence(peek(ex)))
            {
                postfix[j++] = pop(ex);
            }
            push(ex, infix[i]);
        }
    }

    while (!isEmpty(ex))
    {
        postfix[j++] = pop(ex);
    }

    postfix[j] = '\0';

    free(ex);

    return postfix;
}
float evaluate(char x, float op1,float op2)
{

    if(x=='+')return op1+op2;
    if(x=='-')return op1-op2;
    if(x=='*')return op1*op2;
    if(x=='/')
    {
        if (op2 == 0) {printf("Postfix evaluation: INFINITE");exit(0);}
        return op1/op2;
    }
    if(x=='^')return pow(op1,op2);

}
float evaluatePostfix(char* postfix)
{
    stack*s=init();
    float op1,op2,val;
    for(int i = 0; i<strlen(postfix); i++)
    {
        if(postfix[i]=='-'&&(i==0||isdigit(postfix[i+1])))
        {

            i++;
            int j=i;
            float digit=0;
            float decimal=0;
            float result;
            int flag = 0;
            while(postfix[j]!=' ')
            {
                j++;
                if(postfix[j]=='.')
                {
                    flag=1;
                    break;
                }
            }
            for(i; i<j; i++)
            {
                digit+=(postfix[i]-'0')*pow(10,j-i-1);
            }

            i++;
            j=i;
            if(flag)
            {
                while(postfix[j]!=' ')
                {
                    j++;
                }
                int f=0;
                for(i; i<j; i++)
                {
                    decimal+=(postfix[i]-'0')*pow(10,--f);

                }
            }
            result=-1*(decimal+digit);
            push(s,result);
            i--;

        }
        else if(isdigit(postfix[i]))
        {
            int j=i;
            float digit=0;
            float decimal=0;
            float result;
            int flag = 0;
            while(postfix[j]!=' ')
            {
                j++;
                if(postfix[j]=='.')
                {
                    flag=1;
                    break;
                }
            }
            for(i; i<j; i++)
            {
                digit+=(postfix[i]-'0')*pow(10,j-i-1);

            }
            i++;
            j=i;
            if(flag)
            {
                while(postfix[j]!=' ')
                {
                    j++;
                }
                int f=0;
                for(i; i<j; i++)
                {
                    decimal+=(postfix[i]-'0')*pow(10,--f);

                }
            }
            result=(decimal+digit);
            push(s,result);
            i--;
        }
        else if(postfix[i]==' ') {}
        else
        {
            op2=pop(s);
            op1=pop(s);
            if(postfix[i]=='%')
            {if (op2 == 0) {printf("Postfix evaluation:\nError: Division by zero");exit(0);}

                val=(int)op1%(int)op2;
            }
            else
            {
                val=evaluate(postfix[i],op1,op2);
            }
            push(s,val);

        }
    }
    return pop(s);

}

int main()
{
    char infix[100];
    printf("Enter an infix expression: ");
    fgets(infix, sizeof(infix), stdin);
    infix[strcspn(infix, "\n")] = '\0';
    char* postfix = infixToPostfixtest(infix);
    printf("\nPostfix expression: %s\n", postfix);
    printf("\nPostfix evaluation: %f\n",evaluatePostfix(postfix));

    free(postfix);
    return 0;
}
