#include <stdio.h>

void invert(int *ar, int t)
{
    int tamanio = t / sizeof(ar[0]);
    int i, aux = 0;
    for (i = 0; i < tamanio / 2; i++)
    {
        aux = ar[i];
        ar[i] = ar[tamanio - 1 - i];
        ar[tamanio - 1 - i] = aux;
    }
}

int main()
{
    int i;
    int arr[] = {1, 2, 3, 4};
    int t = sizeof(arr) / sizeof(arr[0]);

    for (i = 0; i < t; i++)
    {
        printf("%d ", arr[i]);
    }
    invert(arr, sizeof(arr));
    for (i = 0; i < t; i++)
    {
        printf("%d ", arr[i]);
    }
}