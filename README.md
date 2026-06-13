# Sistemas Operativos - Talleres

[![C](https://img.shields.io/badge/language-C-555555?logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language)) [![C++](https://img.shields.io/badge/language-C%2B%2B-00599C?logo=c%2B%2B&logoColor=white)](https://en.wikipedia.org/wiki/C%2B%2B) [![POSIX Threads](https://img.shields.io/badge/library-pthread-4EAA25?logo=linux&logoColor=white)](https://en.wikipedia.org/wiki/POSIX_Threads) [![Bash](https://img.shields.io/badge/tool-Bash-4EAA25?logo=gnu-bash&logoColor=white)](https://www.gnu.org/software/bash/)

Este repositorio contiene varios ejercicios prácticos de Sistemas Operativos en C/C++ que cubren:
- Hilos POSIX usando `pthread`
- Procesos con POSIX
- Comunicación entre procesos con pipes y señales
- Manejo de matrices y operaciones básicas concurrentes

## Estructura del repositorio
- `PracticaHilosProcesos/`
  - `sumaval.cpp`
- `TallerHilos/`
  - `matrizproc.cpp`
  - `matrizproc.h`
  - `suma_dos_hilos.c`
- `TallerProcesos/`
  - `matrizsum.cpp`
  - `matrizsum.h`
- `taller_pipes/`
  - `señal_central.cpp`
  - `señal_central.h`
  - `señal_sensor.h`
  - `señal_sensor_temp.cpp`
  - `señal_sensor_hum.cpp`
  - `señal_sensor_vie.cpp`
  - `señal_sensor_preci.cpp`

## Descripción de cada módulo
### `PracticaHilosProcesos/sumaval.cpp`
Programa orientado a ejercicios de procesos e hilos para sumar elementos de un arreglo. El código actual incluye estructuras básicas para:
- lectura de un arreglo por teclado
- creación de procesos con `fork`
- uso de hilos con `pthread`


### `TallerHilos/`

#### `matrizproc.cpp` y `matrizproc.h`
Ejercicio de operaciones concurrentes sobre matrices con hilos POSIX.
- Genera una matriz cuadrada de tamaño `m x m` con valores aleatorios.
- Divide el trabajo entre varios hilos.
- Calcula la suma de cada fila o el máximo de cada fila según la operación seleccionada.

Uso esperado:
```bash
g++ -pthread TallerHilos/matrizproc.cpp -o TallerHilos/matrizproc
./TallerHilos/matrizproc <tamaño> sumar
./TallerHilos/matrizproc <tamaño> max
```

#### `suma_dos_hilos.c`
Ejemplo sencillo de dos hilos que calculan la suma de un arreglo en dos rangos.
- Un hilo suma la primera mitad.
- El otro hilo suma la segunda mitad.
- Se muestra la suma parcial de cada hilo y la suma total.

Compilar y ejecutar:
```bash
gcc -pthread TallerHilos/suma_dos_hilos.c -o TallerHilos/suma_dos_hilos
./TallerHilos/suma_dos_hilos
```

### `TallerProcesos/`

#### `matrizsum.cpp` y `matrizsum.h`
Programa que utiliza procesos con `fork()` para sumar filas de una matriz.
- Valida argumentos de línea de comandos `m` y `n`.
- `m` es la dimensión de la matriz cuadrada.
- `n` es el número de procesos hijos.
- Cada proceso hijo suma `m / n` filas y muestra los resultados.

Uso:
```bash
g++ TallerProcesos/matrizsum.cpp -o TallerProcesos/matrizsum
./TallerProcesos/matrizsum <m> <n>
```

### `taller_pipes/`

Este taller muestra un ejemplo de comunicación entre procesos usando pipes nominales. 

#### `señal_central.cpp` y `señal_central.h`
- Actúa como proceso central que solicita datos a procesos sensores.
- Envía `SIGUSR1` a cada sensor para que envíen su valor.
- Lee los datos desde cuatro FIFOs distintos.
- Actualiza un archivo `clima_actual.txt` con el último dato recibido.

#### `señal_sensor_*.cpp` y `señal_sensor.h`
Cada sensor posee su propio proceso y FIFO:
- `señal_sensor_temp.cpp` — temperatura
- `señal_sensor_hum.cpp` — humedad
- `señal_sensor_vie.cpp` — viento
- `señal_sensor_preci.cpp` — precipitación

Cada sensor espera la señal `SIGUSR1` y luego escribe su valor en el pipe correspondiente.


## Compilación general
A continuación hay algunos ejemplos de compilación para los principales ejercicios:

```bash
# Compilacion para el taller de hilos
g++ -pthread TallerHilos/matrizproc.cpp -o TallerHilos/matrizproc
gcc -pthread TallerHilos/suma_dos_hilos.c -o TallerHilos/suma_dos_hilos

# Compilacion para el taller de procesos
g++ TallerProcesos/matrizsum.cpp -o TallerProcesos/matrizsum

# Compilacion para el taller de pipes:
g++ -pthread taller_pipes/señal_central.cpp -o taller_pipes/señal_central
g++ -pthread taller_pipes/señal_sensor_temp.cpp -o taller_pipes/señal_sensor_temp
g++ -pthread taller_pipes/señal_sensor_hum.cpp -o taller_pipes/señal_sensor_hum
g++ -pthread taller_pipes/señal_sensor_vie.cpp -o taller_pipes/señal_sensor_vie
g++ -pthread taller_pipes/señal_sensor_preci.cpp -o taller_pipes/señal_sensor_preci
```

## Ejecución recomendada para `taller_pipes`
1. Abrir varias terminales.
2. Ejecutar cada sensor por separado:
```bash
./taller_pipes/señal_sensor_temp
./taller_pipes/señal_sensor_hum
./taller_pipes/señal_sensor_vie
./taller_pipes/señal_sensor_preci
```
3. Copiar los PID que imprime cada sensor.
4. Ejecutar el proceso central con los PID en el orden: temperatura, humedad, viento, precipitación.
```bash
./taller_pipes/señal_central <pid_temp> <pid_hum> <pid_viento> <pid_prec>
```
## Autor
Repositorio de ejercicios de la materia de Sistemas Operativos.
