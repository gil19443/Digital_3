/*
 ============================================================================
 Name        : Laboratorio6.c
 Author      : Carlos Gil
 ID Number   : 19443
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : union de archivos de texto y escalonamiento de hilos
 Assignment  : Laboratorio 6
 Course      : Electronica Digital 3
 Date        : Guatemala, 1 de septiembbre del 2021
 ============================================================================
 */
//***************************Librerias***************************************
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/timerfd.h>
#include <time.h>
#include <fcntl.h>
#include <sched.h>
#include <string.h>
//*******************************Macros**************************************
#define MAX_LETRAS  100 //maximo de letras de la cadena del buffer
#define MAX_CADENAS 60 //maximo numero de cadenas del string Array
//**************************Variables globales*******************************
char StringArray[MAX_CADENAS][MAX_LETRAS+1]; // arreglo de cadenas
int check = 0;//variable que indica cuando los hilos de lectura se terimnaron de ejecutar
int var = 0;//variable que lleva el conteo de las lineas que se guardaron en el StringArray
int periodo_H = 600000;//variable para modificar todos los periodos
//*******************prototipos de funciones*********************************
void Lectura_pares (void *in); //funcion para leer las lineas pares
void Lectura_impares (void *in); //funcion para leer las lineas impares
//************************************Hilos**********************************
void Lectura_pares(void *in){
	struct sched_param param;//se declara la prioridad del hilo
		param.sched_priority = 1;
	sched_setscheduler(0, SCHED_FIFO, &param);
	FILE *fp_par;	// variable para manejar el archivo de texto
	uint64_t num_periods = 0; //variable de 8 bytes para la funcion read
	int periodo_segundos = 0; //variable para guardardar la cantidad de segundos del periodo
	int tiempo_segundos = 0; //variable para guardar la cantidad de segundos del tiempo de desfase
	int tiempo_nanosegundos = 1000; ////variable para guardar la cantidad de nanosegundos del tiempo de desfase
	fp_par = fopen("Lab6_primero.txt", "r");  // abrir para lectura
	if(fp_par == NULL){ //se revisa que el archivo de texto tenga informacion
		perror("Error al abrir el archivo.");
		exit(0);
	}
	int timer_fd = timerfd_create(CLOCK_MONOTONIC, 0); //se crea el timer y se genera el file descriptor
	struct itimerspec itval; //configuracion del timer
		itval.it_interval.tv_sec = periodo_segundos;
		itval.it_interval.tv_nsec = periodo_H ;
		itval.it_value.tv_sec = tiempo_segundos;
		itval.it_value.tv_nsec = tiempo_nanosegundos;
	timerfd_settime(timer_fd, 0, &itval, NULL);//se inicia el timer
	read(timer_fd, &num_periods, sizeof(num_periods));//un delay para acople
	while ((fgets(in, MAX_LETRAS, fp_par))!=NULL){ //se lee el archivo de texto hasta que haya finalizado
		read(timer_fd, &num_periods, sizeof(num_periods));//delay de escaloniento
		if(num_periods > 1)//se verifica la variable num_periods
		{
			puts("MISSED WINDOW");
			exit(1);
		}
	}
	check++;//se incrementa el check indicando que el hilo ya finaliz[o
	fclose(fp_par);	// cierra el archivo original.
	pthread_exit(0); //se finaliza la ejecusion del hilo
}
void Lectura_impares(void *in){
	struct sched_param param;//se indica la prioridad del hilo
		param.sched_priority = 1;
	sched_setscheduler(0, SCHED_FIFO, &param);
	FILE *fp_impar;	// variable para manekar el archvo de texto
	uint64_t num_periods = 0; //variable para la funcion read
	int periodo_segundos = 0; //variable para guardardar la cantidad de segundos del periodo
	int tiempo_segundos = 0;//variable para guardardar la cantidad de segundos del tiempo de desgase
	fp_impar = fopen("Lab6_segundo.txt", "r");  // abrir para lectura
		if(fp_impar == NULL){ //se verifica que el archivo tenga informacion
			perror("Error al abrir el archivo.");
			exit(0);
		}
	int timer_fd = timerfd_create(CLOCK_MONOTONIC, 0); //se crea el timer
	struct itimerspec itval; //se configura el timer
		itval.it_interval.tv_sec = periodo_segundos;
		itval.it_interval.tv_nsec = periodo_H;
		itval.it_value.tv_sec = tiempo_segundos;
		itval.it_value.tv_nsec = (1000 + (periodo_H/2));

	timerfd_settime(timer_fd, 0, &itval, NULL);//se inicia el timer
	read(timer_fd, &num_periods, sizeof(num_periods)); //se da un delay de sincronizacion
	while ((fgets(in, MAX_LETRAS, fp_impar))!=NULL){ //se lee el archivo hasta que haya finalizado
		//printf(in); // y cada linea de guarda en la cadena
		read(timer_fd, &num_periods, sizeof(num_periods)); //delay de escalonamiento
		if(num_periods > 1) //verficicacion de la funcion read
		{
			puts("MISSED WINDOW");	// similar a printf, manda la cadena al stdandard output
			exit(1);
		}
	}
	check++; //variable que indica que el hilo ha terminado
	fclose(fp_impar);	// cierra el archivo original.
	pthread_exit(0); //se finaliza el hilo
}
void Union (void *in){
	struct sched_param param; //se indica la prioridad del hilo
		param.sched_priority = 1;
	sched_setscheduler(0, SCHED_FIFO, &param);
	uint64_t num_periods = 0; //variable para la funcion read
	int periodo_segundos = 0; //variable para guardardar la cantidad de segundos del periodo
	int tiempo_segundos = 0; //variable para guardardar la cantidad de segundos del tiempo de desfase
	char* buffer; //variable temporal para guardar el buffer
	int timer_fd = timerfd_create(CLOCK_MONOTONIC, 0); //se crea el timer
	struct itimerspec itval; //se configura el timer
		itval.it_interval.tv_sec = periodo_segundos;
		itval.it_interval.tv_nsec = periodo_H/2;
		itval.it_value.tv_sec = tiempo_segundos;
		itval.it_value.tv_nsec = (1000 + (periodo_H/4));
	timerfd_settime(timer_fd, 0, &itval, NULL);//se inicia el timer
	read(timer_fd, &num_periods, sizeof(num_periods)); //se da un delay de sincronizacion
	while(check != 2){ //se ejecuta hasta que ambos hilos de lectura hayan finalizados
		//espera
		buffer = in; //se guarda la cadena en el buffer temporal
		strcpy(StringArray[var], buffer);//se copia la cadena en el String Array
		fflush(stdout); //se vacia la consola
		read(timer_fd, &num_periods, sizeof(num_periods)); //delay de escalonamiento
		if(num_periods > 1) //revision de la funcion read
		{
			puts("MISSED WINDOW");	// similar a printf, manda la cadena al stdandard output
			exit(1);
		}

		var++; //variable que indica el numero de veces que se guardadron cadenas en el String Array
	}
	pthread_exit(0); //se sale el hilo cuando ambos hilos de lectura terminen
}
//**********************************Main*************************************
int main(void) {
	pthread_t thread2,thread3,thread4;//identificador de los hilos
	FILE *fp_final; //variable para manejar el archivo donde se juntara el archivo
	char* Cadena[MAX_LETRAS+1];	// buffer de los hilos de lectura
	int i = 0; //variable para el ciclo for de escritura
	pthread_create(&thread2, NULL, (void*)&Lectura_pares, (void*)Cadena); //funcion para crear el hilo
	pthread_create(&thread3, NULL, (void*)&Lectura_impares, (void*)Cadena); //funcion para crear el hilo
	pthread_create(&thread4, NULL, (void*)&Union , (void*)Cadena); //funcion para crear el hilo
	pthread_join(thread2,NULL);//espera a que el hilo 2 haya terminado
	pthread_join(thread3,NULL);//espera a que el hilo 3 haya terminado
	pthread_join(thread4,NULL); //espera a que el hilo 4 haya terminado
	fp_final = fopen("Lab6_reconstruido.txt", "w"); //se abre el archivo de texto para escrutura
	for(i = 0; i < (var-1); i++){ //se escribe en el archivo de texto cada elemento escrito en el StringArray
		fputs(StringArray[i], fp_final);	// escribe una línea en el archivo
		printf(StringArray[i]); //imprime en la terimnal la linea escrita previamente
	}

	fclose(fp_final);	// cierra el archivo
	printf("\nListo...\n"); //se indica que finalizo el proceso
	return(0); //finaliza el programa
}
//**********************funciones*******************************************
