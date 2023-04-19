#include "shell.h"

char *error_126(char **args);
char *error_127(char **args);

/**
 * error_126 - Creates an error message for permission denied failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_126(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa_(historyCounter);
	if (!hist_str)
		return (NULL);

	len = _str_len_(globalProgramName) + _str_len_(hist_str) + _str_len_(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

    _str_cpy_(error, globalProgramName);
    _str_cat_(error, ": ");
    _str_cat_(error, hist_str);
    _str_cat_(error, ": ");
    _str_cat_(error, args[0]);
    _str_cat_(error, ": Permission denied\n");

	free(hist_str);
	return (error);
}

/**
 * error_127 - Creates an error message for command not found failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_127(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa_(historyCounter);
	if (!hist_str)
		return (NULL);

	len = _str_len_(globalProgramName) + _str_len_(hist_str) + _str_len_(args[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

    _str_cpy_(error, globalProgramName);
    _str_cat_(error, ": ");
    _str_cat_(error, hist_str);
    _str_cat_(error, ": ");
    _str_cat_(error, args[0]);
    _str_cat_(error, ": not found\n");

	free(hist_str);
	return (error);
}
