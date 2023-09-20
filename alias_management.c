#include "shell.h"

/**
 * print_alias - add or remove or show aliases
 *
 * @data: struct program's data
 *
 * @alias: name of the alias to be printed
 *
 * Return: 0 if sucess, or number if arguments
 */

int print_alias(data_of_program *data, char *alias)
{
	int a;
	int b;
	int alias_len;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_len = str_length(alias);
		for (a = 0; data->alias_list[a]; a++)
		{
			if (!alias || (str_compare(data->alias_list[a], alias, alias_len)
				&&	data->alias_list[a][alias_len] == '='))
			{
				for (b = 0; data->alias_list[a][b]; b++)
				{
					buffer[b] = data->alias_list[a][b];
					if (data->alias_list[a][b] == '=')
						break;
				}
				buffer[b + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[a] + b + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - add or remove or show aliases
 *
 * @data: struct for the program's data
 *
 * @name: name of the requested alias.
 *
 * Return: 0 if success, or number if arguments
 */
char *get_alias(data_of_program *data, char *name)
{
	int a;
	int alias_len;

	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_len = str_length(name);

	for (a = 0; data->alias_list[a]; a++)
	{
		if (str_compare(name, data->alias_list[a], alias_len) &&
			data->alias_list[a][alias_len] == '=')
		{
			return (data->alias_list[a] + alias_len + 1);
		}
	}

	return (NULL);

}

/**
 * set_alias - add, or override alias
 *
 * @alias_string: alias to be seted in the form (name='value')
 *
 * @data: struct for the program's data
 *
 * Return: 0 if success, or number if arguments
 */
int set_alias(char *alias_string, data_of_program *data)
{
	int a, b;
	char buffer[250] = {'0'}, *tmp = NULL;

	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);

	for (a = 0; alias_string[a]; a++)
		if (alias_string[a] != '=')
			buffer[a] = alias_string[a];
		else
		{
			tmp = get_alias(data, alias_string + a + 1);
			break;
		}


	for (b = 0; data->alias_list[b]; b++)
		if (str_compare(buffer, data->alias_list[b], a) &&
			data->alias_list[b][a] == '=')
		{
			free(data->alias_list[b]);
			break;
		}

	if (tmp)
	{
		buffer_add(buffer, "=");
		buffer_add(buffer, tmp);
		data->alias_list[b] = str_duplicate(buffer);
	}
	else
		data->alias_list[b] = str_duplicate(alias_string);
	return (0);
}
