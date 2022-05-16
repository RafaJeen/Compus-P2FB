typedef struct {
    char nom[9];
    char password[9];
} User;

//Flag --> 0 estamos en user, si es 1 estamos  escribiendo passwd 
void setCharUser(char c, char flag);
//Pre:
//Post:


char numberLetters(void);
//Pre:
//Post:


void resetCurrentLetters(void);
//Pre:
//Post:


void startUserSearch(void);
//Pre:
//Post:


char searchFinished(void);
//Pre:
//Post:
//      Returns 0 si aun no ha acabado de recorrer todos los usuarios de la ROM
//      Returns 1 si ya ha acabado de recorrer todos los usuarios y el usuario existe en la ROM
//      Returns 2 si ya ha acabado de recorrer todos los usuarios y el usuario no existe en la ROM


void startPasswordCheck(void);
//Pre:
//Post:

char passwdCheck(void);
//Pre:
//Post:
//      Returns 0 si aun no ha acabado de comprobar la contrasenya
//      Returns 1 si ya ha acabado de comprobar la contrasenya y es incorrecta
//      Returns 2 si ya ha acabado de comprobar la contrasenya y es correcta


void registerUser();
//Pre:
//Post:
//      Registers user (lo añade a la ROM)
