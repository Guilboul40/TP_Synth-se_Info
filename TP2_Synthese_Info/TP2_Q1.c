#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define fd 1
#define ERROR_MESSAGE "Erreur dans la commande !\n"

int main(int argc, char* argv[]){
    char *host = argv[1];
    char *file = argv[2];
    // Vérification de la commande (3 caractéristiques: nom du serveur(host), nom du fichier(filename) et ...())
    
    if(argc != 3){
        write(fd, ERROR_MESSAGE, strlen(ERROR_MESSAGE));
        exit(EXIT_FAILURE);    //Si la commande ne contient pas ces 3 caratéristiques, aucune action n'est exécutable, on sort du programmme.
    }
    return 0;
}
