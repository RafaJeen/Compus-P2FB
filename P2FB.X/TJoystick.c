#include "TJoystick.h"

#include "LcTLCD.h"

static char estado = 4;
static char action = 'Q';
static char channel = 0;
static unsigned char mostra = 128;
static char a = 0;


void initADC(void){
    ADCON0 = 0b00000011;
    ADCON1 = 0b00001101;
    ADCON2 = 0b00001100;

}

char checkMostra(void){
    if (mostra >= 240 && channel == 0){
        action = 'W';
        return 0;    
    }
    if (mostra >= 240 && channel == 1){
       action = 'D';
       return 0;   
    }
    if (mostra <= 15 && channel == 0){
        action = 'S';
        return 0;   
    }
    if (mostra <= 15 && channel == 1){
        action = 'A';
        return 0;   
    }
    if (mostra >= 115 && mostra <= 141 && action != 'Q'){
        if((action == 'W' || action == 'S') && channel == 0){
            return 1;
        }
        if((action == 'D' || action == 'A') && channel == 1){
            return 1;
        }
        return 0;     
    }
    return 0;
}

void motorJoystick(void){
    if (estado == 0) {
        ADCON0bits.GO = 1;
        estado++;
    } else if(estado == 1){
        if (ADCON0bits.GO == 0){
            mostra = ADRESH;
            estado++;
        }
    } else if(estado == 2) {
        if(checkMostra()) {
            estado++;
        } else{
            channel = !channel;
            ADCON0bits.CHS0 = channel;
            estado = 0;  
        }
    }
}

char actionAvailable(void){
    return estado == 3;
}


char getAction(void){
    estado = 0;
    a = action; // !!
    action = 'Q';
    return a;
}
 

void stopJoystick(void){
    estado = 4;
}


void startJoystick(void){
    estado = 0;
}
