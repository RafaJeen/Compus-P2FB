#ifndef _TADC_H_
#define _TADC_H_



void initADC(void);
//Post: 

void startConversion(void);
//Pre: 
//Post: 

unsigned char AdGetMostra(void);
//Post: returns the last analog sample which was converted (10 bits).

char AdSampleAvailable(void);
//Post: returns 1 if the conversion has finished or 0 otherwise.

void AdSetChannel(char channel);
//Pre: channel is between 0 and MAX_CHANNELS.
//Post: sets and starts the conversion for the specified channel.



#endif