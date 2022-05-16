#include "TUser.h"


static char currentLetters = 0;
static User user;


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


void startUserSearch(void){

}


char searchFinished(void){
    return 0;
}

void startPasswordCheck(void){

}

char passwdCheck(void){
    return 0;
}

void registerUser(void){
    
}


