#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h> //Pour Linux
#include <newlib/time.h>  //Pour Windows

#define PROMPT "enseash %% "
#define MAX_SIZE_CHAR 256

void write_message(const char *message)
{
    write(STDOUT_FILENO, message, strlen(message));
}

void execute_command(char *command) {
    pid_t pid = fork();
    if (pid == 0) {
        // Enfant
        char *args[] = {command, NULL};
        execvp(args[0], args);
        perror("execvp échoué");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent
        int status;
        waitpid(pid, &status, 0);
        char prompt[MAX_SIZE_CHAR];
        struct timespec time;  // le problème semble venir de la déclaration de time qui ne doit pas être la bonne mais nous n'avons pas réussi à le régler dans les temps

        // Affichage du code de retour ou du signal
        if (WIFEXITED(status)) {
            int return_code = WEXITSTATUS(status);
            snprintf(prompt, sizeof(prompt), "enseash [exit:%d|%d] %% ", return_code, clock_gettime(CLOCK_REALTIME, &time));
        } else if (WIFSIGNALED(status)) {
            int signal_number = WTERMSIG(status);
            snprintf(prompt, sizeof(prompt), "enseash [sign:%d|%d] %% ", signal_number, clock_gettime(CLOCK_REALTIME, &time));
        }
        // Affichage du prompt
        write_message(PROMPT);
    } else {
        perror("fork échoué");
    }
}

int main() {
    char command[MAX_SIZE_CHAR];

    while (1) {
        write_message(PROMPT);
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; //Permet de repérer ENTRER donc la demande d'exécution de la commande

        if (strcmp(command, "exit") == 0) {
            break; // Sortir du minishell
        }
        execute_command(command);
    }

    return 0;
}
