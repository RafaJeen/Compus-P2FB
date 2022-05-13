#include <pic18f4321.inc>
#include "TADC.h"



void initADC(void){
    ADCON0 = 0b00000011;
    ADCON1 = 0b00001101;
    ADCON2 = 0b00001100;
}

unsigned char AdGetMostra(void){
    return ADRESH;
}

void startConversion(void){
    ADCON0bits.ADON = 1;
}

char AdSampleAvailable(void){
    return !ADCON0bits.GO;
}

void AdSetChannel(char channel){
    ADCON0bits.CHS0 = channel;
}


