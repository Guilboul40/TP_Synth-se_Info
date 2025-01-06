# TP n°2 de Synthèse - TFTP

## Question 1:

On nous demande d'utiliser les arguments passés à la ligne de commande des programmes gettftp et
puttftp pour obtenir les informations de requêtes (serveur et fichier). On programme donc le code suivant:

`#include <stdio.h>`

`#include <stdlib.h>`

`#include <unistd.h>`

`#include <string.h>`

`#define fd 1`

`#define ERROR_MESSAGE "Erreur dans la commande !\n"`



`int main(int argc, char* argv[]){`

`    char *host = argv[1];`

`    char *file = argv[2];`

`    // Vérification de la commande (3 caractéristiques: nom du serveur(host), nom du fichier(file) et une autre dont ne se sert pas encore dans la question)`
    
`    if(argc != 3){`

`        write(fd, ERROR_MESSAGE, strlen(ERROR_MESSAGE));`

`        exit(EXIT_FAILURE);    //Si la commande ne contient pas ces 3 caratéristiques, aucune action n'est exécutable, on sort du programmme.`

`    }`

`    return 0;`

`}`

Avec cette première question, on n' obtient pas d'autre résultat qu'une sortie de programme avec un affichage d'erreur commande puisque, pour l'instant, on n'envoie rien au programme.

## Question 2
