#include <iostream>
#include <pthread>
#include <unistd.h>
#include <sys/wait.h>


void sumarnumerosarreglo(int m, int arreglo[]){
int arregloresultado[m*m];
for(int i = 0;i<m;i++){
 for(int j=i+1; j<m-1;j++) {
   arregloresultado[i] = arreglo[i] + arreglo[j];
   }
 }
}

void ejecutar_proceso(){

    for (int k = 0; k < n; ++k) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(1);
        }

    }
  for (int i = 0; i < n; ++i) {
        wait(NULL);
    }
   cout<<"el proceso tiene id numero:"<<getpid()<<endl;
   cout <<"el proceso tiene padre numero: "<<getppid()<<endl;
   _exit(0);
}


void ConstruirHilos(void args*) {
  int operacion1 = *(int *)arg;
    int operacion2 = *((int *)arg + 1);
    free((int *)arg);

}
void ejecutar_hilos() {
int numhilos=10;
pthread_t *hilos=(pthreat*) malloc(numhilos * sizeof(pthreat_t))

 if(hilos ==NULL) {
  cout<< "Asignacion de hilos nula"<<endl;
 }
 for(int i=0;i<numhilos;i++){
 if(pthread_create(&hilos, NULL,leerHilos(),(void*)args !=0){
    cout<<"error al crear el hilo"<<i<<endl;
    free(hilos);
 }

 for (int i = 0; i < num_hilos; i++) {
        if (pthread_join(hilos[i], NULL) != 0) {
            cout << "Error en el join del hilo " << i << endl;
       }
   }

    free(hilos);
}
}
int main(){

cout<< "Bienvenido a sumar un arreglo con procesos e hilos" << endl;
int arreglo[100],m ;
cout<< "ingresa cantidad de datos"<< endl;
cin>>m;

   for(int i=0;i<m;i++){
   cin>>arreglo;
  }



}
