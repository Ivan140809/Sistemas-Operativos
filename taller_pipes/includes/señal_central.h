/* Modulo para procesos con pipes
* Archivo: señal_central.h
* Autor: I. Lastra, J. Mejia, A. Arunachalam, C. Quintero
* Contiene: Cabecera con funcion de señal central con escritura de archivo
* Fecha: Abril 2026
*/
#ifndef SEÑAL_CENTRAL_H
#define SEÑAL_CENTRAL_H

#include <string>
using namespace std;
struct Clima {

float temperatura;
float humedad;
float viento;
float precipitacion;

};

void escribir_archivo(Clima& estado, const string& ultimo_sensor);
void leer_actualizar(const char* fifo,Clima& estado);

#endif


