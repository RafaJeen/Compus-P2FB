#include "TUser.h"


static char currentLetters = 0;
static User user;
static char currentUser = 0;
static char address;
static char data = 0;
static char estadoAction = 0;
static char flag = 0;
static char estado;


void setCharUser(char c, char flag) {
    if(flag == 0) {
        user.nom[currentLetters] = c;
    } else {
        user.password[currentLetters] = c;
    }
    currentLetters++;
}


char numberLetters() {
    return currentLetters;
}



void resetCurrentLetters(void) {
    currentLetters = 0;
}

void setADDR(char user, char isPsswd){
    address = 1 + isPsswd*9 + 18*user;
}

void startUserSearch(void){
    /*LcClear();
    LcGotoXY(0,0);
    for(int i = 0; user.nom[i] != '#' ; i++){
        LcPutChar(user.nom[i]);
    }
    LcGotoXY(0,1);
    for(int i = 0; user.password[i] != '#' ; i++){
        LcPutChar(user.password[i]);
    }*/
    flag = 0;
    currentLetters = 0;
    currentUser = 0;
    setADDR(currentUser, 0);
    estado=1;
}


char searchFinished(void){
    return flag;
}

void startPasswordCheck(void){
    flag = 0;
    currentLetters = 0;
    setADDR(currentUser, 1);
    estado = 4;
}

char getResponse(void) {
    return flag;
}

void readROM(void) {
    estadoAction = 3;
}

void registerUser(void){
    address=0;
    readROM();
    currentLetters=0;
    estado=9;
}

void writeROM(char content) {
    data = content;
    estadoAction = 1;
}

void initUsers(void){
    address=0;
    currentLetters=0;
    readROM();
    estado=7;
}

void motorAccion(void) {
    if (estadoAction == 1) {
        EEADR = address + currentLetters;
        EEDATA = data;
        EECON1bits.EEPGD = 0;
        EECON1bits.CFGS = 0;
        EECON1bits.WREN = 1;
        INTCONbits.GIE = 0;
        EECON2 = 0x55;
        EECON2 = 0xAA;
        EECON1bits.WR = 1;
        estadoAction++;   
    } else if (estadoAction == 2) {
        if(EECON1bits.WR == 0) {
            INTCONbits.GIE = 1;
            EECON1bits.WREN = 0;
            estadoAction=0;
        }
    } else if (estadoAction == 3) {
        EEADR = address + currentLetters;
        EECON1bits.EEPGD = 0;
        EECON1bits.CFGS = 0;
        EECON1bits.RD = 1;  
        data = EEDATA;
        estadoAction = 0;
    }
}

void motorUser(void) {
    if (estado == 1) {
        //LcPutChar('A');
        readROM();
        estado++;
    } else if (estado == 2) {
        if(estadoAction==0) {
            //LcPutChar('B');
            estado++;
        }
    } else if (estado == 3) {
        if(data != user.nom[currentLetters] && currentUser == 7){
            flag=2;
            estado=0;
            return;
        }
        if(data == user.nom[currentLetters] && data == '\0'){
            flag=1;
            estado=0;
            return;
        }
        if(data == user.nom[currentLetters] &&  data != '\0'){
            currentLetters++;
            estado=1;
            return;
        }
        if(data != user.nom[currentLetters] && currentUser < 7){
            currentLetters = 0;
            currentUser++;
            setADDR(currentUser, 0); 
            estado = 1;
            return;
        }
    } else if (estado == 4) {
        readROM();
        estado++;
    } else if (estado == 5) {
        if(estadoAction==0){
            estado++;
        }
    } else if (estado == 6) {
        if(data == user.password[currentLetters] && data != '\0') {
            estado = 4;
            currentLetters++;
            return;
        }
        if(data == user.password[currentLetters] && data == '\0') {
            flag=1;
            estado=0;
            return;
        }
        if(data != user.password[currentLetters]) {
            flag=2;
            estado=0;
            return;
        }
    } else if (estado == 7) {
        if(estadoAction == 0){
            estado++;
        }
    } else if (estado == 8) {
        if(data != 0xFF) {
            estado = 0;
        } else {
            address = 0;
            writeROM(0);
            estado=0;
        }
    } else if (estado == 9) {
        if (estadoAction == 0){
            currentUser = data;
            setADDR(currentUser, 0);
            currentLetters = 0;
            writeROM(user.nom[currentLetters]);
            estado++;
        }      
    } else if (estado == 10) {
        if (estadoAction == 0 && user.nom[currentLetters] != '\0'){
            currentLetters++;
            writeROM(user.nom[currentLetters]);
        } else if (estadoAction == 0 && user.nom[currentLetters] == '\0') {
            currentLetters = 0;
            setADDR(currentUser, 1);
            writeROM(user.password[currentLetters]);
            estado++;
        }
        
    } else if (estado == 11) {
        if (estadoAction == 0 && user.password[currentLetters] != '\0'){
            currentLetters++;
            writeROM(user.password[currentLetters]);
        }else if (estadoAction == 0 && user.password[currentLetters] == '\0'){
            address = 0;
            currentLetters = 0;
            currentUser++;
            if (currentUser == 8){
                currentUser = 0;
            }
            writeROM(currentUser);
            estado = 0;
        }   
    } 
}



/*

RX-RT --> Bluetooth hacia Java (baudrate 9600)
Luego a mano haremos el de baudrate de 1200 

*/