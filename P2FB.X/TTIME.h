#ifndef _TTIME_H_
#define _TTIME_H_

#include "TITTIMER.h"
#include "TGestorLCD.h"

#define ONESEC 1205

void modifyTime(char *modTime);

void initTime(void);

void showActualTime();

void stopShowTime();

void startGameCount();

void motorTime();

void getTime(char *modTime);


#endif