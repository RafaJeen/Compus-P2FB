#include "TSIO.h"





/*void initSIO(void) {
    //TXSTAbits.TXEN = 1; //Si da problemas mirar esto
    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH = 1;

    RCSTAbits.SPEN = 1;
    RCSTAbits.CREN = 1;

    BAUDCONbits.BRG16 = 1;

    //1040 to bin --> 0000 0100 0001 0000
    SPBRGH = 0b00000100;
    SPBRG = 0b00010000;
}

char SiCharAvail(void) {
    return PIR1bits.RCIF;
}

char SiGetChar (void){
    return RCREG;
}

char SiIsAvailable(void) {
    return TXSTAbits.TRMT;
}

void SiSendChar(char c) {
    TXREG = c;
}*/



static char BufferTX[5];
static char FiTx=0;
static char QuantsTX=0;


//------------------------ FUNCTIONS ----------------------

void initSIO(void) {
    //TXSTAbits.TXEN = 1; //Si da problemas mirar esto
    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH = 1;

    RCSTAbits.SPEN = 1;
    RCSTAbits.CREN = 1;

    BAUDCONbits.BRG16 = 1;

    //1040 to bin --> 0000 0100 0001 0000
    SPBRGH = 0b00000100;
    SPBRG = 0b00010000;

	QuantsTX = FiTx = 0;
}

void motorSIO() {
	static char estat = 0;
	if(estat == 0) {
        if(QuantsTX != FiTx) {
            TXREG = BufferTX[FiTx++];
            TXSTAbits.TXEN = 1;
            estat++;
        }else{
            QuantsTX = 0;
            FiTx = 0;
        }
	}else{
		if(TXSTAbits.TRMT == 1) {
			TXSTAbits.TXEN = 0;
			estat--;
		}
	}
}

char SiCharAvail(void) {
   return PIR1bits.RCIF == 1;
}

char SiGetChar(void) {
    return RCREG;
}

char SiIsAvailable(void) {
    return QuantsTX == 0;
}


void SiSendChar(char c) {
    BufferTX[QuantsTX++] = c;
}







