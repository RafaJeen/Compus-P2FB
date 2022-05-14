static char currentLetters = 0;


void setCharUser(char c) {
    user.nom[currentLetters] = c;
    currentLetters++;
}


char currentLetters() {
    return currentLetters;
}


void setCharPsswd(char c) {
    user.password[currentLetters] = c;
    currentLetters++;
}

void resetCurrentLetters(void) {
    currentLetters = 0;
}


