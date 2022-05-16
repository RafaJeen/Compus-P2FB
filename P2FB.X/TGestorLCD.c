#include "TGestorLCD.h"
#include "LcTLCD.h"

//Declarar variable gigante con todos los menus

static char *options[] = {"1.LOGIN\0", "2.REGISTER\0", "USER:\0", "PSWD:\0", "3"};
static char estado=0;
static char indice=0;
static char currentPrinted=0;
static char row = 0;

//Recibira la orden de que tiene que printar

//Printara por el LCD


void printaMenu(char c) {
    //Hardcodeamos que recibes un 1
    LcClear();
    estado++;
    row = 0;
    indice=c;
}

void printaUserPswd(void) {
    //IMPLEMENT
}

void setLCDPointer(char columna, char fila) {

}




void motorGestorLCD(void){
    if (estado == 1){
        LcPutChar(options[indice + row][currentPrinted]);
        currentPrinted++;
        if (options[indice + row][currentPrinted] == '\0' && currentPrinted <= 16){
            estado++;
        }
    } else if (estado == 2){
        row++;
        LcGotoXY( 0, row);
        currentPrinted = 0;
        estado--;
        if (row == 2){
            estado--;
        }
        
    }

}
