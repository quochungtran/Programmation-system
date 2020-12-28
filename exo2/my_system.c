#include "my_system.h"

void my_system(char *chaine)
{
    char *const arguments[] = {"sh", "-c", chaine, NULL};
    int pid, etat;
    if ((pid = fork()) == -1)
        perror("erreur de fork()");
    else if (pid == 0)
    {
        execv("/bin/sh", arguments);
        printf("Retour non attendu. Doit tre une erreur execv\n");
    }
    else
    {
        wait(&etat);
    }
}