#ifndef _TGESTORLCD_H_
#define _TGESTORLCD_H_

#include "LcTLCD.h"

//void printMenu(char );
// Pre: 
// Post:

void printaMenu(char c);
//Printa primer menu de todos

void motorGestorLCD(void);

void setActualLCD(char *aTime);

void printaError(char *err);

void printaGameFinal(char *score , char *decTime);

#endif