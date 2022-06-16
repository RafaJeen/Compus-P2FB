#ifndef _TGESTORLCD_H_
#define _TGESTORLCD_H_

#include "LcTLCD.h"
#include "TITTIMER.h"

#define ONESEC 1204

//void printMenu(char );
// Pre: 
// Post:

void initGestorLCD();

void printaMenu(char c);
//Printa primer menu de todos

void motorGestorLCD(void);

void setActualLCD(char *aTime);

void printaError(char *err);

void printaGameFinal(char *score , char *decTime);

void printaLogOut(char *name);

#endif