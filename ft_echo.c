#include "minishell.h"
void exec_echo(t_holder *holder)
{
	int i = 1;
	if (!ft_strcmp_asd(holder->args_built_in[i], "-n"))
	{
		i++;
	while (holder->args_built_in[i])
	{
		printf("%s",holder->args_built_in[i]);
		i++;
	}
	}
	else
	{
	while (holder->args_built_in[i])
	{
		printf("%s",holder->args_built_in[i]);
		i++;
	}
	printf("\n");
	}
}