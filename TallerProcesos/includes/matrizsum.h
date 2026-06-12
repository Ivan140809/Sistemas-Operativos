#ifndef MATRIZSUM_H
#define MATRIZSUM_H


void validarArgumentos(int argc, char* argv[], int& m, int& n);

int* crearMatriz(int m);

void llenarMatriz(int* matriz, int m);


void ejecutarProcesos(int* matriz, int m, int n);

void liberarMatriz(int* matriz);

#endif
