#include "TTIME.h"


static char estado = 0;
/*static char aMin = 0;
static char aSec = 0;*/
static char aTime[4];
/*static char storedMin = 30;
static char storedSec = 0;*/
static char storedTime[4];
/*static char decMin = 0;
static char decSec = 0;*/
static char decTime[4];
static char flag = 0; // 0 si solo contamos actualTime (tambien lo usamos para saber si ha acabado el tiempo de la partida)
                      // 1 si contamos tambien remaining
                      // 2 si tenemos que hacer show del actual time
static char t = 0;

//static char currentLetters=0;

void updateATime(void) {
    aTime[3]++;
    if(aTime[3] == 10){
        aTime[2]++;
        aTime[3] = 0;
        if(aTime[2] == 6 && aTime[3] == 0) {
            aTime[2] = 0;
            aTime[3] = 0;
            aTime[1]++;
            if (aTime[1]== 10){
                aTime[0] ++;
                aTime[1] = 0;
                //comprobar el caso de 1 hora
            }
        }
    }  
}


char timeFinished() {
    return flag == 0;
}


void updateDecTime(void) {
    if(decTime[3] == 0){
        decTime[3] = 9;
        if(decTime[2]==0){
            decTime[2]= 5;
            if (decTime[1] == 0){
                decTime[1] = 9;
                if (decTime[0] == 0){
                    decTime[1] = 0;
                    decTime[2] = 0;
                    decTime[3] = 0;
                    flag = 0;
                }else{
                    decTime[0]--;
                }        
            }else{
                decTime[1]--;
            }         
        } else {
            decTime[2]--;
        }
    } else{
        decTime[3]--;
    }
}


void modifyTime(char *modTime){
    storedTime[0] = modTime[0];
    storedTime[1] = modTime[1];
    storedTime[2] = modTime[2];
    storedTime[3] = modTime[3];
}

void initTime(void){
    t = TiGetTimer();
    flag = 0;
    storedTime[0]=3;
    storedTime[1]=0;
    storedTime[2]=0;
    storedTime[3]=0;
}

void startGameCount(){
    decTime[0] = storedTime[0];
    decTime[1] = storedTime[1];
    decTime[2] = storedTime[2];
    decTime[3] = storedTime[3];
    flag = 1;
}

void showActualTime() {
    flag=2;
}

void stopShowTime() {
    flag = 0;
}

void getTime(char *modTime) {
    modTime[0]=decTime[0];
    modTime[1]=decTime[1];
    modTime[2]=decTime[2];
    modTime[3]=decTime[3];
}


void motorTime(void) {
    if(estado == 0) {
        if(TiGetTics(t) >= ONESEC) {
            TiResetTics(t);
            updateATime();
            estado++;
        }
    } else if(estado==1) {
        if(flag==1){
            updateDecTime();
            //Aqui deberiamos enviar por la SIO personalizada
            /*if(sendAvailable()){
                if(currentLetters==2) {
                    sendDecTime(':');
                    currentLetters++;
                } else {
                    if(currentLetters<2) {
                        sendDecTime(decTime[currentLetters]);                        
                    } else {
                        sendDecTime(decTime[currentLetters-1]);
                    }
                    if(currentLetters==4){
                        currentLetters=0;
                    } else {
                        currentLetters++;
                    }
                }
            }*/
            if(sendAvailable()){
                /*decTime[0]='0';
                decTime[1]='0';
                decTime[2]='0';
                decTime[3]='0';*/
                sendDecTime(decTime);
            }
            setActualLCD(decTime);
        } else if(flag==2){
            setActualLCD(aTime);
            //sendActual();
        }
        estado--;
    }
}


/*

if(decTime[currNum] & (1 << numSent)){
    //envias 1
} else {
    //envias 0
}

*/
