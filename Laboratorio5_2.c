/*
 ============================================================================
 Name        : Laboratorio5_2.c
 Author      : Carlos Gil
 ID Number   : 19443
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Parte Laboratorio 5, control de bocina con comandos del teclado
 Assignment  : Laboratorio 5
 Course      : Electronica Digital 3
 Date        : Guatemala, 18 de agosto del 2021
 ============================================================================
 */
//***************************Librerias***************************************
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <unistd.h>
#include <pthread.h>
//**************************Variables globales*******************************
char state = 0;//variable donde se guarda lo ingresado por el usuario
char var = 0;//variable para hacer el switch y generara el PWM
//*******************prototipos de funciones*********************************
void Hilo (void *in); //funcion del Hilo con el scanf
void PWM (int pin, float del_alto, float del_bajo);//funcion para pwm
void PWM_off (int pin);//funcion para apagar el PWM
//************************************Hilos**********************************
void Hilo(void *in){
	while(state != 's'){ //cuando el usuario ingrese "s" el programa termina
		printf("\nIngrese lo que desea realizar: ");
		fflush(stdout);
		scanf(" %c",&state); //lo que reciba el scanf lo guarda en state
	}
	pthread_exit(0);
}
//**********************************Main*************************************
int main(void) {
	pthread_t thread2;//identificador del hilo
	int check = 0; //variable local que guarda el estado del boton
	wiringPiSetupGpio(); //funcion de configuracion para usar el pinout normal
	pinMode(16,OUTPUT); //pin para el pwm como salida
	pinMode(26,INPUT); //pin para el boton como entrada
	pullUpDnControl(26,PUD_UP); //pin del boton configurado en pullup
	pthread_create(&thread2, NULL, (void*)&Hilo, NULL); //funcion para crear el hilo
	while(state !='s'){ //cuando el usuario ingrese "s" el programa termina
		if (digitalRead(26)==0){ //revisa si se presiono el boton
			check = 1;
		}
		if (check == 1){ //si el boton se presiono, verificar lo que tenga state
			switch(state){
				case 0: //hacer un sonido en la bocina
					PWM(16,0.11944575,0.11944575);
					break;
				case 112: //se ingreso "p", apagar el PWM
					PWM_off(16);
					break;
				case 114://se ingreso "r", reanudar el PWM
					state = 0;
					break;
			}
		}
	}
	return(0);
}
//**********************funciones*******************************************
void PWM (int pin, float del_alto, float del_bajo){ //funcion para hacer un PWM
	switch(var){
		case 0:
			digitalWrite(pin,HIGH);
			var++;
			delay(del_alto);
			break;
		case 1:
			digitalWrite(pin,LOW);
			var = 0;
			delay(del_bajo);
			break;
	}
}
void PWM_off (int pin){//funcion para apagar el pin del PWM
	digitalWrite(pin, LOW);
}
