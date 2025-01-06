# TP n°2 de Synthèse - TFTP

## Question 1:

On nous demande d'utiliser les arguments passés à la ligne de commande des programmes gettftp et
puttftp pour obtenir les informations de requêtes (serveur et fichier). On programme donc le code suivant:

`#include <stdio.h>`

`#include <stdlib.h>`

`#include <unistd.h>`

`#include <string.h>`

`#define fd 1 //Variable qui vaut 1 pour pouvoir utiliser les write plutôt que les printf`

`#define ERROR_MESSAGE "Erreur dans la commande !\n"`



`int main(int argc, char* argv[]){`

`    char *host = argv[1];`

`    char *file = argv[2];`

`    // Vérification de la commande (3 caractéristiques: nom du serveur(host), nom du fichier(file) et une autre dont ne se sert pas dans la question)`
    
`    if(argc != 3){`

`        write(fd, ERROR_MESSAGE, strlen(ERROR_MESSAGE));`

`        exit(EXIT_FAILURE);    //Si la commande ne contient pas ces 3 caratéristiques, aucune action n'est exécutable, on sort du programmme.`

`    }`

`    return 0;`

`}`

Avec cette première question, on n' obtient pas d'autre résultat qu'une sortie de programme avec un affichage d'erreur commande puisque, pour l'instant, on n'envoie rien au programme.

## Question 2

On code désormais un programme qui permet de récupérer l'adresse du serveur (ici, on essayera avec le serveur local ensea). 


`#include <stdlib.h>`

`#include <unistd.h>`

`#include <string.h>`

`#include <netdb.h>`

`#include <arpa/inet.h>`

``

`#define BUFSIZE 128`

`#define fd 1`

`#define ERROR_MESSAGE "Erreur dans la commande !\n"`

`#define ERROR_INPUT "Erreur dans la commande !\nUsage: <program> <host> <file>\n"`

`#define ERROR_ADRESS "Erreur lors de la résolution de l'adresse.\n"`

``

`//On construit une fonction "printf" à partir d'un write pour éviter de saturer le code et de se répéter`

`void prompt(char *message){`

`    write(fd, message, strlen(message));`
    
`}`

``

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

`        sprintf(adress,"Address: %s\n", adress_str); // On est "obligé" d'utiliser un sprintf pour afficher un message avec une valeur variable`

`        prompt(adress);`

`    }`

`freeaddrinfo(result);`

`}`

``

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

NB: Le code signale une erreur de type "Incomplet, non autorisé" pour la variable "hints" mais cela ne pose pas de problème pour l'exécution du code.

On entre la commande " ./TP2_Info_Q2 localhost ensea.png " dans le terminal et on obtient l'adresse du serveur comme prévu:

![Q2_TP2_Info](https://github.com/user-attachments/assets/d95e1717-278a-4c0d-ad63-df3219581128)

## Question 3:

On récupère le code de la question 2 et on ajoute une fonction "  " qui permet de se connecter au serveur. On modifie légèrement le main pour qu'il exécute cette nouvelle fonction. On obtient les modifications suivantes:

`void create_socket(){`

`    int client_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);`

`    if (client_socket == -1) {`

`        prompt(ERROR_SOCKET);`

`        exit(EXIT_FAILURE);`

`    }`

`    // Connexion au serveur`

`    status = connect(client_socket, result->ai_addr, result->ai_addrlen);`

`    if (status == -1) {`

`        prompt(ERROR_CONNECT);`

`        close(client_socket);`

`        exit(EXIT_FAILURE);`

`    } else {`

`        //Envoie du message de connexion réussie`

`        prompt(CONNECT_SUCCESS);`

`        send(client_socket,CONNECT_SUCCESS,strlen(CONNECT_SUCCESS),0);`

`    }`

`}`

``

`int main(int argc, char* argv[]){`

`    char *host = argv[1];`

`    char *file = argv[2]; //Inutile ici`

`    //Vérification de la commande`

`    if(argc != 3){`

`        write(fd, ERROR_INPUT, strlen(ERROR_INPUT));`

`        exit(EXIT_FAILURE);`

`    }`

`    return_adress(host);`

`    create_socket();`

`    freeaddrinfo(result);`

`    return 0;`

`}`
