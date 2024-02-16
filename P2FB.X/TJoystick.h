#ifndef _TJOYSTICK_H_
#define _TJOYSTICK_H_

#include <xc.h>


void initADC(void);

char actionAvailable(void);
//Pre: 
//Post: 

char getAction(void);
//Pre: 
//Post: 

void stopJoystick(void);
//Pre: 
//Post: 

void startJoystick(void);
//Pre: 
//Post: 

void motorJoystick(void);

#endif