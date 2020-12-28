#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
void main(int argc, char *argv[])
{

	FILE *fp;
	char c;
	// printf("%s ", argv[0]);
	// printf("%s ", argv[0]);
	// printf("%s ", argv[1]);
	// printf("%s ", argv[2]);

	while (1)
	{
		if (argc != 3)
			exit(EXIT_FAILURE);
		fp = fopen(argv[1], "r");
		if (fp == NULL)
			exit(EXIT_FAILURE);
		c = fgetc(fp);
		fclose(fp);
		// add this command line for inform that this application is running

		if (c == '1')
		{
			printf("[power manager] Mise en veille en cours ...\n");
			/* ajoutez vos modification ici */
			killpg(getpgid(getppid()), SIGUSR1);
			fp = fopen(argv[1], "w");
			fputs("0", fp);
			fclose(fp);
			//on n'envoie que SIGUSR1 de power_manager a ApplicationManager
		}
		printf("[power manager] Power Manager est en cours executé ...\n");
		sleep(atoi(argv[2]));
	}
}
