/* Modulo para manejar operaciones matriciales con hilos
* Archivo: matrizproc.h
* Autor: I. Lastra, J. Mejia, A. Arunachalam, C. Quintero
* Contiene: Programa de matrices para manejar suma y maximo con el uso de Hilos de POSIX
* Fecha: Marzo 2026
*/

#ifndef MATRIZPROC_H
#define MATRIZPROC_H


#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

bool validar_argumentos(int argc, char *argv[], int &tamaño, char *&operacion);
void generar_matriz_aleatoria(int **matriz, int tamaño);
void mostrar_matriz(int **matriz, int tamaño, int *resultados);
void *procesar_filas(void *arg);
void ejecutar_hilos(int **matriz, int tamaño, char *operacion, int *resultados, int num_hilos);

#endif

