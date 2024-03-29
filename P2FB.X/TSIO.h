#ifndef _TSIO_H_
#define _TSIO_H_

#include <xc.h>
#include "TITTIMER.h"
#include "LcTLCD.h"

void motorBluetooth(void);

void initSIO(void);
//Post: returns the number of available characters that are in the reception queue.

char SiCharAvail(void);
//Post: returns the number of available characters that are in the reception queue.
//Retorna -1 if there are no available characters.

char SiGetChar(void);
//Pre: SiCharAvail() returns a number greater than zero.
//Post: returns and removes the first element from the reception queue.

char SiIsAvailable(void);
//Post: returns 1 if the SIO module is available for sending.

void SiSendChar(char c);
//Pre: SiIsAvailable().
//Post: starts sending the specified character.

void motorOwnSIO(void);

void motorOwnReceiveSIO(void);

void enableReceiveSIO();

void disableReceiveSIO();

char newOwnContent();

char getOwnContent();

#endif