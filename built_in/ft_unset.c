#include "../minishell.h"
void remove_node(t_env **mini_env, int i)
{
	t_env *tmp;
	t_env *join;
	t_env *head;
	int j;

	head = *mini_env;
	j = 0;
	while (*mini_env)
	{
		if (j == i - 1)
		{
			join = (*mini_env)->next;
			(*mini_env)->next = (*mini_env)->next->next;
			free(join->env);
			free(join);

		}
		*mini_env = (*mini_env)->next;
		j++;
	}
	*mini_env = head;
}

void exec_unset(t_env **mini_env, t_holder *holder)
{
	t_env *tmp;
	char *sub;
	char *value;
	t_line *tmp1;
	int i;
	int j;
    int ind = 1;
	tmp = *mini_env;
	while (holder->args_built_in[ind])
	{
		value = ft_strjoin(holder->args_built_in[ind], "=",0);
		i = 0;
		while (tmp)
		{
			if (!ft_strncmp(value, tmp->env, ft_strlen(value)))
			{
				free(value);
				remove_node(mini_env, i);
				break;
			}
			tmp = tmp->next;
			i++;
		}
	ind++;
	}
}
