# TP_Synthese Info
## Compte rendu - TP1 
Question 1:
On importe les librairies et fichiers nécessaires:

`#include <stdio.h>`

`#include <stdlib.h>`

`#include <unistd.h>`

`#include <string.h>`

On code un programme permettant d'afficher un simple message d'accueil:

`#define WELCOME_MESSAGE "Bienvenue dans le Shell ENSEA !\nPour quitter, tapez 'exit'.\n"`

`#define PROMPT "enseash %\n"`


`void show_message(void){`

`    write(STDOUT_FILENO, WELCOME_MESSAGE, strlen(WELCOME_MESSAGE));`

`    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));`

`    return(0);`

`}`

`int main(void){`

`    show_message();`

`}`


On observe bien le message dans le terminal:

![image](https://github.com/user-attachments/assets/43e15794-ce93-45a1-806a-038c24e3d73c)

Question 2:

Question 3:

Question 4: 
On rentre le code nécessaire pour la question:

Ensuite, on lance le programme et on entre dans le terminal la commande date (par exemple). On obtient:


On peut également tester que le programme compte les erreurs d'exécution:


Enfin on vérifie qu'on peut bien lancer un deuxième programme après "date", ici nous avons essayé avec geany:
