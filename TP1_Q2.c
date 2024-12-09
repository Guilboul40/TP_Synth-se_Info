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
        

        // On crée un processus fils pour exécuter la commande
        pid_t pid = fork();
        if (pid > 0)
        {
            // Processus père
            int status;
            waitpid(pid, &status, 0); // On attend que le processus fils termine
        }

        if (pid == 0)
        {
            // Processus fils
            char *argv[] = {command, NULL}; 
            execvp(argv[0], argv);
            // Si la commande échoue on applique par défaut la commande exit() que l'on va ajouter dans la question suivante
            write_message(CODE_ERROR_EXEC);
            exit(1);
        }
    }

    return 0;
}
