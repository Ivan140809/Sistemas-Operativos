#include <iostream>
#include <cstring>
#include <cctype>
#include <unistd.h>
#include <sys/wait.h>
#include "matrizsum.h"
using namespace std;

void validarArgumentos(int argc, char* argv[], int& m, int& n){
/* Función: validarArgumentos
 * Parámetros de entrada:
 *   argc - número de argumentos recibidos
 *   argv - arreglo de argumentos
 *   m, n - referencias donde se almacenan los valores convertidos
 * Valor de salida: no retorna valor
 * Descripción:
 *   Verifica que el usuario ingrese exactamente dos argumentos,
 *   que sean enteros positivos y que n sea divisor de m.
 */

if(argc != 3){

cerr<<" Uso del programa: ./matrizsum m n"<<endl;
	exit(1);
}

for (int i = 1; i <= 2; ++i) {
 // Validación de que los argumentos sean números positivos
        if (argv[i] == NULL || strlen(argv[i]) == 0) {
            cerr << "Error: argumentos vacios. " << endl;
            exit(1);
        }
        for (size_t j = 0; j < std::strlen(argv[i]); ++j) {
            if (!isdigit(static_cast<unsigned char>(argv[i][j]))) {
                cerr << "Error: los argumentos deben ser enteros positivos.\n";
                exit(1);
            }
        }
    }
   m= atoi(argv[1]);
   n= atoi(argv[2]);
if (m <= 0 || n <= 0) {
        cerr << "Error: m y n deben ser mayores que 0."<<endl;
        exit(1);
    }

    if (m % n != 0) {
        cerr << "Error: n debe ser divisor de m." <<endl;;
        exit(1);
    }
}
/* Función: crearMatriz
 * Parámetros de entrada:
 *   m - dimensión de la matriz cuadrada
 * Valor de salida:
 *   Retorna un apuntador a la matriz dinámica creada.
 * Descripción:
 *   Reserva memoria dinámica para una matriz de m x m
 *   elementos almacenados en forma lineal.
 */


int* crearMatriz(int m){
    int* matriz = new int[m * m];
    return matriz;
}
/* Función: llenarMatriz
 * Parámetros de entrada:
 *   matriz - apuntador a la matriz dinámica
 *   m - dimensión de la matriz
 * Valor de salida: no retorna valor
 * Descripción:
 *   Llena la matriz con valores consecutivos desde 1
 *   hasta m*m.
 */
void llenarMatriz(int *matriz, int m) {
for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            matriz[i*m+j] = i*m+j +1;
        }
    }
}
/* Función: ejecutarProcesos
 * Parámetros de entrada:
 *   matriz - matriz dinámica a procesar
 *   m - dimensión de la matriz
 *   n - número de procesos a crear
 * Valor de salida: no retorna valor
 * Descripción:
 *   Crea n procesos hijos utilizando fork().
 *   Cada hijo suma m/n filas de la matriz y muestra
 *   los valores sumados junto con su PID.
 *   El proceso padre espera la finalización de todos
 *   los procesos hijos usando wait().
 */
void ejecutarProcesos(int* matriz, int m, int n){
 int filas_por_proceso = m / n;

    for (int k = 0; k < n; ++k) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(1);
        }

        if (pid == 0) { // Código ejecutado únicamente por el hijo 
            int inicio = k * filas_por_proceso;
            int fin    = inicio + filas_por_proceso;

            for (int fila = inicio; fila < fin; ++fila) {
                long suma = 0;

                cout << "PID " << getpid() << " - Fila " << fila << ": ";

                for (int col = 0; col < m; ++col) {
                    int val = matriz[fila * m + col];
                    suma += val;
                    cout << val;
                    if (col != m - 1) cout << " + ";
                }

                cout << " = " << suma << " "<<endl;
            }

            _exit(0); // Finaliza el proceso hijo
        }
    }
// El proceso padre espera a que terminen todos los hijos
    for (int i = 0; i < n; ++i) {
        wait(NULL); 
    }
}
/* Función: liberarMatriz
 * Parámetros de entrada:
 *   matriz - apuntador a la matriz dinámica
 * Valor de salida: no retorna valor
 * Descripción:
 *   Libera la memoria dinámica reservada para la matriz.
 */

void liberarMatriz(int* matriz) {
    delete[] matriz;
}

/* Función: main
 * Parámetros de entrada:
 *   argc - número de argumentos
 *   argv - arreglo de argumentos
 * Valor de salida:
 *   Retorna 0 si la ejecución fue correcta.
 * Descripción:
 *   Coordina la ejecución del programa:
 *   valida argumentos, crea la matriz,
 *   ejecuta los procesos y libera memoria.
 */
int main(int argc, char* argv[]) {
    int m = 0, n = 0;

    validarArgumentos(argc, argv, m, n);

    int* matriz = crearMatriz(m);
    llenarMatriz(matriz, m);

    ejecutarProcesos(matriz, m, n);

    liberarMatriz(matriz);
    return 0;
}
