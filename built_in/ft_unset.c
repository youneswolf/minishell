/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 23:49:59 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/29 11:20:58 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_node(t_env **mini_env, int i)
{
	t_env	*head;
	int		j;

	head = *mini_env;
	j = 0;
	while (*mini_env)
	{
		if (i == 0)
		{
			(*mini_env)->deleted = 1;
			break ;
		}
		if (j == i - 1)
		{
			(*mini_env)->next->deleted = 1;
			break ;
		}
		*mini_env = (*mini_env)->next;
		j++;
	}
	*mini_env = head;
}

int	check_unset_syntax(char *str)
{
	int	i;

	i = 0;
	if (str && str[0] && ft_isdigit(str[0]))
	{
		ft_status(1, 1);
		return (0);
	}
	while (str && str[i])
	{
		if (str[i] == '.' || str[i] == ',' || str[i] == '/' || str[i] == '-'
			|| str[i] == ':' || str[i] == '=' || str[i] == '+')
		{
			ft_status(1, 1);
			return (0);
		}
		i++;
	}
	if (i != 0 && str[i - 1] == '!')
	{
		ft_status(1, 1);
		return (0);
	}
	return (1);
}

void	print_error_unset(char *str)
{
	ft_putstr_fd("bash: unset: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" not a valid identifier\n", 2);
}

void	exec_unset(t_env **mini_env, t_holder *holder)
{
	t_unset	vars;

	(1) && (vars.ind = 1, vars.tmp = *mini_env);
	while (holder->args_built_in[vars.ind])
	{
		if (!check_unset_syntax(holder->args_built_in[vars.ind]))
		{
			print_error_unset(holder->args_built_in[vars.ind++]);
			continue ;
		}
		vars.value = ft_strjoin(holder->args_built_in[vars.ind], "=", 0);
		vars.i = 0;
		while (vars.tmp)
		{
			if (!ft_strncmp(vars.value, vars.tmp->env, ft_strlen(vars.value)))
			{
				if (vars.tmp->deleted == 1)
				{
					vars.tmp = vars.tmp->next;
					continue ;
				}
				free(vars.value);
				remove_node(mini_env, vars.i);
				break ;
			}
			vars.tmp = vars.tmp->next;
			vars.i++;
		}
		vars.ind++;
	}
}
