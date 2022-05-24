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
static char t=0;
static char t2=0;
static char time[6];
static char currentLetters=0;
static char currentShifted=0;
static char estado=0;
static char estadoReceive=0;
static char dataObtained;
static char bitsReceived=0;
static char newData=0;

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
    
    t = TiGetTimer(); //TMR para enviamiento de la SIO personalizada
    t2 = TiGetTimer(); //TMR para el recibimiento de la SIO personalizda
}

void motorOwnSIO(){
    if (estado == 1){
        if(TiGetTics(t) >= 1){ //Enviamos StartBit
            LATCbits.LATC1=0;
            TiResetTics(t);
			estado++;    
        }
    } else if (estado == 2){
        if(TiGetTics(t) >= 1){
            //LATCbits.LATC1 = (time[currentLetters] >> (currentBits-1)) & 1;
            LATCbits.LATC1=time[currentLetters] & 1;
            TiResetTics(t);
            time[currentLetters] = time[currentLetters] >> 1;
            currentShifted++;
            if(currentShifted==8){
                estado++;
            }

        }
    } else if(estado==3) {
        if(TiGetTics(t) >= 1){
            LATCbits.LATC1=1; //Enviamos StopBit
			currentShifted=0;
			currentLetters++;
			if(currentLetters < 6){
                TiResetTics(t);
                estado=1;
			} else {
				currentLetters=0;
				estado=0;
            }
        }
    }
}


void motorOwnReceiveSIO(){
    if(estadoReceive == 1){
        //if(bitsReceived < 8){
        if(bitsReceived > 0){
            dataObtained=0;
            dataObtained = dataObtained | PORTCbits.RC0;
            dataObtained = dataObtained << 1;
            bitsReceived++;
            estadoReceive++;
        }else{
            if(PORTCbits.RC0 == 0){
                bitsReceived++;
                estadoReceive++;
            }
        }
        /*}else{
            estadoReceive=3;
        }*/
        TiResetTics(t2);
    }else if(estadoReceive == 2){
        if(TiGetTics(t2) >= 1){
            if(bitsReceived < 9) { // < 10
                estadoReceive--;
            } else {
                estadoReceive++;
            }
            TiResetTics(t2);
        }
    }else if(estadoReceive == 3) {
        if(TiGetTics(t2) >= 1) {
            if(PORTCbits.RC0 == 1){
                newData=1;
                estadoReceive=1;
                bitsReceived=0;
            }
            //enviar dataObtained
            /*LcGotoXY(12,1);
            LcPutChar(dataObtained);*/   
        }
    }
}

void enableReceiveSIO() {
    estadoReceive++;
}

void disableReceiveSIO() {
    estadoReceive=0;
}

char newOwnContent() {
    return newData;
}

char getOwnContent() {
    newData=0;
    return dataObtained;
}


void motorBluetooth() {
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

void sendDecTime(char *decTime) {
    time[0] = '\r';
	time[1]= decTime[0]+'0';
	time[2]= decTime[1]+'0';
	time[3]=':';
	time[4]= decTime[2]+'0';
	time[5]= decTime[3]+'0';
    currentLetters = 0;
    currentShifted = 0;
	estado = 1;
    TiResetTics(t);
}

char sendAvailable() {
	return estado == 0;
}

/*

00110101
&
00110001
=
00110001

*/



