#include <xc.h>
#include <pic18f4321.h>
#include "TiTTimer.h"
#include "LcLCD.h"
#include "TSIO.h"


//Configs de asm. El fet de posar pragma ens permetrà accedir al compilador i posar instruccions de asm
#pragma config OSC = HSPLL
#pragma config PBADEN = DIG
#pragma config WDT = OFF
#pragma config MCLRE = OFF
#pragma config DEBUG = OFF
#pragma config PWRT = OFF
#pragma config BOR = OFF
#pragma config LVP = OFF



void __interrupt() RSI_High(void){
	RSI_Timer0();
}

void __interrupt(low_priority)  RSI_Low(void) {

}


void initPorts(void) {
    TRISA = 256;
    TRISB = 0;
    TRISC = 0b11000000;
    TRISD = 0;
}

void initInterrupts(void) {
 	RCONbits.IPEN = 0;
    INTCONbits.GIE = 1;
}



void main() {
    initPorts();
    initInterrupts();
    LcInit(2, 16);
    TiInit();
    initSIO();
    //initADC();


    while(1) {
        //Call all motors
        
    }

    return;
}