#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

struct ThreadArgs {
    int *arr;
    int start;
    int end;
    int sum;
};

void *sumar_rango(void *arg) {
 ThreadArgs *args = static_cast<ThreadArgs *>(arg);
 args->sum = 0;
  for (int i = args->start; i < args->end; ++i) {
     args->sum += args->arr[i];
   }
  pthread_exit(NULL);
}

void ejecutar_hilos(int arreglo[], int m, int num_hilos) {
    if (num_hilos <= 0) {
        num_hilos = 1;
    }
    if (num_hilos > m) {
        num_hilos = m;
    }

    pthread_t *hilos = new pthread_t[num_hilos];
    ThreadArgs *args = new ThreadArgs[num_hilos];
    int base = m / num_hilos;
    int extra = m % num_hilos;
    int inicio = 0;

    for (int i = 0; i < num_hilos; ++i) {
        int fin = inicio + base + (i < extra ? 1 : 0);
        args[i].arr = arreglo;
        args[i].start = inicio;
        args[i].end = fin;
        args[i].sum = 0;
        if (pthread_create(&hilos[i], NULL, sumar_rango, &args[i]) != 0) {
            cerr << "Error al crear el hilo " << i << endl;
            delete[] hilos;
            delete[] args;
            return;
        }
        inicio = fin;
    }

    int suma_total = 0;
    for (int i = 0; i < num_hilos; ++i) {
        pthread_join(hilos[i], NULL);
        suma_total += args[i].sum;
    }

    cout << "Suma total con " << num_hilos << " hilos es " << suma_total << endl;
    delete[] hilos;
    delete[] args;
}

void ejecutar_proceso(int arreglo[], int m, int num_procesos) {
    if (num_procesos <= 0) {
        num_procesos = 1;
    }
    if (num_procesos > m) {
        num_procesos = m;
    }
    int base = m / num_procesos;
    int extra = m % num_procesos;
    for (int k = 0; k < num_procesos; k++) {
        pid_t pid = fork();
        if(pid < 0) {
         perror("fork");
         exit(1);
      }
        if (pid == 0) {
            int inicio = k * base + min(k, extra);
            int fin = inicio + base + (k < extra ? 1 : 0);
            int suma = 0;
            cout << "Hijo" << getpid() << " rango " << inicio << "-" << fin - 1 << ": ";
            for (int i=inicio; i<fin; i++) {
                suma += arreglo[i];
                cout << arreglo[i];
                if (i+1<fin) {
                    cout << " ";
                }
            }
            cout << " = " << suma << endl;
            _exit(0);
        }
    }

    for (int i = 0; i < num_procesos; ++i) {
        wait(NULL);
    }

    cout << "Proceso padre " << getpid() << " ha terminado" << endl;
}

int main() {
    cout << "Bienvenido a sumar un arreglo con procesos e hilos" << endl;
    int arreglo[100];
    int m;

    cout << "Ingresa cantidad de datos ";
    cin >> m;
    if (m <= 0) {
        cerr << "Cantidad de datos invalida." << endl;
        return 1;
    }

    cout << "Ingresa " << m << " valores enteros:" << endl;
    for (int i = 0; i < m; ++i) {
        cin >> arreglo[i];
    }

    int num_procesos;
    cout << "Ingresa numero de procesos: ";
    cin >> num_procesos;
    ejecutar_proceso(arreglo, m, num_procesos);
    int num_hilos;
    cout << "Ingresa numero de hilos: ";
    cin >> num_hilos;
    ejecutar_hilos(arreglo, m, num_hilos);
    return 0;
}
