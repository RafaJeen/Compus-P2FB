#include "TGestor.h"


static char letter = 0;
static char option = 0;
static char flag = 0;
static char estado = 0;
static char content = 0;
/*static char modMin = 0;
static char modSec = 0;*/
static char modTime[4];
static char contenido = 0;
static char name[9];
static char currentSend = 0;
static char t = 0;
static char scoreInt = 0;
static char score[2];
static char error[2];



void initGestor() {
    t = TiGetTimer();
}

void updateOption(void){
    if (letter == 'W'){
        if (option != 0){
            option--;
            printaMenu(4 + option); 
        }
    }else if (letter == 'S'){
         if (option != 4){
            option++;
            printaMenu(4 + option); 
        }
    }
}

void goToMenu() {
    option=0;
    letter=0;
    flag=0;
    printaMenu(4);
    estado=9;
    startJoystick();
}

void updateModMinSec() {
    modTime[flag]=letter-'0';
    if(flag == 1) {
        LcGotoXY(3,1);
    }
    flag++;
}

void endGame(void) {
    stopShowTime();
    stopJoystick();
    stopMusic();
    disableReceiveSIO();
    //goToMenu();
    SiSendChar('F');
    estado++;
}

void motorGestor(){
    if (estado== 0){
        printaMenu(0);
        estado++;
    } else if(estado == 1) {
        if (newContent() == 1){
            option = getCharacter();    //Optimizable suprimiendo estado 2
            //LcPutChar(option);
            estado++;
        }
    } else if(estado == 2) {
        if(noPremut()){
            if (option == '2' || option == '1'){
                printaMenu(2);
                flag = 0;
                setModeSMS();
                resetCurrentLetters();
                estado++;
            } else {
                estado--;
            }
        }
    } else if(estado == 3) {
        content = newContent();
        if(content==1){
            letter = getCharacter();
            estado++;
        } else if(content == 2 || content == 3){
            letter = getCharacter();
            gotDef();
            if (flag == 0){
                name[numberLetters()] = letter;
            }
            setCharUser(letter, flag);
            estado=5; //igual dos estado++ mas optimo
        }
    } else if(estado == 4) {
        if (letter != '#'){ 
            LcGotoXY(6 + numberLetters(), flag);
            LcPutSimpleChar(letter);
            //printChar();
            estado--;
        } else{
            estado = 6;    //posible 2 ++;
            if (flag == 0){
                name[numberLetters()] = '\0';
            }
            setCharUser('\0', flag); // character '\0' marks end of string
        }     
    } else if(estado == 5) {
        if (numberLetters()== 8){
            if (flag == 0){
                name[numberLetters()] = '\0';
            }
            setCharUser('\0', flag);
            estado++;
        }else{
            LcGotoXY(6 + numberLetters(), flag);
            estado = 3;
        }    
    } else if(estado == 6) {
        if(flag == 0){
            flag++;
            LcGotoXY(6, flag);
            resetCurrentLetters();
            estado=3;
            //LcPutChar('R');
        } else {
            LcClear();
            LcGotoXY(0,0);
            startUserSearch();
            disableModeSMS();
            estado++;
        }
    } else if(estado == 7) {
        if((searchFinished()==1 && option == '2') || (searchFinished()==2 && option == '1')){
            estado=0;
        } else if(searchFinished()==2 && option == '2'){
            registerUser();
            printaMenu(2);
            flag=0;
            setModeSMS();
            resetCurrentLetters();
            estado=3;
            option='1';
        } else if (searchFinished() == 1 && option == '1') {
            startPasswordCheck();
            estado++;
        }
    } else if(estado == 8) {
        if (searchFinished() == 2){
            estado = 0; 
        }
        if (searchFinished() == 1){
            startJoystick();
            goToMenu();
        }     
    } else if(estado == 9) {
       if(actionAvailable()) {
            letter = getAction();
            updateOption();
       } else if(newContent() == 1) {
            letter = getCharacter();
            if(letter == '#'){
                letter = option +1;
                estado++;
            }
       }
    } else if(estado == 10) {
        if (letter == 1){
            option = 0;
            estado=14;
            enableReceiveSIO();
            return;
        }
        if (letter == 2){
            stopJoystick();
            printaMenu(10);
            modTime[0] = 0;
            modTime[1] = 0;
            modTime[2] = 0;
            modTime[3] = 0;
            estado++;
            return;
        }
        if (letter == 3){
            showTop5();
            estado = 13;
            return;
        }
        if (letter == 4){
            printaLogOut(name);
            estado = 22;
            TiResetTics(t);
            return;
        }
        if (letter == 5){
            stopJoystick();
            printaMenu(12);
            showActualTime();
            estado=13;
            return;
        }
    } else if (estado == 11){
        if (newContent()){
            letter = getCharacter();
            estado++;
        }
    } else if (estado == 12){
        if (letter != '#' && letter != '*')  {
            LcPutChar(letter);
            updateModMinSec();
            estado--;
        } else if (letter == '#' && flag == 4){ //flag=4 es que ya nos han introducido los 4 numeros

            modifyTime(modTime);
            goToMenu();
        } else if (letter == '*'){
            goToMenu();
        } else if (letter == '#' && flag != 4){
            estado--;
        }
    } else if (estado == 13) {
        //esperar a que nos den # para volver al menu
        if (newContent()){
            letter = getCharacter();
            if(letter == '#') {
                stopShowTime();
                goToMenu();
            }
        }
    } else if (estado == 14) {
        //LcPutChar('Q');
        if(SiIsAvailable()) {
            //TXSTAbits.TXEN = 1;
            SiSendChar(name[option]);
            //estado++;
            if(name[option] == '\0'){
                option=0;
                printaMenu(16);
                LcClear();
                estado++;
            } else {
                option++;
            }
        }
    } else if(estado == 15) {
        if(SiCharAvail() && SiGetChar() == 'K'){
            printaMenu(14);
            startGameCount();
            playMusic();
            LcClear();
            estado++;
        }
    } else if(estado == 16) {
        if (newContent()){
            letter = getCharacter();
            if(letter == '*') {
                //En este momento se hace el proceso de final de partida
                endGame();
            } else if(letter != '#') {
                SiSendChar(letter);
            }
        } else if(actionAvailable()) {
            SiSendChar(getAction());
        } else if(newOwnContent()) {
            SiSendChar(getOwnContent());
        }  else if(timeFinished()) {
            endGame();
        }
    } else if(estado == 17) {
        if(SiCharAvail()) {
            letter = SiGetChar();
            scoreInt = letter;
            //saveScore(scoreInt);
            TiResetTics(t);
            score[0] = '0';
            score[1] = '0';
            estado++;
        }
    } else if (estado == 18){
        if (letter >= 10){
            letter -= 10;
            score[0]++;
        }else{
            score[1] += letter;
            estado++;
        }
    } else if (estado == 19) {
        if(SiCharAvail()) {
            error[0]=SiGetChar();
            TiResetTics(t);
            estado++;
        }
        if(TiGetTics(t) >= THREESEC){
            getTime(modTime);
            printaGameFinal(score, modTime); 
            saveScore(scoreInt);
            estado++;
            estado++;
        }
    } else if (estado == 20){
        if(SiCharAvail()) {
            error[1]=SiGetChar();
            printaError(error);
            estado--;
        }
    } else if (estado == 21){
        if(newContent() == 1){
            letter = getCharacter();
            if (letter == '#'){
                goToMenu();
            }
        }
    } else if (estado == 22){
        if(TiGetTics(t) >= TWOSEC){
            estado = 0;
        }
    }
}









