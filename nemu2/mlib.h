#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100



typedef enum
{
    TK_NOTYPE,
    TK_NUM,
    TK_OP,
    TK_LB,
    TK_RB
} TokenType;

typedef struct token
{
    int id;
    int type;
    char len;
    char str[32];
} Token;

Token tokens[64];


typedef struct
{
    char items[MAX];
    Token items2[MAX];
    int top;
} Stack;

// 初始化栈
void initStack(Stack *s)
{
    s->top = -1;
}

// 判断栈是否为空
bool isEmpty(Stack *s)
{
    return s->top == -1;
}

// 判断栈是否已满
bool isFull(Stack *s)
{
    return s->top == MAX - 1;
}

// 入栈
void push(Stack *s, char c)
{
    if (isFull(s))
    {
        printf("Stack overflow\n");
        exit(1);
    }
    s->items[++(s->top)] = c;
}
void push2(Stack *s, Token c)
{
    if (isFull(s))
    {
        printf("Stack overflow\n");
        exit(1);
    }
    s->items2[++(s->top)] = c;
}
// 出栈
char pop(Stack *s)
{
    if (isEmpty(s))
    {
        printf("Stack underflow\n");
        exit(1);
    }
    return s->items[(s->top)--];
}
Token pop2(Stack *s)
{
    if (isEmpty(s))
    {
        printf("Stack underflow\n");
        exit(1);
    }
    return s->items2[(s->top)--];
}
// 获取栈顶元素
char peek(Stack *s)
{
    if (isEmpty(s))
    {
        printf("Stack is empty\n");
        exit(1);
    }
    return s->items[s->top];
}

// 检查括号是否匹配
bool isMatchingPair(char left, char right)
{
    return (left == '(' && right == ')') ||
           (left == '{' && right == '}') ||
           (left == '[' && right == ']');
}

// 检查表达式中的括号是否匹配
// bool areParenthesesBalanced(const char *expr)
// {
//     Stack s;
//     initStack(&s);

//     for (int i = 0; i < strlen(expr); i++)
//     {
//         if (expr[i] == '(' || expr[i] == '{' || expr[i] == '[')
//         {
//             push(&s, expr[i]);
//         }
//         else if (expr[i] == ')' || expr[i] == '}' || expr[i] == ']')
//         {
//             if (isEmpty(&s))
//             {
//                 return false;
//             }
//             else if (!isMatchingPair(pop(&s), expr[i]))
//             {
//                 return false;
//             }
//         }
//     }

//     return isEmpty(&s);
// }



// bool check(char *expr)
// {
//     bool Balanced = areParenthesesBalanced(expr);
//     if (!Balanced)
//     {
//         exit(1);
//         return false;
//     }

//     if (expr[0] == '(' && expr[strlen(expr) - 1] == ')')
//     {
//         char substr[strlen(expr) - 2];
//         for (size_t i = 1; i < strlen(expr) - 1; i++)
//         {
//             substr[i - 1] = expr[i];
//         }

//         return areParenthesesBalanced(substr);
//     }
//     else
//     {
//         return false;
//     }
// }

// 定义运算符的优先级
int getPriority(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

