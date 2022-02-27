#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define MAX 100
using namespace std;

struct Proceso{
    int PID;
    int Tllegada;
    int duracion;
    int prioridad;
    int Tsalida;
    int contador;
};

//Prototipos de Funciones
void creaProceso(int pid,int tlleg,int dur,int prior,Proceso &proceso);
void mostrarProceso(Proceso procesos[MAX],int n);
void simulacion(Proceso procesos[MAX],int n);
void salidaProceso(Proceso cola[MAX],int &nlim,int indice);
void creaCola(Proceso procesos[MAX],int &n);
void ordenarPorLLegada(Proceso procesos[MAX],int n);

int main(){
    int n=0;
    Proceso procesos[MAX];
    creaCola(procesos,n);
    ordenarPorLLegada(procesos,n);
    cout<<"\nINICIANDO SIMULACION: ";
    cout<<endl;
    mostrarProceso(procesos,n);
    system("pause");
    cout<<endl;
    simulacion(procesos,n);
    cout<<"\nSIMULACION FINALIZADA: \n";
    mostrarProceso(procesos,n);
    cout<<endl;
	return 0;
}

void creaProceso(int pid,int tlleg,int dur,int prior,Proceso &proceso){ //ingresa los datos a los atributos del tipo de dato Proceso
    proceso.PID=pid;
    proceso.Tllegada=tlleg;
    proceso.duracion=dur;
    proceso.prioridad=prior;
    proceso.Tsalida=0;
}
void mostrarProceso(Proceso procesos[MAX],int n){ //Muestra la cola de procesos
    printf("PID\tTllegada\tDuracion\tPrioridad\tTSalida");
    cout<<endl;
    for (int i=0;i<n;i++){
        printf("P%d\t%-10d\t%-10d\t%-10d\t%-10d",procesos[i].PID,procesos[i].Tllegada,procesos[i].duracion,procesos[i].prioridad,procesos[i].Tsalida);
        cout<<endl;
    }
    cout<<endl;
}

void creaCola(Proceso procesos[MAX],int &n){ // crea la cola de procesos
     int tlleg, dur, prior,naux;
     naux=0;
    cout<<"\n**SIMULADOR ROUND ROBIN**\n";
    cout<<"Ingrese numero de procesos:";
    cin>>naux;
    cout<<"\nDigite el tiempo de llegada, duracion y prioridad\n";
     for(int i=0;i<naux;i++)
    {
        cout<<"\nP["<<i+1<<"]\n";
        cout<<"\tTiempo de llegada:";
        cin>>tlleg;
        cout<<"\tTiempo de duracion:";
        cin>>dur;
        cout<<"\tPrioridad:";
        cin>>prior;
        creaProceso(i+1,tlleg,dur,prior,procesos[i]);
    }
    n=naux;
}
void ordenarPorLLegada(Proceso procesos[MAX],int n){ //ordena los procesos ingresos por orden de llegada
    int i, j;
        Proceso aux;
        for(i=0; i<n-1;){
            for(j=i+1; j<n;){
                if(procesos[i].Tllegada>procesos[j].Tllegada){
                   aux=procesos[j];
                   procesos[j]=procesos[i];
                   procesos[i]=aux;
                }
                j=j+1;
            }
             i=i+1;
        }
}
void salidaProceso(Proceso cola[MAX],int &nlim,int indice){ // saca al proceso de una cola al cumplir su duracion establecida
    for(int j=indice;j<nlim-1;j++){
        cola[j]=cola[j+1];
    }
    nlim=nlim-1;
}
void simulacion(Proceso procesos[MAX],int n){
    int tiempo=0; //Contador de la ejecucion de los procesos
    int nlim=0; //numero de procesos en la cola de ejecucion
    int cantSalidas=0; //contador de los procesos que salen de la cola de ejecucion
    int indiceProcesos=0; //indice para recorrer la cola de ejecucion
    int contadorPrioridad=0; //contador de la prioridad de los procesos
    Proceso cola[MAX];

    while(cantSalidas<n||tiempo<60){
        if(procesos[nlim].Tllegada==tiempo&&nlim<n){ // agrega procesos a la cola de ejecucion
            cola[nlim]=procesos[nlim];
            printf("\n\tTiempo %d: Proceso %d  entro a la cola...\n",tiempo,cola[nlim].PID);
            nlim++;
        }
        if(nlim>0){ // si la cola de ejecucion esta vacia

            if(cola[indiceProcesos].prioridad<=contadorPrioridad){ // si el proceso alcanzo su cantidad de prioridad, se continuará con el siguiente proceso iterando el indice

                contadorPrioridad=0; //reinicia el contador de prioridad
                indiceProcesos++;
            }
            if(indiceProcesos>=nlim){ //Si se termino de ejecutar todos los procesos en cola se comienza desde el inicio
                indiceProcesos=0; //reinicia el indice
            }
            if(cantSalidas<5){
                printf("\nTiempo %d: Proceso %d, Prioridad - %d, Contador - %d\n",tiempo,cola[indiceProcesos].PID,cola[indiceProcesos].prioridad,cola[indiceProcesos].duracion);
            }else{
                break;
            }
            cola[indiceProcesos].duracion--; // disminuye la duracion del proceso en ejecucion
            contadorPrioridad++;  //cuenta la prioridad del proceso en ejecucion
            if(cola[indiceProcesos].duracion<=0){ // si el proceso en ejucucion alcanzó su duracion , se sale de la cola
                for(int i=0;i<n;i++){
                    if(cola[indiceProcesos].PID==procesos[i].PID){ // Almacena el tiempo de salida correspondiente en el arreglo de procesos
                        procesos[i].Tsalida=tiempo+1;
                        printf("\n\tTiempo %d: Proceso %d  salio de la cola...\n",tiempo+1,procesos[i].PID);
                    }
                }
                salidaProceso(cola,nlim,indiceProcesos);
                cantSalidas++; // itera la cantidad de procesos salidos de la cola
                contadorPrioridad=0; //reinicia el contador de prioridad
            }


        }
        tiempo++; ///itera la linea de tiempo de ejecucion
    }

}
