#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/**
 * main - Entry point for the simple shell
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *command = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;

	while (1)
	{
		printf("simple_shell> ");
		read = getline(&command, &len, stdin);

		if (read == -1)
		{
			if (feof(stdin))
			{
				free(command);
				exit(0);
			}
			else
			{
				perror("getline");
				continue;
			}
		}

		command[strcspn(command, "\n")] = '\0';

		if (strlen(command) == 0)
		{
			continue;
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
		}
		else if (pid == 0)
		{
			char *argv[] = {command, NULL};

			if (execvp(command, argv) == -1)
			{
				perror(command);
			}
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
		}
	}

	free(command);
	return (0);
}
