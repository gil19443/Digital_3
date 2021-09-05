/*
 ============================================================================
 Name        : Laboratorio5.c
 Author      : Carlos Gil
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <unistd.h>
#include <pthread.h>
int state = 0;
void Hilo(void *in){

}
int main(void) {
	pthread_t thread2;
	int var = 0;
	wiringPiSetupGpio();
	pinMode(18,OUTPUT);
	pinMode(21,INPUT);
	pthread_create(&thread2, NULL, (void*)&Hilo, NULL);
	while(1){
		if (pinRead)
	}
	return(0);
}
void PWM (int pin, int del){
	delay(del);
	switch(var){
		case 0:
			digitalWrite(pin,HIGH);
			var++;
			break;
		case 1:
			digitalWrite(pin,LOW);
			var = 0;
			break;
	}
}
