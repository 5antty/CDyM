#include <stdio.h>

int suma(unsigned char N)
{
    int i;
    int sum = 0;
    for (i = 1; i <= N; i++)
    {
        sum += i;
    }
    return sum;
}

int main()
{
    unsigned char N = 321;
    printf("n es %u", N);
    int total;
    total = suma(N);
    printf("La suma desde 1 hasta N es %d", total);
    return 0;
}
