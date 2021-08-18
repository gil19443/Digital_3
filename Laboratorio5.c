/*
 ============================================================================
 Name        : Laboratorio5.c
 Author      : Carlos Gil
 ID Number   : 19443
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Parte Laboratorio 5, leds que alternan con delay aleatorio
 Assignment  : Laboratorio 5
 Course      : Electronica Digital 3
 Date        : Guatemala, 18 de agosto del 2021
 ============================================================================
 */

#include <stdio.h> //librerias utilizadas
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
int var = 0;//variable para hacer el cambio en el switch case
int del = 0;//variable donde se guardo el numero aleatorio para el delay
int main(void) {
	wiringPiSetupGpio();//funcion de configuracion para usar el pinout normal
	pinMode(18,OUTPUT);//seleccionar como salidas los 2 pines para los LEDs
	pinMode(21,OUTPUT);
	srand(time(NULL));//funcion para cambiar la semilla de la funcion rand cada segundo
	while(1){
		del = rand() % 1000 + 500;//numero aleatorio entre 500 y 1500
		delay(del); //delay entre 1 y 1.5 seg
		switch(var){ //ciclo que intercambia el estado de los LEDs luego de cada delay
			case 0:
				digitalWrite(18,HIGH);
				digitalWrite(21,LOW);
				var++;
				break;
			case 1:
				digitalWrite(21,HIGH);
				digitalWrite(18,LOW);
				var = 0;
				break;
		}
	}
	return(0);
}
