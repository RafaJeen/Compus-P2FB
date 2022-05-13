#include <pic18f4321.inc>
#include "TSIO.h"


/*  BSF TXSTA, 5, 0
    BCF TXSTA, 4, 0
    BSF TXSTA, 2, 0

    BSF RCSTA, 7, 0
    BSF RCSTA, 4, 0 ; Enables receiver

    BSF BAUDCON, 3, 0 ; 16 bit baudrate

    ; Baudrate 9600 --> 1040
    MOVLW HIGH(.1040)
    MOVWF SPBRGH, 0
    MOVLW LOW(.1040)
    MOVWF SPBRG, 0 */



void initSIO(void) {
    TXSTAbits.TXEN = 1; //Si da problemas mirar esto
    TXSTAbits.SYNC = 1;
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

char getChar (void){
    return RCREG;
}

char SiIsAvailable(void) {
    return TXSTAbits.TRMT;
}

void SiSendChar(char c) {
    TXREG = c;
}
