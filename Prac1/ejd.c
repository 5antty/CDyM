#include <stdio.h>
#include <unistd.h> // Para la función sleep()

void enviarBitsSerie(unsigned char numero)
{
    for (int i = 0; i < 8; i++)
    {
        printf("%d\n", (numero >> i) & 1); // Extrae y envía el bit menos significativo
        // fflush(stdout);                    // Asegura que el bit se imprima inmediatamente
        sleep(1); // Espera 1 segundo antes de enviar el siguiente bit
    }
}

int main()
{
    unsigned char numero = 0b10101010; // Número de prueba
    enviarBitsSerie(numero);
    return 0;
}
