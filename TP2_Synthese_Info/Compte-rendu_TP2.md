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

`#include <stdlib.h>`

`#include <unistd.h>`

`#include <string.h>`

`#include <netdb.h>`

`#include <arpa/inet.h>`



`#define BUFSIZE 128`

`#define fd 1`

`#define ERROR_MESSAGE "Erreur dans la commande !\n"`

`#define ERROR_INPUT "Erreur dans la commande !\nUsage: <program> <host> <file>\n"`

`#define ERROR_ADRESS "Erreur lors de la résolution de l'adresse.\n"`



`void prompt(char *message){`

`    write(fd, message, strlen(message));`
    
`}`

`void return_adress(char *host){`

`    struct addrinfo hints, *result, *rp;`

`    int status;`

`    void *addr;`

`    char adress[BUFSIZE];`

`    char adress_str[BUFSIZE];`

`    memset(&hints, 0, sizeof(struct addrinfo));`

`    hints.ai_family = AF_UNSPEC;    // Autorise les IPV4 ou IPV6`

`    // On récupère les informations sur le serveur`

`    status = getaddrinfo(host, "tftp", &hints, &result);`

`    if (status != 0) {`

`        prompt(ERROR_ADRESS);`

`        exit(EXIT_FAILURE);`

`    }`

`    for (rp = result; rp != NULL; rp = rp->ai_next) {`

`       if (rp->ai_family == AF_INET) { // IPv4`

`            struct sockaddr_in *ipv4 = (struct sockaddr_in *)rp->ai_addr;`

`            addr = &(ipv4->sin_addr);`

`        }else { // IPv6`

`            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)rp->ai_addr;`

`            addr = &(ipv6->sin6_addr);`

`        }`

`        // On convertit l'adresse en chaîne de caractères`

`        inet_ntop(rp->ai_family, addr, adress_str, sizeof(adress_str));`

`        sprintf(adress,"Address: %s\n", adress_str);`

`        prompt(adress);`

`    }`



`freeaddrinfo(result);`

`}`

`int main(int argc, char* argv[]){`

`    // Vérification de la commande (3 caractéristiques)`

`    if(argc != 3){`

`        write(fd, ERROR_MESSAGE, strlen(ERROR_MESSAGE));`

`        prompt(ERROR_INPUT);`

`        exit(EXIT_FAILURE);`

`    }`

`    char *host = argv[1];`

`    return_adress(host);`

`    return 0;`

`}`

![Q2_TP2_Info](https://github.com/user-attachments/assets/b2312082-3b0c-400c-b4b1-643dddc6c4f0)
