#include "TGestorLCD.h"


//Declarar variable gigante con todos los menus

static char *options[] = {"1.LOGIN\0", "2.REGISTER\0", "USER:\0", "PSWD:\0", "1.PLAY A GAME\0", "2.MODIFY TIME\0", "3.SHOW GENERAL TOP 5 SCORES \0", "4.LOGOUT\0", "5.SHOW TIME\0", " \0", "MODIFY TIME:\0", "  :  \0", "CURRENT TIME:\0", "  :  \0", "TIME REMAINING:\0", "  :  \0", "STARTING GAME...\0", " \0", "ERRORS:\0", " \0", "TIME LEFT:\0", "SCORE:\0", "BYE BYE\0", " \0"};
static char estado=0;
static char indice=0;
static char currentPrinted=0;
static char row = 0;
static char flag=0;
static char error[2];
static char time[4];
static char n[9];
static char rowMarq = 0;
static signed char marqPointer = 0;
static signed char extractContent=0;
static char t;
//Recibira la orden de que tiene que printar

//Printara por el LCD

void initGestorLCD(){
    t = TiGetTimer();
}

void printaMenu(char c) {
    //Hardcodeamos que recibes un 1
    LcClear();
    flag = 0;
    currentPrinted=0;
    marqPointer = 0;
    extractContent=0;
    rowMarq=0;
    estado=1;
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
    estado=1;
    row = 0;
    indice=18;
    flag=2;
    error[0]=err[0];
    error[1]=err[1];
}

void printaGameFinal( char *score , char *decTime) {
    LcClear();
    estado=1;
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

void printaLogOut(char *name){
    LcClear();
    estado=1;
    row = 0;
    indice=22;
    flag=3;
    n[0] = name[0];
    n[1] = name[1];
    n[2] = name[2];
    n[3] = name[3];
    n[4] = name[4];
    n[5] = name[5];
    n[6] = name[6];
    n[7] = name[7];
    n[8] = name[8];
    n[9] = name[9];
}



void motorGestorLCD(void){
    if (estado == 1){
        LcPutChar(options[indice + row][currentPrinted]);
        currentPrinted++;
        if (options[indice + row][currentPrinted] == '\0'){
            estado++;
        }else{
            if (currentPrinted == 16){
                flag = 4;
                rowMarq = row;
                estado++;
            }
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
            } else if (flag == 3){
                LcGotoXY(8, 0);
                estado=3;
            } else if (flag == 4){
                TiResetTics(t);
                marqPointer = 1;
                estado = 4;
            }         
            flag = 0;
        }        
    } else if(estado==3) {
        if (n[currentPrinted] != '\0'){
            LcPutChar(n[currentPrinted++]);
        } else {
            estado=0; 
        }
    } else if (estado == 4){
        if (TiGetTics(t) >= ONESEC){
            LcGotoXY(0, rowMarq);
            estado++;
            TiResetTics(t);
            extractContent = marqPointer;
        }
    } else if (estado == 5){
        if (currentPrinted != 16 ){
            LcPutChar(options[indice + rowMarq][extractContent++]);
            if (options[indice+rowMarq][extractContent] == '\0') {
                extractContent = 0;
            }
            currentPrinted++;
        } else {
            currentPrinted=0;
            estado--;
            marqPointer++;
            if(options[indice+rowMarq][marqPointer] == '\0'){
                marqPointer = 0;
            }
            
        }    
    }
}
