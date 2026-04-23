#include "señal_central.h"
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <csignal>
#include <sstream>
#include <iomanip>

using namespace std;

void escribir_archivo(Clima& estado, const string& ultimo_sensor) {
    ofstream archivo("clima_actual.txt");

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo" << endl;
        return;
    }

    archivo << fixed << setprecision(2);

    archivo << "Estado actual del clima:" << endl;
    archivo << "Ultimo sensor actualizado: " << ultimo_sensor << endl;
    archivo << "Temperatura: " << estado.temperatura << " C" << endl;
    archivo << "Humedad: " << estado.humedad << " %" << endl;
    archivo << "Velocidad del viento: " << estado.viento << " m/s" << endl;
    archivo << "Precipitacion: " << estado.precipitacion << " mm" << endl;

    archivo.close();
}

void leer_y_actualizar(const char* fifo, Clima& estado) {
    int fd = open(fifo, O_RDONLY);
    if (fd == -1) {
        perror("Error al abrir FIFO en central");
        return;
    }

    char buffer[100] = {0};
    int n = read(fd, buffer, sizeof(buffer) - 1);

    if (n > 0) {
        string nombre;
        float valor;
        stringstream ss(buffer);
        ss >> nombre >> valor;

        if (nombre == "temperatura") {
            estado.temperatura = valor;
        } else if (nombre == "humedad") {
            estado.humedad = valor;
        } else if (nombre == "viento") {
            estado.viento = valor;
        } else if (nombre == "precipitacion") {
            estado.precipitacion = valor;
        }

        escribir_archivo(estado, nombre);
        cout << "Recibido: " << buffer << endl;
    }

    close(fd);
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cerr << "Uso: " << argv[0]
             << " <pid_temperatura> <pid_humedad> <pid_viento> <pid_precipitacion>"
             << endl;
        return 1;
    }

    pid_t pid_temp = atoi(argv[1]);
    pid_t pid_hum = atoi(argv[2]);
    pid_t pid_viento = atoi(argv[3]);
    pid_t pid_prec = atoi(argv[4]);

    const char* fifo_temp = "/tmp/fifo_temperatura_señal";
    const char* fifo_hum = "/tmp/fifo_humedad_señal";
    const char* fifo_viento = "/tmp/fifo_viento_señal";
    const char* fifo_prec = "/tmp/fifo_precipitacion_señal";

    mkfifo(fifo_temp, 0666);
    mkfifo(fifo_hum, 0666);
    mkfifo(fifo_viento, 0666);
    mkfifo(fifo_prec, 0666);

    Clima estado;
    estado.temperatura = 0.0f;
    estado.humedad = 0.0f;
    estado.viento = 0.0f;
    estado.precipitacion = 0.0f;

    while (true) {
        cout << "Solicitando datos a los procesos con pipes" << endl;

        kill(pid_temp, SIGUSR1);
        kill(pid_hum, SIGUSR1);
        kill(pid_viento, SIGUSR1);
        kill(pid_prec, SIGUSR1);

        leer_y_actualizar(fifo_temp, estado);
        leer_y_actualizar(fifo_hum, estado);
        leer_y_actualizar(fifo_viento, estado);
        leer_y_actualizar(fifo_prec, estado);

        sleep(5);
    }

    return 0;
}
