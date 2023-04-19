#include "shell.h"

/**
 * helpAll - Displays all possible builtin shellby commands.
 */
void helpAll(void)
{
	char *msg = "Shellby\nThese shell commands are defined internally.\n";

	write(STDOUT_FILENO, msg, _str_len_(msg));
	msg = "Type 'help' to see this list.\nType 'help globalProgramName' to find ";
	write(STDOUT_FILENO, msg, _str_len_(msg));
	msg = "out more about the function 'globalProgramName'.\n\n  alias   \t";
	write(STDOUT_FILENO, msg, _str_len_(msg));
	msg = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, msg, _str_len_(msg));
	msg = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, msg, _str_len_(msg));
	msg = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, msg, _str_len_(msg));
	msg = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, msg, _str_len_(msg));
}

/**
 * helpAlias - Displays information on the shellby builtin command 'alias'.
 */
void helpAlias(void)
{
	char *msg = "alias: alias [NAME[='VALUE'] ...]\n\tHandles alias_list.\n";

	write(STDOUT_FILENO, msg, _str_len_(msg));
	msg = "\n\talias: Prints a list of all alias_list, one per line, in ";
	write(STDOUT_FILENO, msg, _str_len_(msg));
	msg = "the format NAME='VALUE'.\n\talias globalProgramName [name2 ...]:prints";
	write(STDOUT_FILENO, msg, _str_len_(msg));
	msg = " the alias_list globalProgramName, name2, etc. one per line, in the ";
	write(STDOUT_FILENO, msg, _str_len_(msg));
	msg = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, msg, _str_len_(msg));
	msg = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, msg, _str_len_(msg));
	msg = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, msg, _str_len_(msg));
}

/**
 * helpCd - Displays information on the shellby builtin command 'cd'.
 */
void helpCd(void)
{
	char *msg = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, msg, _str_len_(msg));
	msg = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, msg, _str_len_(msg));
	msg = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, msg, _str_len_(msg));
	msg = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, msg, _str_len_(msg));
	msg = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, msg, _str_len_(msg));
	msg = "after a change of directory.\n";
	write(STDOUT_FILENO, msg, _str_len_(msg));
}

/**
 * helpExit - Displays information on the shellby builtin command 'exit'.
 */
void helpExit(void)
{
	char *msg = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, msg, _str_len_(msg));
	msg = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, msg, _str_len_(msg));
	msg = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, msg, _str_len_(msg));
	msg = " exit 0.\n";
	write(STDOUT_FILENO, msg, _str_len_(msg));
}

/**
 * hhelp - Displays information on the shellby builtin command 'help'.
 */
void hhelp(void)
{
	char *msg = "help: help\n\tSee all possible Shellby builtin commands.\n";

	write(STDOUT_FILENO, msg, _str_len_(msg));
	msg = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, msg, _str_len_(msg));
	msg = "builtin command.\n";
	write(STDOUT_FILENO, msg, _str_len_(msg));
}
