#ifndef _TGESTORLCD_H_
#define _TGESTORLCD_H_



//void printMenu(char );
// Pre: 
// Post:

void printaMenu(char c);
//Printa primer menu de todos


void printaUserPswd(void);
//Printa User: || Pswd:

void setLCDPointer(char columna, char fila);

void printChar(char c);

void motorGestorLCD(void);

#endif