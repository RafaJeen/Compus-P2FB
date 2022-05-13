#include "TGestorLCD.h"
#include "LcTLCD.h"

//Declarar variable gigante con todos los menus

const char *options[] = {'1.Login\0', '2.Register\0'};


//Recibira la orden de que tiene que printar

//Printara por el LCD


void printaPrimerMenu() {
    //Hardcodeamos que recibes un 1
    char i = 0;
    char opcio = 0;
    LcClear();
    for(i = 0; options[0][i] != '\0'; i++){
        LcPutChar(options[0][i]);
    }
    LcGotoXY(0, 1);
    for(i = 0; options[1][i] != '\0'; i++){
        LcPutChar(options[1][i]);
    }
    
}





