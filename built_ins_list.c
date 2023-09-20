#include "shell.h"

/**
 * built_ins_list - search for match and execute the associate builtin
 * @data: struct for the program's data
 * Return: Returns the return of the function executed is there is a match,
 * otherwise returns -1.
 **/
int built_ins_list(data_of_program *data)
{
	int iterator;
	built_ins options[] = {
		{"exit", built_in_exit},
		{"help", built_in_help},
		{"cd", built_in_cd},
		{"alias", built_in_alias},
		{"env", built_in_env},
		{"setenv", built_in_set_env},
		{"unsetenv", built_in_unset_env},
		{NULL, NULL}
	};

	for (iterator = 0; options[iterator].built_in != NULL; iterator++)
	{

		if (str_compare(options[iterator].built_in, data->command_name, 0))
		{

			return (options[iterator].function(data));
		}
	}
	return (-1);
}
