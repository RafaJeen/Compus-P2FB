#include <xc.h>
#include "TITTIMER.h"
#include "LcTLCD.h"
#include "TSIO.h"
#include "TTeclat.h"
#include "TGestorLCD.h"
#include "TJoystick.h"
#include "TGestor.h"
#include "TUser.h"
#include "TTIME.h"


//Configs de asm. El fet de posar pragma ens permetrà accedir al compilador i posar instruccions de asm
#pragma config OSC = HSPLL
#pragma config PBADEN = DIG
#pragma config WDT = OFF
#pragma config MCLRE = OFF
#pragma config DEBUG = OFF
#pragma config PWRT = OFF
#pragma config BOR = OFF
#pragma config LVP = OFF


static char currentLetters=0;


void __interrupt() RSI_High(void){
	RSI_Timer0();

}

void __interrupt(low_priority)  RSI_Low(void) {

}


//PUERTO A PARA ADCON Y TECLADO
//PUERTO B PARA FILAS TECLADO
//PUERTO C PARA RX/TX Y RC5-->ENVIAR || RC4 --> RECIBIR (SIO PERSONALIZADA)
//PUERTO D PARA LCD

void initPorts(void) {
    TRISA = 0b11111111;
    TRISB = 0;
    TRISC = 0b11000001; //RC3 para altavoz
                        //RC0 RX personalizado
                        //RC1 TX personalizado
    //Inicializamos PWM y SIO personalizada
    LATCbits.LATC1 = 1;
    //
    //TRISD = 0;
}

void initInterrupts(void) {
 	RCONbits.IPEN = 0;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
}



void main() {
    initPorts();
    initInterrupts();
    TiInit();
    LcInit(2, 16);
    initSIO();
    initADC();
    initTeclat();
    LcCursorOff();
    initUsers();
    initTime();
    initGestor();

    while(1) {     
        //Call all motors
        motorBarrido();
        motorTeclat();
        motorGestor();
        motorJoystick();    
        motorGestorLCD(); 
        motorAccion();
        motorUser();
        motorTime();
        motorSIO();
    }

    return;
}