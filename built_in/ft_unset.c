#include "../minishell.h"

// int	ft_isdigit(int c)
// {
// 	if ((char )c >= 48 && (char )c <= 57)
// 	{
// 		return (1);
// 	}
// 	return (0);
// }
void remove_node(t_env **mini_env, int i)
{
	t_env *tmp;
	t_env *join;
	t_env *head;
	int j;
	t_env *new_list;
	head = *mini_env;
	j = 0;
	while (*mini_env)
	{
		if (i == 0)
		{
			(*mini_env)->deleted =1;
			break;
		}
		if (j == i - 1)
		{
			join = (*mini_env)->next;
			(*mini_env)->next->deleted = 1;
			// (*mini_env)->next = (*mini_env)->next->next;
			break;
			// free(join->env);
			// free(join);

		}
		*mini_env = (*mini_env)->next;
		j++;
	}
	*mini_env = head;
}
int check_unset_syntax(char *str)
{
	int i;

	i = 0;
	if (str && str[0] && ft_isdigit(str[0]))
	{
		ft_status(1,1);
		return (0);
	}
	while (str && str[i])
	{
		if (str[i] == '.'|| str[i] == ',' || str[i] == '/'|| str[i] == '-'
			|| str[i] == ':' || str[i] == '=' || str[i] == '+')
		{
			ft_status(1,1);
			return (0);
		}
		i++;
	}
	return (1);
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
		if (!check_unset_syntax(holder->args_built_in[ind]))
		{
			ind++;
			continue;
		}
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
