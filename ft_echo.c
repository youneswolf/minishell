#include "minishell.h"
void exec_echo(t_holder *holder)
{
	int i = 1;
	int	j = 0;
	if (!ft_strcmp_asd(holder->args_built_in[i], "-n"))
	{
		i++;
		while (holder->args_built_in[i + 1])
		{
			printf("%s ",holder->args_built_in[i]);
			i++;
		}
		if (holder->args_built_in[i])
			printf("%s", holder->args_built_in[i]);
	}
	else
	{
		while (holder->args_built_in[j + 2])
		{
			printf("%s ",holder->args_built_in[j + 1]);
			j++;
		}
		if (holder->args_built_in[j + 1])
			printf("%s", holder->args_built_in[j + 1]);
		printf("\n");
	}
}