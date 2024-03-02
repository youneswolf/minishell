#include "minishell.h"

char **cpy_in_2d(char **str)
{
	int i;
	int j;
	char **new_str;
	i = 0;
	while (str[i])
	{
		i++;
	}
	new_str = malloc(sizeof(char *) * (i + 1));
	if (!new_str)
		exit(0);
	i = 0;
	while (str[i])
	{
		j = 0;
		new_str[i] = malloc(sizeof(char) * (ft_strlen(str[i]) + 1));
		if (!new_str[i])
			(free2darray(new_str, i), exit(0));
		while (str[j])
		{
			new_str[i][j] = str[i][j];
			j++;
		}
		i++;
	}
	new_str[i] = NULL;
	return (new_str);
}