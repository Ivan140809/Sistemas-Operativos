/* Modulo para manejar operaciones matriciales con hilos
* Archivo: matrizproc.cpp
* Autor: I. Lastra, J. Mejia, A. Arunachalam, C. Quintero
* Contiene: Programa de matrices para manejar suma y maximo con el uso de Hilos de POSIX 
* Fecha: Marzo 2026
*/
#include "matrizproc.h"

int **g_matriz;
int g_tamaño;
char g_operacion[10];
int *g_resultados;

/* Funcion: validar_argumentos
 * Parámetros de Entrada: cantidad de argumentos, tamaño, operacion
 * Valor de salida: verdadero | falso segun verficacion
 * Descripción: Verifica si se esta enviando las entradas correctamente con cada uno de los elementos que incluyen
*  tamaño, uso del programa y operacion con las palabras correspondientes */ 

bool validar_argumentos(int argc, char *argv[], int &tamaño, char *&operacion) {
    tamaño = atoi(argv[1]);
    operacion = argv[2];
    if (argc != 3) {
        cout << "Uso del programa: " << argv[0] << "tamaño matriz" << argv[1] << "sumar | max" << endl;
        return false;
    }

    if (tamaño <= 0) {
        cout << "El tamaño debe ser mayor a 0" << endl;
        return false;
    }

    if (strcmp(operacion, "sumar") != 0 && strcmp(operacion, "max") != 0) {
        cout << "La operación debe ser 'sumar' o 'max'" << endl;
        return false;
    }

    return true;
}

/* Funcion: generar_matriz_aleatoria
 * Parámetros de Entrada: matriz vacia, tamaño de matriz
 * Valor de salida: no tiene
 * Descripción: se encarga con una libreria de aleatorizar los elementos de la matriz 
*  Para despues operarla */

void generar_matriz_aleatoria(int **matriz, int tamaño) {
    srand(time(NULL));
    for (int i = 0; i < tamaño; i++) {
        for (int j = 0; j < tamaño; j++) {
            matriz[i][j] = rand() % 10;
        }
    }
}

/* Funcion: mostrar_matriz
 * Parámetros de Entrada: matriz llena, tamaño de matriz, arreglo de resultados
 * Valor de salida: no tiene
 * Descripción: Muestra la matriz llena con los valores aleatorios correspondientes
 *  */
void mostrar_matriz(int **matriz, int tamaño, int *resultados) {
    cout << "Resultados: " << endl;
    for (int i = 0; i < tamaño; i++) {
        for (int j = 0; j < tamaño; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << resultados[i] << endl;
    }
}

/* Funcion: procesar_filas
 * Parámetros de Entrada: parametro de hilo
 * Valor de salida: no tiene
 * Descripción: Procesa cada una de las filas para que haga la operacion deseada ya seas suma o maximo 
*  usando memoria dinamica */
void *procesar_filas(void *arg) {
    int fila_inicio = *(int *)arg;
    int fila_fin = *((int *)arg + 1);
    free((int *)arg);

    if (strcmp(g_operacion, "sumar") == 0) {
        for (int i = fila_inicio; i < fila_fin; i++) {
            int suma = 0;
            for (int j = 0; j < g_tamaño; j++) {
                suma += g_matriz[i][j];
            }
            g_resultados[i] = suma;
        }
    } else if (strcmp(g_operacion, "max") == 0) {
        for (int i = fila_inicio; i < fila_fin; i++) {
            int maximo = g_matriz[i][0];
            for (int j = 1; j < g_tamaño; j++) {
                if (g_matriz[i][j] > maximo) {
                    maximo = g_matriz[i][j];
                }
            }
            g_resultados[i] = maximo;
        }
    }
    pthread_exit(NULL);
}
/* Funcion: ejecutar_hilos
 * Parámetros de Entrada: matriz llena, operacion, arreglo de resultados, cantidad de hilos dada
 * Valor de salida: no tiene
 * Descripción: Crea los hilos y llama a la funcion anterior para ejecutar lo que se nececite hacer con varios 
*  elementos */

void ejecutar_hilos(int **matriz, int tamaño, char *operacion, int *resultados, int num_hilos) {

    g_matriz = matriz;
    g_tamaño = tamaño;
    strcpy(g_operacion, operacion);
    g_resultados = resultados;
    int filas_por_hilo = tamaño / num_hilos;
    int filas_restantes = tamaño % num_hilos;
    int fila_actual = 0;
    int fila_fin = fila_actual + filas_por_hilo;

    pthread_t *hilos = (pthread_t *) malloc(num_hilos * sizeof(pthread_t));

    if (hilos == NULL) {
        cout << "Asignacion de memoria de hilos nula" << endl;
    }

    for (int i = 0; i < num_hilos; i++) {

        if (i < filas_restantes) {
            fila_fin = fila_fin + 1;
        }

        int *args = (int *)malloc(2 * sizeof(int));
        args[0] = fila_actual;
        args[1] = fila_fin;

        if (pthread_create(&hilos[i], NULL, procesar_filas, (void *)args) != 0) {
            cout << "No se pudo crear el hilo " << i << endl;
            free(hilos);
        }
        fila_actual = fila_fin;
    }

    for (int i = 0; i < num_hilos; i++) {
        if (pthread_join(hilos[i], NULL) != 0) {
            cout << "Error en el join del hilo " << i << endl;
       }
   }

    free(hilos);
}

/* Funcion: main
 * Parámetros de Entrada: argumentos de terminal
 * Valor de salida: no tiene
 * Descripción: Llama a las demas funciones para guiar la ejecucion del programa para que vaya validando
*   */

int main(int argc, char* argv[]) {

    int tamaño = 0;
    char* operacion = NULL;
    int num_hilos = 8; // G6 + 2

    if (!validar_argumentos(argc, argv, tamaño, operacion)) {
        return 1;
    }

    int **matriz = (int **) malloc(tamaño * sizeof(int *));
    int *resultados = (int *)malloc(tamaño * sizeof(int));

    if (matriz == NULL) {
        cout << " No se pudo reservar memoria para la matriz" << endl;
    }

    for (int i = 0; i < tamaño; i++) {
        matriz[i] = (int *)malloc(tamaño * sizeof(int));
        if (matriz[i] == NULL) {
            cout << "No se pudo asignar memoria para la fila " << i << endl;
        }
    }

    generar_matriz_aleatoria(matriz, tamaño);

    if (resultados == NULL) {
        cout << "No se puede generar memoria para la matriz resultante" << endl;
    }

    cout << "Matriz generada " << tamaño << "x" << tamaño<<endl;
    for (int i = 0; i < tamaño; i++) {
        for (int j = 0; j < tamaño; j++) {
            cout << matriz[i][j] << " ";
        }
     cout<<endl;

    }
  cout <<endl;

    ejecutar_hilos(matriz, tamaño, operacion, resultados, num_hilos);

    mostrar_matriz(matriz, tamaño, resultados);

    free(resultados);
    for (int i = 0; i < tamaño; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}
