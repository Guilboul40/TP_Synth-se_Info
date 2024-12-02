# TP_Synthese Info
## Compte rendu - TP1 - Seance 1
Question 1:
On importe les librairies et fichiers nécessaires:
`#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>`

On code un programme permettant d'afficher un simple message d'accueil:
`
#define WELCOME_MESSAGE "Bienvenue dans le Shell ENSEA !\nPour quitter, tapez 'exit'.\n"
#define PROMPT "enseash %\n"

void show_message(void){
    write(STDOUT_FILENO, WELCOME_MESSAGE, strlen(WELCOME_MESSAGE));
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
    return(0);
}

int main(void){
    show_message();
}
`

On observe bien le message dans le terminal:
![](TP1_Info_Q1.jpg)
