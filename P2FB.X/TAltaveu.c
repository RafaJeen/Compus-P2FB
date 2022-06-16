#include "TAltaveu.h"


static char estado=0;
static char t;
static char t2;
static char halfT;
static char times[]={2, 3, 7, 8, 4};
static char nota=0; //La usamos para contar notas tocadas y tambien para controlar que haya pasado un segundo

void initAltaveu() {
    LATCbits.LATC3=0;
    estado=0;
    t2 = TiGetTimer();
    t = TiGetTimer();
}

void playMusic() {
    nota = 0;
    halfT = times[0];
    LATCbits.LATC3 = 1;
    estado=1; 
    TiResetTics(t);
    TiResetTics(t2);
}

void stopMusic() {
    LATCbits.LATC3=0;
    estado=0;
}

void motorAltaveu() {
    if(estado==1) {
        if(TiGetTics(t) >= halfT){
            LATCbits.LATC3 = 0;
            TiResetTics(t);
            estado++;
        } 
    } else if(estado==2) {
        if (TiGetTics(t) >= halfT){
            if(TiGetTics(t2) >= ONESEC ){
                if (nota < 4){
                    nota++; 
                    halfT = times[nota];
                    LATCbits.LATC3 = 1;
                    estado--;
                }else{
                    estado++;
                }
                TiResetTics(t2);
            } else {
                LATCbits.LATC3 = 1;
                estado--;
            }
            TiResetTics(t);
        }
    } else if(estado==3) {
        if (TiGetTics(t2) >= ONESEC){
            nota++;
            if(nota == 59){
                nota = 0;
                LATCbits.LATC3 = 1;
                TiResetTics(t);
                halfT = times[0];
                estado = 1;
            }
            TiResetTics(t2);
        }
    }
}




