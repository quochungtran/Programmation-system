#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>

#define MAX 255
#define MAXPAR 20

static pid_t pid;
static pid_t main_process;
static pid_t process_fils;

char *format_chaine(char *source)
{
    char *res = malloc(sizeof(char) * strlen(source) - 1);
    for (int i = 0; i < strlen(source) - 2; i++)
    {
        res[i] = source[i];
    }
    res[strlen(source) - 1] = '\0';
    return res;
    // return token;
}

char *getValeur(char *chaine)
{
    char *token = strtok(chaine, "=");
    token = strtok(NULL, "=");
    token = format_chaine(token);
    return token;
}

void terminerApplication(int sig)
{
    printf("Fermer toutes les applications\n");
    sleep(1);
    killpg(process_fils, SIGKILL);
}

int main()
{
    int nbApp, i;
    pid_t pid_fils;
    char chaine[30];
    char *token;

    int status;

    //ouvrire file
    FILE *filePointeur = fopen("list_appli.txt", "r");

    printf("Gestionnaire d’applications personnalisé \n\n");

    if (filePointeur != NULL)
    {
        fgets(chaine, 30, filePointeur);

        // afficher le nombre d'application
        nbApp = atoi(getValeur(chaine));
        if (nbApp == 0)
        {
            printf("il n'y a pas de Application\n");
            fclose(filePointeur);
            return EXIT_SUCCESS;
        }
        // initiatiation
        char *nomApplication[nbApp];
        char *path[nbApp];
        int nbArg[nbApp];
        char *argumentsApp[nbApp][100]; //

        // dans ce cas nb_App = 3

        // nom de application
        for (int i = 0; i < nbApp; i++)
        {
            fgets(chaine, 30, filePointeur);
            nomApplication[i] = getValeur(chaine);

            //path de application
            fgets(chaine, 30, filePointeur);
            path[i] = getValeur(chaine);

            //nombre argument
            fgets(chaine, 30, filePointeur);
            nbArg[i] = atoi(getValeur(chaine));

            if (nbArg[i] != 0)
            {
                //lire 1eme ligne

                fgets(chaine, 30, filePointeur);
                // // lire argument
                for (int j = 0; j < nbArg[i]; j++)
                {
                    fgets(chaine, 30, filePointeur);
                    argumentsApp[i][j] = malloc(sizeof(char) * (strlen(chaine) - 1));
                    argumentsApp[i][j] = format_chaine(chaine);
                }
            }
            else
            {
                fgets(chaine, 30, filePointeur);
            }
            fgets(chaine, 30, filePointeur);
        }
        fclose(filePointeur);
        //----------------------------------------------------------------------------------
        // -------------------créer un ensemble de processus fils chacun est responsable----
        //-------------------- à l’exécution d’une application------------------------------
        //----------------------------------------------------------------------------------

        printf("-----------------------------------------------------\n");
        printf("---------Les Applications commencent à executer---------\n");
        printf("-----------------------------------------------------\n");
        main_process = getpid();
        // printf("main_process = %d\n\n", main_process);
        for (int i = 0; i < nbApp; i++)
        {
            pid = fork();
            // printf("pid = %d\n\n",pid);
            if (pid < 0)
            {
                perror("ERROR fork()");
            }
            else if (pid == 0)
            {
                // pid_t pid_test_1;
                // printf("pid_test_1 = %d\n\n", getpid());
                if (nbArg[i] == 0)
                {
                    char *chaine = path[i];
                    // char *const arguments[] = {"sh", "-c", chaine, NULL};
                    // execv("/bin/sh", arguments);
                    system(chaine);
                }
                else
                {
                    process_fils = getpgid(pid);
                    char *chaine1 = path[i];

                    for (int j = 0; j < nbArg[i]; j++)
                    {
                        strcat(chaine1, " ");
                        strcat(chaine1, argumentsApp[i][j]);
                    }
                    pid_t pid_test_2 = getpid();
                    // printf("pid_test_2 = %d\n\n", pid_test_2);
                    char *const arguments[] = {"sh", "-c", chaine1, NULL};
                    execv("/bin/sh", arguments);
 
                    // system(chaine1);
                }
                // pid_t parent_of_pid = getppid();
                // printf("parent_of_pid = %d\n\n", parent_of_pid);
                //--------informer l’utilisateur en lui affichant le nom de----------------------------
                //--------l’application terminée ------------------------------------------------------
                // struct sigaction sa;
                // sa.sa_handler = transfer;
                // sigaction(SIGUSR1, &sa, NULL);
                // sa.sa_flags = 0;
                printf("-----Application %s est terminé-------- \n", nomApplication[i]);
                sleep(1);
                exit(0);
            }
        } // terminal a lire file
          // pour le pere attendre a la fin de processus fils
        struct sigaction sa;
        sa.sa_handler = terminerApplication;
        sigaction(SIGUSR1, &sa, NULL);
        sa.sa_flags = 0;
        int etat;
        while (wait(&etat) > 0)
            ;
        return 0;
    }
}