#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>
#include <assert.h>
#include "mlib.h"

#define MAX_EXPR_LEN 100
int pos = 0;

void expressionerror()
{
    printf("expression is error.\n");
}

bool areParenthesesBalanced(int p, int q)
{
    Stack s;
    initStack(&s);

    for (int i = p; i <= q; i++)
    {
        if (tokens[i].type == TK_LB)
        {
            push(&s, tokens[i].str[0]);
        }
        else if (tokens[i].type == TK_RB)
        {
            if (isEmpty(&s))
            {
                return false;
            }
            else if (!isMatchingPair(pop(&s), tokens[i].str[0]))
            {
                return false;
            }
        }
    }

    return isEmpty(&s);
}

void printtokens()
{

    for (size_t i = 0; i < 64; i++)
    {
        Token t = tokens[i];
        if (t.type != TK_NOTYPE)
        {
            fprintf(stderr, "token type:%d  token: %s\n", t.type, t.str);
        }
    }
}
int getsize(int p, int q)
{
    int len = 0;
    for (size_t i = p; i <= q; i++)
    {
        len += tokens[i].len;
    }
    return len;
}
void printstr(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        printf("%c", str[i]);
        i++;
    }
    printf("\n");
}

bool check_Parentheses(int p, int q)
{
    Stack s;
    initStack(&s);

    for (int i = p; i <= q; i++)
    {
        if (tokens[i].type == TK_LB)
        {
            push2(&s, tokens[i]);
        }
        else if (tokens[i].type == TK_RB)
        {
            assert(!isEmpty(&s));
            Token c = pop2(&s);
            if (i == q)
            {
                if (c.index == p)
                {
                    return true;
                }
            }
        }
    }

    return false;
}
int findMainOperatorPos(int p, int q)
{
    int minPriority = MAX;
    int mainOperatorIndex = -1;
    int brackets = 0;

    for (int i = p; i <= q; i++)
    {
        Token t = tokens[i];

        if (t.type == TK_LB)
        {
            brackets++;
        }
        else if (t.type == TK_RB)
        {
            brackets--;
        }
        else if (brackets == 0 && t.type == TK_OP)
        {
            char c = t.str[0];
            int priority = getPriority(c);
            if (priority <= minPriority)
            {
                minPriority = priority;
                mainOperatorIndex = i;
            }
        }
    }

    return mainOperatorIndex;
}
int eval(int p, int q)
{
    printf("eval   [p: %d  %d q]\n", p,q);
    if (p > q)
    {
        // error
        assert(false);
        exit(1);
        return 0;
    }
    else if (p == q)
    {
        // single number
        assert(tokens[p].type == TK_NUM);
        return atoi(tokens[p].str);
    }
    else if (check_Parentheses(p, q))
    {
        return eval(p + 1, q - 1);
    }
    else
    {
        int op_pos = findMainOperatorPos(p, q);
        assert(op_pos != -1);
        assert(tokens[op_pos].type == TK_OP);

        printf("main op pos: %d \n", op_pos);
        printf("p: %d \n", p);
        
        int val1 = eval(p, op_pos - 1);
        int val2 = eval(op_pos + 1, q);

        
        switch (tokens[op_pos].str[0])
        {
        case '+':
            return val1 + val2;
            break;
        case '-':
            return val1 - val2;
            break;
        case '*':
            return val1 * val2;
            break;
        case '/':
            return val1 / val2;
            break;
        default:
            break;
        }
        exit(1);
        return 0;
    }
}
void match_regex(const char *expr)
{
    regex_t regex_num;
    regex_t regex_op;
    regex_t regex_lb;
    regex_t regex_rb;
    regmatch_t pmatch[1];
    const char *pattern_num = "[0-9]+";
    const char *pattern_op = "[-+*/]";
    const char *pattern_lb = "[(]";
    const char *pattern_rb = "[)]";
    const char *p = expr;
    int reti;

    TokenType tt = TK_NOTYPE;
    // 编译正则表达式
    reti = regcomp(&regex_num, pattern_num, REG_EXTENDED);
    if (reti)
    {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
    reti = regcomp(&regex_op, pattern_op, REG_EXTENDED);
    if (reti)
    {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
    reti = regcomp(&regex_lb, pattern_lb, REG_EXTENDED);
    if (reti)
    {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
    reti = regcomp(&regex_rb, pattern_rb, REG_EXTENDED);
    if (reti)
    {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    regmatch_t goodmatch;
    goodmatch.rm_so = MAX_EXPR_LEN;
    // 匹配正则表达式
    while (*p != '\0')
    {

        reti = regexec(&regex_num, p, 1, pmatch, 0);
        if (reti == 0)
        {
            if (pmatch[0].rm_so < goodmatch.rm_so)
            {
                goodmatch = pmatch[0];
                tt = TK_NUM;
            }
        }

        reti = regexec(&regex_op, p, 1, pmatch, 0);
        if (reti == 0)
        {
            if (pmatch[0].rm_so < goodmatch.rm_so)
            {
                goodmatch = pmatch[0];
                tt = TK_OP;
            }
        }
        reti = regexec(&regex_lb, p, 1, pmatch, 0);
        if (reti == 0)
        {
            if (pmatch[0].rm_so < goodmatch.rm_so)
            {
                goodmatch = pmatch[0];
                tt = TK_LB;
            }
        }
        reti = regexec(&regex_rb, p, 1, pmatch, 0);
        if (reti == 0)
        {
            if (pmatch[0].rm_so < goodmatch.rm_so)
            {
                goodmatch = pmatch[0];
                tt = TK_RB;
            }
        }

        if (goodmatch.rm_so != MAX_EXPR_LEN)
        {
            Token token;
            token.index = pos;
            token.type = tt;
            int t = 0;
            int start = goodmatch.rm_so;
            int end = goodmatch.rm_eo;
            token.len = end - start;
            printf("TK so:%d eo:%d\n", start, end);
            printf("TK:%d Matched: ", tt);
            for (int i = start; i < end; i++)
            {
                putchar(p[i]);
                token.str[t++] = p[i];
            }
            token.str[t] = '\0';
            printf("\n");
            tokens[pos++] = token;

            p += end; // 移动指针到下一个匹配位置
            goodmatch.rm_so = MAX_EXPR_LEN;
        }
    }

    // 释放正则表达式
    regfree(&regex_num);
    regfree(&regex_op);
    regfree(&regex_lb);
    regfree(&regex_rb);
}

int main()
{
    char expr[MAX_EXPR_LEN];

    printf("Enter an expression: ");
    if (fgets(expr, sizeof(expr), stdin) != NULL)
    {
        // 移除换行符
        size_t len = strlen(expr);
        if (len > 0 && expr[len - 1] == '\n')
        {
            expr[len - 1] = '\0';
        }

        removeSpaces(expr);

        match_regex(expr);

        printtokens();

        int tokennum = 0;
        for (size_t i = 0; i < 64; i++)
        {
            Token t = tokens[i];
            if (t.type != TK_NOTYPE)
            {
                tokennum++;
            }
        }
        printf("tokens num: %d\n", tokennum);



        bool Balanced = areParenthesesBalanced(0, tokennum - 1);
        if (!Balanced)
        {
            printf("expression is error.\n");
            return false;
        }



        int x = eval(0, tokennum - 1);

        printf("expression value: %d\n", x);
    }
    else
    {
        fprintf(stderr, "Error reading input\n");
    }

    return 0;
}