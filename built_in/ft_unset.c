/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 23:49:59 by asedoun           #+#    #+#             */
/*   Updated: 2024/06/03 12:39:18 by asedoun          ###   ########.fr       */
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
		if (j == i)
		{
			(*mini_env)->deleted = 1;
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

void	unset_loop(t_unset *vars, t_env **mini_env)
{
	while (vars->tmp)
	{
		if (!ft_strncmp(vars->value, vars->tmp->env, ft_strlen(vars->value)))
		{
			if (vars->tmp->deleted == 1)
			{
				vars->tmp = vars->tmp->next;
				vars->i++;
				continue ;
			}
			free(vars->value);
			remove_node(mini_env, vars->i);
			break ;
		}
		vars->tmp = vars->tmp->next;
		vars->i++;
	}
}

int	check_is_equal(char *str, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(str, tmp->env, ft_strlen(tmp->env)))
			return (0);
		tmp = tmp->next;
	}
	return (1);
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
		if (check_is_equal(holder->args_built_in[vars.ind], mini_env))
			vars.value = ft_strjoin(holder->args_built_in[vars.ind], "=", 0);
		else
			vars.value = ft_strdup(holder->args_built_in[vars.ind]);
		vars.tmp = *mini_env;
		vars.i = 0;
		unset_loop(&vars, mini_env);
		vars.ind++;
	}
}
