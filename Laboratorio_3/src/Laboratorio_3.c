/*
 ============================================================================
 Name        : Laboratorio_3.c
 Author      : Carlos Gil
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Multiples hilos, modificacion de L3_hilos_Ej1.c creado por Luis Rivera
 Date        : Guatemala, 4 de agosto del 2021
 Course      : Electronica Digital 3
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Código a ejecutar por el segundo hilo
void My_Thread(void *ptr)
{
	char *message;	// puntero, para la cadena de caracteres (string)
	message = (char *)ptr; // recupera la información pasada a este hilo

	while(1)
	{
		printf("%s", message);
		fflush(stdout);
		usleep(1100000);
	}

	// Lo siguiente no se ejecutará, pero es buena costumbre incluirlo
	pthread_exit(0);	// Para salir correctamente del hilo
}
void My_Thread4(void)
{
	while(1)
	{
		printf("Laboratorio_3 Carlos Gil ");
		fflush(stdout);
		usleep(5000000);
	}

	// Lo siguiente no se ejecutará, pero es buena costumbre incluirlo
	pthread_exit(0);	// Para salir correctamente del hilo
}
// Función principal (primer hilo de ejecución)
int main(void)
{
	pthread_t thread2;	// variable para identificar el 2do hilo que se creará
	pthread_t thread3;	// variable para identificar el 2do hilo que se creará
	pthread_t thread4;	// variable para identificar el 2do hilo que se creará
	// Los siguientes son dos strings
	char *message1 = "Hello ";
	char *message2 = "World\n";
	char *message3 = "Buenos_dias\n";

	// Función que crea un POSIX thread (pthread), que es un hilo del estándar POSIX
	// necesita la variable tipo pthread, configuraciones (NULL para usar las default),
	// la función a ejecutar por el hilo, y puntero para la información que se quiere
	// pasar al nuevo hilo (NULL si no se quiere pasar nada)
	pthread_create(&thread2, NULL, (void*)&My_Thread, (void*)message1);
	pthread_create(&thread3, NULL, (void*)&My_Thread, (void*)message3);
	pthread_create(&thread4, NULL, (void*)&My_Thread4, NULL);
	while(1)
	{
		printf("%s", message2);
		fflush(stdout);
		usleep(1000000);
	}

	return(0);
}
