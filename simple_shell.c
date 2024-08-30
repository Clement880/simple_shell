#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

/**
 * _strlen - Calculates the length of a string
 * @str: The string to calculate
 *
 * Return: The length of the string
 */
int _strlen(char *str)
{
	int len = 0;

	while (str[len] != '\0')
		len++;

	return (len);
}

/**
 * _puts - Writes a string to stdout
 * @str: The string to write
 */
void _puts(char *str)
{
	write(STDOUT_FILENO, str, _strlen(str));
}

/**
 * main - Entry point for the simple shell
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char command[BUFFER_SIZE];
	pid_t pid;
	int i;

	while (1)
	{
		_puts("simple_shell> ");
		i = 0;

		while (1)
		{
			if (read(STDIN_FILENO, &command[i], 1) == 0)
				_exit(0);
			if (command[i] == '\n')
				break;
			i++;
		}
		command[i] = '\0';

		if (command[0] == '\0')
			continue;

		pid = fork();
		if (pid == -1)
		{
			_puts("Fork error\n");
			continue;
		}
		if (pid == 0)
		{
			char *argv[] = {command, NULL};

			if (execve(command, argv, NULL) == -1)
			{
				_puts(command);
				_puts(": Command not found\n");
			}
			_exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
		}
	}

	return (0);
}
