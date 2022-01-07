/*
 * Ces 10 lignes de code m'ont économisé environ 600 autres
 *
#include <stdlib.h>
#include <string.h>
int scanningStart(const char *fileName)
{
    char* command[250];
    strcpy(command, "scanimage --mode Color --format=jpeg > ");
    strcat(command, fileName);
    strcat(command, ".jpg");
    system(command);
}
*/


// QSqlDatabase::removeDatabase("puzzle");
