//
// M�dul de gesti� de Timers
// Barsalona, Novembre de 1995, Juan Perez & Josep M. Ribes.
// Desembre de 2001. FEC. Ajustat per al Fujitsu 90583
// Mar� de 2010. FEC. Ajustat per al PIC24 (com passen els anys...)
// 

//
//--------------------------------CONSTANTS---AREA-----------

#include "TITTIMER.h"  
#include "LcTLCD.h"


#define         TI_FALS                         0
#define         TI_CERT     					1

// Tipus imb�cils
typedef unsigned char        BYTE;
typedef unsigned short       WORD;

//
//---------------------------End--CONSTANTS---AREA-----------
//

//
//--------------------------------VARIABLES---AREA-----------
//
struct Timer {
	unsigned int h_TicsInicials;
	unsigned char b_busy;
} s_Timers[TI_NUMTIMERS]; 

static unsigned int  h_Tics=0;
static int counter;

/*static char time[4];
static char flag=0;
static char currentLetters=0;
static char currentBits=0;*/

//
//---------------------------End--VARIABLES---AREA-----------
//
//
//--------------------------------PRIVADES----AREA-----------
//


void RSI_Timer0 (void) { 
	// Cada 1ms, amb un error del 1,74% (segons simulador) i triga 10us
//	IO_SetValue(GPIO_1, 1); // Per comprovar la temportitzaci�
    INTCONbits.TMR0IF = 0;    //Resetejo el flag de peticio d'interrupcio
	TMR0H = 0b11110111; 
	TMR0L = 0b11100101;
	h_Tics++;

	if (h_Tics>=TI_MAXTICS) {
		// Abans que dongui la volta, tots avall (cada 30s)
		for (counter=0;counter<TI_NUMTIMERS;counter++)
			if (s_Timers[counter].b_busy==TI_CERT)
				s_Timers[counter].h_TicsInicials -= h_Tics;
		h_Tics=0;
	}
//	IO_SetValue(GPIO_1, 0); // Per comprovar la temportitzaci�

	/*if(flag) {
		if(currentBits==0) { //Enviamos StartBit
			LATCbits.LATC1=0;
			currentBits++;
			return;
		}
		if(currentBits > 0 && currentBits < 9) {
			LATCbits.LATC1 = (time[currentLetters] >> (currentBits-1)) & 1;
			currentBits++;
		} else {
			LATCbits.LATC1=1; //Enviamos StopBit
			currentBits=0;
			currentLetters++;
			if(currentLetters == 4){
				currentLetters=0;
				flag=0;
			}
		return;
		}
	}*/
}
//
//---------------------------End--PRIVADES----AREA-----------
//

//
//--------------------------------PUBLIQUES---AREA-----------
//

void TiInit () {
	unsigned char counter;
	for (counter=0;counter<TI_NUMTIMERS;counter++) {
		s_Timers[counter].b_busy=TI_FALS;
	}
	h_Tics=0;
	// Anem a 40MHz
	//Tiempo de interrupcion 0,166ms
	T0CONbits.T08BIT=0; // 16 bits
	T0CONbits.T0CS = 0;	// Clock: fosc/4
	T0CONbits.PSA = 0; // Prescaler --> 16
	T0CONbits.T0PS = 1; // Preescaler a 1/4, pols de 4us  
	// La resta de valors de T1CON per defecte
	TMR0H = 0b11110111; 
	TMR0L = 0b11100101;	// (256-6) * 4us = 1ms 
	T0CONbits.TMR0ON = 1;		// Activo el timer
	// Activo la interrupci� del timer 1
	INTCONbits.TMR0IF = 0;
	INTCONbits.TMR0IE = 1;
}



char TiGetTimer() {
	unsigned char counter=0;
	while (s_Timers[counter].b_busy==TI_CERT) {
		counter++;
		if (counter == TI_NUMTIMERS) return -1;
	}
	s_Timers[counter].b_busy=TI_CERT;
	return (counter);
}

void TiResetTics (unsigned char Handle) {
	//__DI(); h_Tics integer, per tant, indivisible
	s_Timers[Handle].h_TicsInicials=h_Tics;
	//__EI();
}


unsigned int TiGetTics (unsigned char Handle) {
volatile unsigned int actual;
	actual=h_Tics; // indivisible si �s un int, clar.
	return (actual-(s_Timers[Handle].h_TicsInicials));
}

void TiCloseTimer (unsigned char Handle) {
	s_Timers[Handle].b_busy=TI_FALS;
}


void TiEnd () {
}

/*
void sendDecTime(char *decTime) {
	time[0]=decTime[0]+'0';
	time[1]=decTime[1]+'0';
	time[2]=decTime[2]+'0';
	time[3]=decTime[3]+'0';
	/*time[0]=decTime[0];
	time[1]=decTime[1];
	time[2]=decTime[2];
	time[3]=decTime[3];
	flag=1;
}

char sendAvailable() {
	return flag == 0;
}
*/
//
//---------------------------End--PUBLIQUES---AREA-----------
//



