#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define PROMPT "simple_shell> "

extern char **environ;

/**
 * handle_command - Executes a command using execve.
 * @command: The command to execute.
 */
void handle_command(char *command)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		execlp(command, command, (char *)NULL);

		perror("simple_shell");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("simple_shell");
	}
	else
	{
		do
		{
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

/**
 * main - Entry point for the simple shell program.
 *
 * Return: Always 0.
 */
int main(void)
{
	char buffer[BUFFER_SIZE];

	while (1)
	{
		printf(PROMPT);
		fflush(stdout);

		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			else
			{
				perror("simple_shell");
				continue;
			}
		}

		buffer[strcspn(buffer, "\n")] = '\0';

		if (strlen(buffer) > 0)
		{
			handle_command(buffer);
		}
	}

	return (0);
}
