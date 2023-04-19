#include "shell.h"

int shellby_alias(char **args, char __attribute__((__unused__)) **front);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);

/**
 * shellby_alias - Builtin command that either prints all alias_list, specific
 * alias_list, or sets an alias.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellby_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *temp = alias_list;
	int i, ret = 0;
	char *value;

	if (!args[0])
	{
		while (temp)
		{
			print_alias(temp);
			temp = temp->next;
		}
		return (ret);
	}
	for (i = 0; args[i]; i++)
	{
		temp = alias_list;
		value = _str_chr_(args[i], '=');
		if (!value)
		{
			while (temp)
			{
				if (_str_cmp_(args[i], temp->name) == 0)
				{
					print_alias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret = make_error(args + i, 1);
		}
		else
			set_alias(args[i], value);
	}
	return (ret);
}

/**
 * set_alias - Will either set an existing alias 'globalProgramName' with a new value,
 * 'value' or creates a new alias with 'globalProgramName' and 'value'.
 * @var_name: Name of the alias.
 * @value: Value of the alias. First character is a '='.
 */
void set_alias(char *var_name, char *value)
{
	alias_t *temp = alias_list;
	int len, j, k;
	char *new_value;

	*value = '\0';
	value++;
	len = _str_len_(value) - _str_spn_(value, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;
	for (j = 0, k = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			new_value[k++] = value[j];
	}
	new_value[k] = '\0';
	while (temp)
	{
		if (_str_cmp_(var_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = new_value;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_alias_end(&alias_list, var_name, new_value);
}

/**
 * print_alias - Prints the alias in the format globalProgramName='value'.
 * @alias: Pointer to an alias.
 */
void print_alias(alias_t *alias)
{
	char *alias_string;
	int len = _str_len_(alias->name) + _str_len_(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
    _str_cpy_(alias_string, alias->name);
    _str_cat_(alias_string, "='");
    _str_cat_(alias_string, alias->value);
    _str_cat_(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}
/**
 * replaceAliases - Goes through the arguments and replace any matching alias
 * with their value.
 * @args: 2D pointer to the arguments.
 *
 * Return: 2D pointer to the arguments.
 */
char **replaceAliases(char **args)
{
	alias_t *temp;
	int i;
	char *new_value;

	if (_str_cmp_(args[0], "alias") == 0)
		return (args);
	for (i = 0; args[i]; i++)
	{
		temp = alias_list;
		while (temp)
		{
			if (_str_cmp_(args[i], temp->name) == 0)
			{
				new_value = malloc(sizeof(char) * (_str_len_(temp->value) + 1));
				if (!new_value)
				{
                    free_argmnts(args, args);
					return (NULL);
				}
                _str_cpy_(new_value, temp->value);
				free(args[i]);
				args[i] = new_value;
				i--;
				break;
			}
			temp = temp->next;
		}
	}

	return (args);
}
