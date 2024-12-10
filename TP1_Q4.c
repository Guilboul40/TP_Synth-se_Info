#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define PROMPT "enseash %% "

//On utilise toujours cette mini fonction qui reproduit l'effet d'un printf et qui rend le code moins dense
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
        waitpid(pid, &status, 0); //Attente que le processus fils soit terminé
        char prompt[256];

        // Affichage du code de retour ou du signal
        if (WIFEXITED(status)) {
            int return_code = WEXITSTATUS(status);
            snprintf(prompt, sizeof(prompt), "enseash [exit:%d] %% ", return_code); //Ici nous sommes obligés d'utiliser le snprintf pour pouvoir intégrer des valeurs dans le message
        } else if (WIFSIGNALED(status)) {
            int signal_number = WTERMSIG(status);
            snprintf(prompt, sizeof(prompt), "enseash [sign:%d] %% ", signal_number); //Idem
        }
        // Affichage du prompt
        write_message(PROMPT);
    } else {
        perror("fork échoué");
    }
}

int main() {
    char command[256];

    while (1) {
        write_message(PROMPT);
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; //Repérer ENTRER pour savoir quand exécuter la commande

        if (strcmp(command, "exit") == 0) {
            break; // Sortir du minishell
        }
        execute_command(command);
    }

    return 0;
}
