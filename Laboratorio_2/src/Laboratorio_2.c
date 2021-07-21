/*
 ============================================================================
 Name        : Laboratorio_2.c
 Author      : Carlos Gil
 Version     :
 Copyright   : Your copyright notice
 Description : Laboratorio 2
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <Windows.h>

int main(void) {
	int i = 0;
	for (i = 0; i<20;i++){
		printf("El valor de la variable es: %i \n",i);
		fflush(stdout);
		sleep(1);
	}
	puts("El programa ha terminado");
}
