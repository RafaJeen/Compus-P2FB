typedef struct {
    char nom[8];
    char password[8];
} User;

static char currentLetters = 0;

//Flag --> 0 estamos en user, si es 1 estamos  escribiendo passwd 
void setCharUser(char c, char flag);
//Pre:
//Post:


char currentLetters(void);
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