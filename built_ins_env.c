#include "shell.h"

/**
 * built_in_env - shows the environment where the shell runs
 *
 * @data: struct for the program's data
 *
 * Return: zero if sucess, or other number if its declared in the arguments
 */

int built_in_env(data_of_program *data)
{
	int i;
	char copy_name[50] = {'\0'};
	char *var_copy = NULL;

	if (data->tokens[1] == NULL)
		print_environ(data);
	else
	{
		for (i = 0; data->tokens[1][i]; i++)
		{
			if (data->tokens[1][i] == '=')
			{

				var_copy = str_duplicate(env_get_key(copy_name, data));
				if (var_copy != NULL)
					env_set_key(copy_name, data->tokens[1] + i + 1, data);


				print_environ(data);
				if (env_get_key(copy_name, data) == NULL)
				{
					_print(data->tokens[1]);
					_print("\n");
				}
				else
				{
					env_set_key(copy_name, var_copy, data);
					free(var_copy);
				}
				return (0);
			}
			copy_name[i] = data->tokens[1][i];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * built_in_set_env - ............
 *
 * @data: struct for the program's data
 *
 * Return: 0 if sucess, or other ..........
 */
int built_in_set_env(data_of_program *data)
{

	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	env_set_key(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * built_in_unset_env - ...............
 *
 * @data: struct for the program's data'
 *
 * Return: ..
 */

int built_in_unset_env(data_of_program *data)
{
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	env_remove_key(data->tokens[1], data);

	return (0);
}
