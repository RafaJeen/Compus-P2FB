#include "TGestorLCD.h"


//Declarar variable gigante con todos los menus

static char *options[] = {"1.LOGIN\0", "2.REGISTER\0", "USER:\0", "PSWD:\0", "1.PLAY A GAME\0", "2.MODIFY TIME\0", "3.SHOW GENERAL\0", "4.LOGOUT\0", "5.SHOW TIME\0", " \0", "MODIFY TIME:\0", "  :  \0", "CURRENT TIME:\0", "  :  \0", "TIME REMAINING:\0", "  :  \0", "STARTING GAME...\0", " \0", "ERRORS:\0", " \0", "TIME LEFT:\0", "SCORE:\0"};
static char estado=0;
static char indice=0;
static char currentPrinted=0;
static char row = 0;
static char flag=0;
static char error[2];
static char time[4];
//Recibira la orden de que tiene que printar

//Printara por el LCD


void printaMenu(char c) {
    //Hardcodeamos que recibes un 1
    LcClear();
    estado++;
    row = 0;
    indice=c;
}

void setActualLCD(char *aTime) {
    LcGotoXY(0, 1);
    LcPutChar(aTime[0]+'0');
    LcPutChar(aTime[1]+'0');
    LcGotoXY(3,1);
    LcPutChar(aTime[2]+'0');
    LcPutChar(aTime[3]+'0');
}


void printaError(char *err) {
    LcClear();
    estado++;
    row = 0;
    indice=18;
    flag=2;
    error[0]=err[0];
    error[1]=err[1];
}

void printaGameFinal( char *score , char *decTime) {
    LcClear();
    estado++;
    row = 0;
    indice=20;
    flag=1;
    error[0]=score[0];
    error[1]=score[1];
    time[0] = decTime[0];
    time[1] = decTime[1];
    time[2] = decTime[2];
    time[3] = decTime[3];
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
            if(flag==2) {
                LcGotoXY(0,1);
                LcPutChar(error[0]);
                LcPutChar(error[1]);
            } else if (flag==1) {
                LcGotoXY(11,0);
                LcPutChar(time[0] +'0');
                LcPutChar(time[1] +'0');
                LcPutChar(':');
                LcPutChar(time[2] +'0');
                LcPutChar(time[3] +'0');
                LcGotoXY(7,1);
                LcPutChar(error[0]);
                LcPutChar(error[1]);
            }
            flag = 0;
        }        
    }
}
