#include "TTeclat.h"
#include <pic18f4321.inc>



static char estado = 0;
static char estadoBarrido = 0;
static char escombratEnabled = 1;
static char cops = 0;
static char modeSMS = 0;
static char fila = 4;
static char columna = 3;
static char filaDef = 4;
static char columnaDef = 3;
static char availability = 0;
static char counting = 0; //optimizavble con MODSMS = 2


static char teclat[4][3][5] =
{
    {{'1', 0, 0, 0, 0}, {'2', 'A', 'B', 'C', 0}, {'3', 'D', 'E', 'F', 0}},
    {{'4', 'G', 'H', 'I', 0}, {'5', 'J', 'K', 'L', 0}, {'6', 'M', 'N', 'O', 0}},
    {{'7', 'P', 'Q', 'R', 'S'}, {'8', 'T', 'U', 'V', 0}, {'9', 'W', 'X', 'Y', 'Z'}},
    {{'*', 0, 0, 0, 0}, {'0', 0, 0, 0, 0}, {'#', 0, 0, 0, 0}}
};


//Cambiar pines
void setFila(char f0, char f1, char f2, char f3){
  LATBbits.LATB0 = f0;
  LATBbits.LATB1 = f1;
  LATBbits.LATB2 = f2;
  LATBbits.LATB3 = f3;
}


void motorBarrido(void) {
  if(escombratEnabled){
    if(estadoBarrido == 0){
      setFila(0,0,0,1);
      estadoBarrido++;
    }else if(estadoBarrido == 1){
      setFila(0,0,1,0);
      estadoBarrido++;
    }else if(estadoBarrido == 2){
      setFila(0,1,0,0);
      estadoBarrido++;
    }else if(estadoBarrido == 3){
      setFila(1,0,0,0);
      estadoBarrido=0;
    }
    fila = estadoBarrido;
  }
}


//Cambiar pines
char hiHaColumna(){
  if(PORTAbits.PORTA3 == 1){
    return 0;
  }else if(PORTAbits.PORTA4 == 1){
    return 1;
  }else if(PORTAbits.PORTA5 == 1){
    return 2;
  }else{
    return 3;
  }
}


void incrementaCops(){
    cops++;
    if(((fila == 0 && columna == 0) || fila == 3) && cops == 1){
        cops = 0;
    }

    if(((fila ==0 && (columna == 1 || columna == 2)) || fila == 1 || (fila == 2 && columna = 1)) && cops == 4){
        cops = 0;
    }

    if((fila == 2 && (columna == 0 || columna == 2)) && cops == 5){
        cops = 0;
    }
  
}


void setModeSMS(void) {
    modeSMS = 1;
}

void disableModeSMS(void) {
    modeSMS = 0;
    cops = 0;
}

char charAvailable(void) {
    //Mirar si hay nuevo contenido
    //return columna != 3 && fila != 4;
}

char getChar(void) {
    if (availability == 3) availability = 0
    else availability--
    return teclat[filaDef][columnaDef][cops]; 
}

/*char getTecla(void) {
  return teclat[fila][columna][0];
}*/

char newContent(void){
  return availability;
}

//si counting == 0
// fila = filadef
// columna = columnadef
// availability = 1
//si counting == 1
//  si mismaTecla() == 1
//    cops ++
//    availability = 1;
//  si mismaTecla() == 0
//    availability = 2;
void checkChar (void){
 
}

void gotDef(void){
  filaDef = fila;
  columnaDef = columna;
}

void motorTeclat(void) {

}

























