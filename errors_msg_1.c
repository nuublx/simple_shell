#include "shell.h"

char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
/**
 * error_env - Creates an error message for shellby_env errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_env(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa_(historyCounter);
	if (!hist_str)
		return (NULL);

	args--;
	len = _str_len_(globalProgramName) + _str_len_(hist_str) + _str_len_(args[0]) + 45;
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
    _str_cat_(error, ": Unable to add/remove from environment\n");

	free(hist_str);
	return (error);
}

/**
 * error_1 - Creates an error message for shellby_alias errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_1(char **args)
{
	char *error;
	int len;

	len = _str_len_(globalProgramName) + _str_len_(args[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

    _str_cpy_(error, "alias: ");
    _str_cat_(error, args[0]);
    _str_cat_(error, " not found\n");

	return (error);
}

/**
 * error_2_exit - Creates an error message for shellby_exit errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_exit(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa_(historyCounter);
	if (!hist_str)
		return (NULL);

	len = _str_len_(globalProgramName) + _str_len_(hist_str) + _str_len_(args[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

    _str_cpy_(error, globalProgramName);
    _str_cat_(error, ": ");
    _str_cat_(error, hist_str);
    _str_cat_(error, ": exit: Illegal number: ");
    _str_cat_(error, args[0]);
    _str_cat_(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * error_2_cd - Creates an error message for shellby_cd errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_cd(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa_(historyCounter);
	if (!hist_str)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
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
	if (args[0][0] == '-')
        _str_cat_(error, ": cd: Illegal option ");
	else
        _str_cat_(error, ": cd: can't cd to ");
    _str_cat_(error, args[0]);
    _str_cat_(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * error_2_syntax - Creates an error message for syntax errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_syntax(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa_(historyCounter);
	if (!hist_str)
		return (NULL);

	len = _str_len_(globalProgramName) + _str_len_(hist_str) + _str_len_(args[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

    _str_cpy_(error, globalProgramName);
    _str_cat_(error, ": ");
    _str_cat_(error, hist_str);
    _str_cat_(error, ": Syntax error: \"");
    _str_cat_(error, args[0]);
    _str_cat_(error, "\" unexpected\n");

	free(hist_str);
	return (error);
}
