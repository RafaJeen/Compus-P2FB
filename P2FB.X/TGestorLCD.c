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
static Top player[5];
static char user = 0; 
static char userNext = 0;
static char data = 0;
static char currentLetters = 0;
static char trash = 0;
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


void showTop5() {
    user=0;
    userNext=0;
    currentLetters=0;
    estado=6;
}

void stopShowTop5 (){
    estado = 0;
    
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
    } else if (estado == 6) {
        if(user < 5) {
            readROMscore(user);
            estado++;
        } else {
            user = 0;
            userNext = 0;
            estado = 12;
        }
    } else if (estado == 7) {
        if(dataROMavail()) {
            data = getROMdata();
            estado++;
        }
    } else if (estado == 8) {
        if(data == 0xFF) {
            player[user++].noMostrar = 1;
            estado = 6;
        } else {
            player[user].score[0] = '0';
            player[user].score[1] = '0';
            player[user].score[2] = '\0';
            estado++;
        }
    } else if (estado == 9) {
        if(data >= 10) {
            player[user].score[0]++;
            data-=10;
        } else {
            player[user].score[1]+=data;
            currentLetters=0;
            readROMname(user, currentLetters);
            estado++;
        }
    } else if (estado == 10) {
        if(dataROMavail()) {
            data = getROMdata();
            estado++;
        }
    } else if (estado == 11) {
        if(data != '\0') {
            player[user].name[currentLetters++] = data;
            readROMname(user, currentLetters);
            estado--;
        } else {
            player[user].name[currentLetters] = '\0';
            player[user].noMostrar = 0;
            user++; 
            estado = 6;
        }
    } else if (estado == 12) {
        if(player[user].noMostrar == 1) {
            user++;
            if(user == 5){
                user=0;
            }
        } else {
            userNext = user+1;
            estado++;
        }
    } else if (estado == 13) {
        if(player[userNext].noMostrar == 1) {
            userNext++;
            if(userNext == 5){
                userNext = 0;
            }
        } else {
            LcClear();
            currentPrinted = 0;
            currentLetters = 0;
            trash = 0;
            TiResetTics(t);
            estado++;
        }
    } else if (estado == 14) {
        if (trash == 0){
            estado++;
        } else{
            LcGotoXY(16-currentPrinted, 0);
            estado = 17;
        }
    } else if (estado == 15) {
        if (player[user].name[currentPrinted] == '\0'){
            trash = 1;
            LcGotoXY(16-currentPrinted, 0);
            estado = 17;
        } else {
            estado++;
        }
    } else if (estado == 16){
        if (player[user].name[currentPrinted + currentLetters] != '\0'){
            LcPutChar(player[user].name[currentPrinted + currentLetters]);
            currentLetters++;
        }else{
            currentLetters = 0;
            LcGotoXY(16 - currentPrinted, 0);
            estado++;
        }
    } else if (estado == 17){
        if (currentLetters != currentPrinted && player[userNext].name[currentLetters] != '\0'){
            LcPutChar(player[userNext].name[currentLetters]);
            currentLetters++;
        } else {
            currentLetters = 0;
            LcGotoXY(0,1);
            estado++;
        }
    } else if (estado == 18){
        if (currentPrinted > 1){
            LcGotoXY(16-currentPrinted, 1);
            estado = 20;
        } else {
            estado++;
        }

    } else if (estado == 19){
        if (player[user].score[currentPrinted + currentLetters] == '\0'){
            LcGotoXY(16 - currentPrinted, 1);
            currentLetters = 0;
            estado++;
        } else{
            LcPutChar(player[user].score[currentPrinted + currentLetters]);
            currentLetters++;
        }
    } else if (estado == 20){
        if (TiGetTics(t) < ONESEC){
            if (currentLetters != currentPrinted && player[userNext].score[currentLetters] != '\0'){
                LcPutChar(player[userNext].score[currentLetters]);
                currentLetters++;
            }
        }else {
            if (currentPrinted == 15){
                user = userNext;
                userNext++;
                estado = 13;
            } else{
                currentPrinted++;
                currentLetters = 0;
                TiResetTics(t);
                LcClear();
                estado = 14;
            }
            
        }

    }


}
