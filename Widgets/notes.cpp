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


/*
 * Pour la page de choix des scanners
 * Appel de scanimage -L
 * récuppération de l'output
 * affichage du nom dans un combobox
 * transfert du nom choisit via signal
 * mise en attribut dans prepare de scanner
*/

/*
 * Pour la page de choix des webcams
 * Appel de const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
 * affichage des npùs dans un combobox
 * transfert du QCameraInfo via signal
 * passage de la def de la webcam dans prepare
*/
