#include "shell.h"



/**
 * sig_handler - Prints a new prompt upon a signal.
 * @sig: The signal.
 */
void sig_handler(int sig)
{
	char *new_prompt = "\n$ ";

	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, new_prompt, 3);
}

/**
 * execute - Executes a command in a child process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last executed command.
 */
int execute(char **args, char **front)
{
	pid_t child_pid;
	int status, flag = 0, ret = 0;
	char *command = args[0];

	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = get_location(command);
	}

	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (make_error(args, 126));
		else
			ret = (make_error(args, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(command);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(command, args, environ);
			if (errno == EACCES)
				ret = (make_error(args, 126));
			free_env();
            free_argmnts(args, front);
			free_alias_list(alias_list);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(command);
	return (ret);
}

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	int ret = 0, retn;
	int *exe_ret = &retn;
	char *prompt = "$ ", *new_line = "\n";

    globalProgramName = argv[0];
    historyCounter = 1;
    alias_list = NULL;
	signal(SIGINT, sig_handler);

	*exe_ret = 0;
	environ = _copyenv();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		ret = procFileCommands(argv[1], exe_ret);
		free_env();
		free_alias_list(alias_list);
		return (*exe_ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != ENDOFFILE && ret != EXIT)
			ret = handle_argmnts(exe_ret);
		free_env();
		free_alias_list(alias_list);
		return (*exe_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = handle_argmnts(exe_ret);
		if (ret == ENDOFFILE || ret == EXIT)
		{
			if (ret == ENDOFFILE)
				write(STDOUT_FILENO, new_line, 1);
			free_env();
			free_alias_list(alias_list);
			exit(*exe_ret);
		}
	}

	free_env();
	free_alias_list(alias_list);
	return (*exe_ret);
}
