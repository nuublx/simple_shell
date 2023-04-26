#include "shell.h"

/**
 * get_argmnts - Gets a command from standard input.
 * @line: A buffer to store the command.
 * @exe_ret: The return value of the last executed command.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *get_argmnts(char *line, int *exe_ret)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
		free(line);

	read = _getline(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		historyCounter++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_argmnts(line, exe_ret));
	}

	line[read - 1] = '\0';
	replace_variable(&line, exe_ret);
	handle_line_entered(&line, read);

	return (line);
}

/**
 * call_argmnts - Partitions operators from commands and calls them.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int call_argmnts(char **args, char **front, int *exe_ret)
{
	int ret, index, flag = -1;

	if (!args[0])
		return (*exe_ret);
	for (index = 0; args[index]; index++)
	{
		if (_str_n_cmp_(args[index], "||", 2) == 0)
			flag = 0;

		else if (_str_n_cmp_(args[index], "&&", 2) == 0)
			flag = 1;

		free(args[index]);
		args[index] = NULL;
		args = replaceAliases(args);
		ret = run_argmnts(args, front, exe_ret);
		if (flag == 0)
		{
			if (*exe_ret != 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
		else if (flag == 1)
		{
			if (*exe_ret == 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
	}
	args = replaceAliases(args);
	ret = run_argmnts(args, front, exe_ret);
	return (ret);
}

/**
 * run_argmnts - Calls the execution of a command.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int run_argmnts(char **args, char **front, int *exe_ret)
{
	int ret, i;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, front);
		if (ret != EXIT)
			*exe_ret = ret;
	}
	else
	{
		*exe_ret = execute(args, front);
		ret = *exe_ret;
	}

	historyCounter++;

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (ret);
}

/**
 * handle_argmnts - Gets, calls, and runs the execution of a command.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: If an end-of-file is read - ENDOFFILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int handle_argmnts(int *exe_ret)
{
	int ret = 0, index;
	char **args, *line = NULL, **front;

	line = get_argmnts(line, exe_ret);
	if (!line)
		return (ENDOFFILE);

	args = _strtok_(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (check_argmnts(args) != 0)
	{
		*exe_ret = 2;
        free_argmnts(args, args);
		return (*exe_ret);
	}
	front = args;

	for (index = 0; args[index]; index++)
	{
		if (_str_n_cmp_(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			ret = call_argmnts(args, front, exe_ret);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		ret = call_argmnts(args, front, exe_ret);

	free(front);
	return (ret);
}

/**
 * check_argmnts - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @args: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *	   Otherwise - 0.
 */
int check_argmnts(char **args)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; args[i]; i++)
	{
		cur = args[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (make_error(&args[i], 2));
			nex = args[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (make_error(&args[i + 1], 2));
		}
	}
	return (0);
}
