#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#define NB_FORK 4

int main()
{
    for (int i = 0; i < NB_FORK; i++)
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            return EXIT_FAILURE;
        }
        else if (pid == 0)
            printf("Mon PID est : %d et le pid de mon père est : %d \n", getpid(), getppid());
        // else
        //     printf("Mon PID est : %d et le pid de mon fils est : %d \n", getpid(), pid);

        sleep(1);
    }
    return EXIT_SUCCESS;
}
