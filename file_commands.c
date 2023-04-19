#include "shell.h"

int cant_open(char *file_path);
int procFileCommands(char *file_path, int *exe_ret);

/**
 * cant_open - If the file doesn't exist or lacks proper permissions, print
 * a cant open error.
 * @file_path: Path to the supposed file.
 *
 * Return: 127.
 */

int cant_open(char *file_path)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa_(historyCounter);
	if (!hist_str)
		return (127);

	len = _str_len_(globalProgramName) + _str_len_(hist_str) + _str_len_(file_path) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (127);
	}

    _str_cpy_(error, globalProgramName);
    _str_cat_(error, ": ");
    _str_cat_(error, hist_str);
    _str_cat_(error, ": Can't open ");
    _str_cat_(error, file_path);
    _str_cat_(error, "\n");

	free(hist_str);
	write(STDERR_FILENO, error, len);
	free(error);
	return (127);
}

/**
 * procFileCommands - Takes a file and attempts to run the commands stored
 * within.
 * @file_path: Path to the file.
 * @exe_ret: Return value of the last executed command.
 *
 * Return: If file couldn't be opened - 127.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of the last command ran.
 */
int procFileCommands(char *file_path, int *exe_ret)
{
	ssize_t file, b_read, i;
	unsigned int line_size = 0;
	unsigned int old_size = 120;
	char *line, **args, **front;
	char buffer[120];
	int ret;

    historyCounter = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_ret = cant_open(file_path);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && line_size == 0)
			return (*exe_ret);
		buffer[b_read] = '\0';
		line_size += b_read;
		line = _realloc_(line, old_size, line_size);
        _str_cat_(line, buffer);
		old_size = line_size;
	} while (b_read);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < line_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
    replace_variable(&line, exe_ret);
    handle_line_entered(&line, line_size);
	args = _strtok_(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_argmnts(args) != 0)
	{
		*exe_ret = 2;
        free_argmnts(args, args);
		return (*exe_ret);
	}
	front = args;

	for (i = 0; args[i]; i++)
	{
		if (_str_n_cmp_(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = call_argmnts(args, front, exe_ret);
			args = &args[++i];
			i = 0;
		}
	}

	ret = call_argmnts(args, front, exe_ret);

	free(front);
	return (ret);
}
