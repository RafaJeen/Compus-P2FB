#ifndef _TGESTORLCD_H_
#define _TGESTORLCD_H_

#include "LcTLCD.h"
#include "TITTIMER.h"
#include "TUser.h"

#define ONESEC 1204

typedef struct {
    char name[9];
    char score[3];
    char noMostrar;
} Top;

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

void showTop5();

#endif