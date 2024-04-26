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
			write(1 ,holder->args_built_in[i], 1);
			i++;
		}
		if (holder->args_built_in[i])
			write(1, holder->args_built_in[i], 1);
	}
	else
	{
		while (holder->args_built_in[j + 2])
		{
			write(1 ,holder->args_built_in[j + 1], 1);
			j++;
		}
		if (holder->args_built_in[j + 1])
			write(1, holder->args_built_in[j + 1], 1);
		write(1, "\n", 1);
	}
}