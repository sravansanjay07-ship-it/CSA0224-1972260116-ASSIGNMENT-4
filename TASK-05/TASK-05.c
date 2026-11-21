#include <stdio.h>

/* Global variable */
int global_token = 1000;

/* Static counter */
int next_token(void)
{
    static int token = 1000;
    return ++token;
}

/* Automatic counter */
int auto_token(void)
{
    int token = 1000;
    return ++token;
}

/* Extern counter */
int extern_token(void)
{
    extern int global_token;
    return ++global_token;
}

int main(void)
{
    int s1, s2, s3;
    int a1, a2, a3;
    int e1, e2, e3;

    s1 = next_token();
    s2 = next_token();
    s3 = next_token();

    a1 = auto_token();
    a2 = auto_token();
    a3 = auto_token();

    e1 = extern_token();
    e2 = extern_token();
    e3 = extern_token();

    printf("static: %d %d %d\n", s1, s2, s3);
    printf("auto  : %d %d %d\n", a1, a2, a3);
    printf("extern: %d %d %d\n", e1, e2, e3);

    printf("register: ");

    for (register int i = 1; i <= 3; i++)
    {
        printf("%d ", i);
    }

    printf("\n");

    return 0;
}
