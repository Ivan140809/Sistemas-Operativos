/* Modulo para procesos con pipes
* Archivo: señal_central.h
* Autor: I. Lastra, J. Mejia, A. Arunachalam, C. Quintero
* Contiene: Cabecera con funciones para funciones de señales
* Fecha: Abril 2026
*/

#ifndef SEÑAL_SENSOR_H
#define SEÑAL_SENSOR_H

void manejador_señal(int señal);

float generar_temp();
float generar_hum();
float generar_viento();
float generar_precip();

void enviar_fifo(const char* fifo, const char* sensor, float valor);

#endif

