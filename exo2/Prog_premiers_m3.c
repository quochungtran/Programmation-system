#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

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

int premier(int nb)
{
    int r = 0;

    for (int i = 1; i <= nb; i++)
    {
        if (nb % i == 0)
        {
            r++;
        }
    }

    if (r > 2)
        return 0;
    else
        return 1;
}
void explorer(int debut, int fin)
{
    int etat, pid, pid2;
    pid = fork();
    if (pid == 0)
    {
        for (int i = debut; i <= fin; i++)
        {

            if (premier(i) == 1)
            {
                pid2 = fork();
                if (pid2 == 0)
                {
                    char chaine[200];
                    sprintf(chaine, "echo  '%d est un nombre premier écrit par le processus %d qui a créé le processus system, le PID de son pere est: %d \n --le PID de processus qui a écrit le message sur le terminal: '$$>>nbr_premiers.txt", i, getpid(), getppid());
                    my_system(chaine);
                    exit(0);
                }
            }
        }
        int etat;
        while (wait(NULL) > 0)
            ; // wait for all children
        exit(0);
    }
}

int main()
{
    int grp = 1;
    while (grp <= 11)
    {
        explorer(grp + 1, grp + 10);
        grp = grp + 10;
    }
    while (wait(NULL) > 0)
        ; // wait for all children
}
