#include "TGestor.h"


static char letter = 0;
static char option = 0;
static char flag = 0;
static char estado = 0;
static char content = 0;



void motorGestor(){
    if (estado== 0){
        printaMenu1();
        estado++;
    } else if(estado == 1) {
        if (newContent() == 1){
            option = getCharacter();    //Optimizable suprimiendo estado 2
            estado++;
        }
    } else if(estado == 2) {
        if (option == 2 || option == 1){
            printaUserPswd();
            flag = 0;
            setLCDPointer(6, flag);
            setModeSMS();
            resetCurrentLetters();
            estado++;
        } else {
            estado--;
        }
    } else if(estado == 3) {
        content = newContent();
        if(content==1){
            letter = getCharacter();
            estado++;
        } else if(content == 2 || content == 3){
            letter = getCharacter();
            setCharUser(letter, flag);
            estado=5; //igual dos estado++ mas optimo
        }
    } else if(estado == 4) {
        if (letter != '#'){
            printChar(letter);
            estado--;
        } else{
            estado = 6;    //posible 2 ++;
        }
                
    } else if(estado == 5) {
        if (currentLetters()== 8){
            estado++;
        }else{
            setLCDPointer(6+currentLetters(), flag);
            estado = 3;
        }    
    } else if(estado == 6) {
        if(flag == 0){
            flag++;
            setLCDPointer(6, flag);
            resetCurrentLetters();
            estado=3;
        } else {
            startUserSerch();
            disableModeSMS();
            estado++;
        }
    } else if(estado == 7) {
        if((searchFinished()==1 && option == 2) || (searchFinished()==2 && option == 1)){
            estado=0;
        } else if(searchFinished()==2 && option == 2){
            registerUser();
            printaUserPasswd();
            flag=0;
            setLCDPointer(6,flag);
            setModeSMS();
            resetCurrentLetters();
            estado=3;
        }
    } else if(estado == 8) {
        if (passwdCheck() == 2){
            estado = 0;
        }
        if (passwdCheck() == 1){
            printaMenu2(0);
            options = 0;
            letter = 0;
            flag = 0;
            estado++;
        }
        
    } /*else if(estado == 9) {
        
    } else if(estado == 10) {

    }*/
}