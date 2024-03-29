#include "TTeclat.h"


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
static char t = 0;

static char teclat[4][3][5] =
{
    {{'1', 0, 0, 0, 0}, {'2', 'A', 'B', 'C', 0}, {'3', 'D', 'E', 'F', 0}},
    {{'4', 'G', 'H', 'I', 0}, {'5', 'J', 'K', 'L', 0}, {'6', 'M', 'N', 'O', 0}},
    {{'7', 'P', 'Q', 'R', 'S'}, {'8', 'T', 'U', 'V', 0}, {'9', 'W', 'X', 'Y', 'Z'}},
    {{'*', 0, 0, 0, 0}, {'0', ' ', 0, 0, 0}, {'#', 0, 0, 0, 0}}
};


//Cambiar pines
void setFila(char f3, char f2, char f1, char f0){
  LATBbits.LATB0 = f0;
  LATBbits.LATB1 = f1;
  LATBbits.LATB2 = f2;
  LATBbits.LATB3 = f3;
}

void initTeclat(void){
  t = TiGetTimer();
  modeSMS = 0;
  estado = 0;
  estadoBarrido = 0;
}

void motorBarrido(void) {
  if(escombratEnabled){
    fila=estadoBarrido;
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
  }
}


//Cambiar pines
char hiHaColumna(void){
  if(PORTAbits.RA3 == 1){
    return 0;
  }else if(PORTAbits.RA4 == 1){
    return 1;
  }else if(PORTAbits.RA5 == 1){
    return 2;
  }else{
    return 3;
  }
  //return 3;
}


void incrementaCops(void){
    cops++;
    /*if(((fila == 0 && columna == 0) || fila == 3) && cops == 1){
        cops = 0;
        return;
    }

    if(((fila ==0 && (columna == 1 || columna == 2)) || fila == 1 || (fila == 2 && columna == 1)) && cops == 4){
        cops = 0;
        return;
    }

    if((fila == 2 && (columna == 0 || columna == 2)) && cops == 5){
        cops = 0;
        return;
    }*/

    if((filaDef == 0 && columnaDef == 0) || (filaDef == 3 && (columnaDef == 0 || columnaDef == 2)) && cops == 1){
        cops = 0;
        return;
    }

    if(((filaDef == 0 && (columnaDef == 1 || columnaDef == 2)) || filaDef == 1 || (filaDef == 2 && columnaDef == 1)) && cops == 4){
        cops = 0;
        return;
    }

    if((filaDef == 2 && (columnaDef == 0 || columnaDef == 2)) && cops == 5){
        cops = 0;
        return;
    }

    if((filaDef == 3 && columnaDef == 1) && cops == 2){
        cops = 0;
        return;
    } 
}


void setModeSMS(void) {
    modeSMS = 1;
    counting = 0;
}

void disableModeSMS(void) {
    modeSMS = 0;
    cops = 0;
    counting = 0;
}


char getCharacter(void) {
    if (availability == 3) {
        availability = 0;
    }else {
        availability--;
    }
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
  if(counting == 0) {
    filaDef = fila;
    columnaDef = columna;
    availability = 1;
  } else {
    if(columna == columnaDef && fila == filaDef){
      incrementaCops();
      availability = 1;
    } else {
      availability = 2;
    }
  }
}

void gotDef(void){
  filaDef = fila;
  columnaDef = columna;
  cops = 0;
  if (teclat[filaDef][columnaDef][cops] == '#'){
    counting = 0;
  }
}

char noPremut(){
  return escombratEnabled;
}

void motorTeclat(void) {
  if (estado == 0){
    if(hiHaColumna() != 3){
      escombratEnabled = 0;
      columna = hiHaColumna();
      TiResetTics(t);
      estado++;
    }
    if(counting == 1 && TiGetTics(t) >= ONESEC) { 
      counting = 0;
      availability = 3;
    }
  } else if (estado == 1){
    if (TiGetTics(t) >= TREBOTS){
        if (columna != hiHaColumna()){
          columna = 3;
          escombratEnabled = 1;
          estado--;
        }
        if (columna == hiHaColumna() && modeSMS == 1){
          checkChar();
          estado++;
        }
        if (columna == hiHaColumna() && modeSMS == 0){
          availability = 1;
          gotDef();
          estado++;
        }
    }
  } else if(estado == 2) {
    if (hiHaColumna() == 3){
      TiResetTics(t);
      estado++;
    }
  } else if(estado == 3){
    if (TiGetTics(t) >= TREBOTS){
      if (hiHaColumna() != 3){
        estado--;
      }
      if (hiHaColumna() == 3 && modeSMS == 0){
        escombratEnabled = 1;
        estado = 0;
      }
      if (hiHaColumna() == 3 && modeSMS == 1){
        if(teclat[filaDef][columnaDef][cops] != '#'){
          counting = 1;
          TiResetTics(t);
        }
        escombratEnabled = 1;
        estado = 0;
      }

    }
  }

}

























