#include "señal_sensor.h"
#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <csignal>
#include <cstring>

using namespace std;

const char* fifo = "/tmp/fifo_viento_señal";

float generar_temp() {
return 0.0f;
}

float generar_hum() {
return 0.0f;
}

float generar_vie() {
return( rand() % 300) / 10.0f;
}

float generar_precip() {
return 0.0f;
}

void enviar_fifo(const char* fifo, const char* sensor, float valor) {
int fd = open(fifo, O_WRONLY);
if(fd == -1) {
perror("Error al abrir el FIFO");
return;
}

char buffer [100];
snprintf(buffer,sizeof(buffer), "%s%.2f", sensor ,valor);
write(fd,buffer, strlen(buffer) + 1);
close(fd);

cout<<"sensor: "<< sensor << "enviado: " <<buffer<<endl;
}

void manejador_señal(int sig){
if(sig == SIGUSR1) {
float valor= generar_temp();
enviar_fifo(fifo, "viento", valor);
  }
}

int main() {
srand(time(NULL) + getpid());

mkfifo(fifo,0666);
chmod(fifo,0666);
signal (SIGUSR1, manejador_señal);

cout <<"PID vie: " << getpid() <<endl;

while(true) {
pause ();
   }
return 0;

}
