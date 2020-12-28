#include "explorer.h"

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
                else
                    wait(&etat); // instruction 41
            }
        }
        exit(0);
    }
    else
        wait(&etat); // instruction 46
}