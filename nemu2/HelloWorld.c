#include <stdio.h>
#include <string.h>
void main()
{
    char str[] = "abc1234";
    char str2[] = "abc1234";
    str[1] = 'E';
    printf("Hello World: str len= %d\n", strlen(str));

    printf("Hello World: str = %s\n", str);
    printf("Hello World: str2 = %s\n", str2);


    printf("Hello World: str ptr = %p\n", str);
    printf("Hello World: str2 ptr = %p\n", str2);
}