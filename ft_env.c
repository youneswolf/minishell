#include "minishell.h"

void exec_env(t_env **mini_env)
{
	int i;
	t_env *tmp;

	tmp = *mini_env;
	while (tmp)
	{
		printf("%s\n",tmp->env);
		tmp = tmp->next;
	}
}
