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
#include <time.h>
int var = 0;
int del = 0;
int main(void) {
	wiringPiSetupGpio();
	pinMode(18,OUTPUT);
	pinMode(21,OUTPUT);
	srand(time(NULL));
	while(1){
		del = rand() % 1000 + 500;//numero entre 500 y 1500
		delay(del);
		switch(var){
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
