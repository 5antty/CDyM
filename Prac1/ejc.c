#include <stdio.h>

void convert(unsigned char N)
{
    int dig1 = N % 10;
    dig1 += 48;
    N /= 10;
    int dig2 = N % 10;
    dig2 += 48;
    N /= 10;
    int dig3 = N % 10;
    dig3 += 48;
    printf("Los 3 digitos ASCII son %c %c %c", dig3, dig2, dig1);
}

int main()
{
    unsigned char n;
    printf("Ingrese un numero de 8 bits ");
    scanf("%u", &n);
    convert(n);
    return 0;
}