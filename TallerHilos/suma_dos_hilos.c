#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *numeros;
    int inicio;
    int fin;
    int suma_parcial;
} DatosHilo;

void *sumar_rango(void *arg) {
    DatosHilo *datos = (DatosHilo *)arg;
    datos->suma_parcial = 0;

    for (int i = datos->inicio; i < datos->fin; i++) {
        datos->suma_parcial += datos->numeros[i];
    }

    return NULL;
}

int main(void) {
    const int numeros[] = {5, 8, 3, 10, 7, 2, 6, 9};
    const int total_numeros = (int)(sizeof(numeros) / sizeof(numeros[0]));
    const int mitad = total_numeros / 2;

    pthread_t hilo1;
    pthread_t hilo2;

    DatosHilo datos1 = {numeros, 0, mitad, 0};
    DatosHilo datos2 = {numeros, mitad, total_numeros, 0};

    if (pthread_create(&hilo1, NULL, sumar_rango, &datos1) != 0) {
        perror("Error al crear el hilo 1");
        return EXIT_FAILURE;
    }

    if (pthread_create(&hilo2, NULL, sumar_rango, &datos2) != 0) {
        perror("Error al crear el hilo 2");
        return EXIT_FAILURE;
    }

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    int suma_total = datos1.suma_parcial + datos2.suma_parcial;

    printf("Suma parcial del hilo 1: %d\n", datos1.suma_parcial);
    printf("Suma parcial del hilo 2: %d\n", datos2.suma_parcial);
    printf("Suma total: %d\n", suma_total);

    return EXIT_SUCCESS;
}
