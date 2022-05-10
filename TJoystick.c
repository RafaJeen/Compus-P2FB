#include <pic18f4321.inc>
#include "TJoystick.h"


static char estado = 0;
static char action = 'Q';
static char channel = 0;
static unsigned char mostra = 128;
static char a = 0;

void motorJoystick(void){
    if (estado == 0) {
        startConversion();
        estado++;
    } if else (estado == 1){
        if ( AdSampleAvailable() == 1){
            mostra = AdGetMostra();
            estado++;
        }
    } if else (estado == 2) {
        if(checkMostra()) {
            estado++;
        }  else{
            channel = !channel;
            AdSetChannel(channel);
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
 
char checkMostra(){
    if (mostra >= 240 && channel == 0){
        action = 'W';
        return 0;    
    }
    if (mostra >= 240 && channel == 1){
       action = 'D';
       return 0;   
    }
    if (mostra >= 240 && channel == 0){
        action = 'S';
        return 0;   
    }
    if (mostra >= 240 && channel == 1){
        action = 'A';
        return 0;   
    }
    if (mostra >= 115 && mostra <= 141 && action != 'Q'){
        if((action == 'W' || action == 'S') && channel == 0){
            return = 1;
        }
        if((action == 'D' || action == 'A') && channel == 1){
            return = 1;
        }
        return 0;
        
    }
    
    return 0;
}





