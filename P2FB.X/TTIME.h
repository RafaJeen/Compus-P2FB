#ifndef _TTIME_H_
#define _TTIME_H_

#include "TITTIMER.h"
#include "TGestorLCD.h"

#define ONESEC 1204

void modifyTime(char *modTime);

void initTime(void);

char timeFinished();

void showActualTime();

void stopShowTime();

void startGameCount();

void motorTime();

void getTime(char *modTime);


#endif