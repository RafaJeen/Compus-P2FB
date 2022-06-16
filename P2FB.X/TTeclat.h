#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include <xc.h>
#include "TITTIMER.h"
#include "LcTLCD.h"

#define TREBOTS 20
#define ONESEC 1204

void initTeclat(void);
//Pre: 
//Post: 

char newContent(void);
//Pre: 
//Post: 
//      Returns 0 Si no han apretado una nueva tecla
//      Returns 1 Si nos han apretado una tecla, si esta en Modo SMS empieza a contar un segundo. 
//      Returns 2 Si han apretado una tecla diferente a la anterior en modo SMS en menos de un segundo
//      Returns 3 Si ha pasado un segundo despues de una tecla en modo SMS

void gotDef(void);
//Pre: 
//Post: 

char getCharacter(void);

void setModeSMS(void);

void disableModeSMS(void);

void motorTeclat(void);

void motorBarrido(void);

char noPremut(void);











#endif