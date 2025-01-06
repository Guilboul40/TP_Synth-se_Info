#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define WELCOME_MESSAGE "Bienvenue dans le Shell ENSEA !\nPour quitter, tapez 'exit'.\n"
#define PROMPT "enseash %\n"

void show_message(void){
    write(STDOUT_FILENO, WELCOME_MESSAGE, strlen(WELCOME_MESSAGE));
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}

int main(void){
    show_message();
}
