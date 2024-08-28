#include "hsh.h"
/**
 * main - Main entry point of the simple shell.
 *
 * Return: 0 on success.
 */
int main(void)
{
	char *line = NULL;

	while (1)
	{
		display_prompt();
		line = read_input();

	if (line == NULL)
		{
		printf("\n");
		break;
		}

		execute_command(line);
	}

	cleanup(line);
	return (0);
}

/**
 * display_prompt - Displays the shell prompt.
 */
void display_prompt(void)
{
    printf("$ ");
    fflush(stdout);
}

/**
 * read_input - Reads input from the user.
 *
 * Return: Pointer to the input line or NULL on EOF.
 */
char *read_input(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread = getline(&line, &len, stdin);

	if (nread == -1)
	{
		if (feof(stdin))
		{
			free(line);
			return (NULL);
		}
		perror("getline");
		exit(EXIT_FAILURE);
	}

	if (line[nread - 1] == '\n')
	{
	line[nread - 1] = '\0';
	}

	return (line);
}

/**
 * execute_command - Executes the command entered by the user.
 * @command: The command to be executed.
 */
void execute_command(char *command)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execlp(command, command, (char *)NULL);

		perror("execlp");
		exit(EXIT_FAILURE);
	}
	else
	{

	int status;
	waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
		printf("Command not found: %s\n", command);
		}
	}
}

/**
 * cleanup - Frees allocated resources.
 * @line: The line to be freed.
 */
void cleanup(char *line)
{
	if (line != NULL)
	{
		free(line);
	}
}
