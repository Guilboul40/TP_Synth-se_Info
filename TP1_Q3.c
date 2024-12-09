#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024
#define PROMPT "enseash %\n"
#define CODE_ERROR_READING "\nErreur de lecture ou fin de fichier.\n"
#define CODE_ERROR_EXEC "Erreur d'exécution de la commande.\n"


//On crée une fonction write_message qui permet de réduire, d'alléger le code des longues lignes "write"
void write_message(const char *message)
{
    write(1, message, strlen(message));
}

ssize_t read_message(char *message)
{
    ssize_t bytesRead = read(0, message, MAX_CMD_LEN - 1);
    if (bytesRead > 0)
    {
        message[bytesRead] = '\0'; 
    }
    return bytesRead;
}

int main(){
    char command[MAX_CMD_LEN];
    while (1)
    {
        write_message(PROMPT);

        ssize_t bytesRead = read_message(command);
        
        if (bytesRead <= 0) //Si la lecture n'a pas fonctionné
        {
            write_message(CODE_ERROR_READING);
            break;
        }

        size_t len = strlen(command);
        if (len > 0 && command[len - 1] == '\n')
        {
            command[len - 1] = '\0';
        }
        
        // Check for "exit" command
        if (strcmp(command, "exit") == 0)
        {
            write_message("Au revoir !\n");
            break;
        }
...
