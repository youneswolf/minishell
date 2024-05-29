/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 23:29:31 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/29 09:58:45 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*null_terminate(void)
{
	char	*str;

	str = malloc(1);
	if (!str)
		perror("malloc error");
	str[0] = '\0';
	return (str);
}

void	ft_putstr_export(char *s)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], 1);
		if (s[i] == '=' && !j)
		{
			j = 1;
			write(1, "\"", 1);
		}
		i++;
	}
	if (j)
		write(1, "\"", 1);
}

int	check_is_all_printed(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (tmp->printed == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	if_not_in_env(t_export *vars, t_env **env)
{
	*env = vars->tmp;
	while ((*env)->next)
	{
		(*env) = (*env)->next;
	}
	vars->value = ft_substr(vars->line_tmp->args_built_in[vars->j], vars->i,
			ft_strlen(vars->line_tmp->args_built_in[vars->j]) - vars->i);
	vars->join = ft_strjoin(vars->var_name, vars->value, 2);
	vars->node = malloc(sizeof(t_env));
	vars->node->env = vars->join;
	vars->node->next = NULL;
	vars->node->deleted = 0;
	(*env)->next = vars->node;
}

void	if_not_in_env1(t_export *vars, t_env **env)
{
	*env = vars->tmp;
	while ((*env)->next)
	{
		(*env) = (*env)->next;
	}
	vars->value = ft_substr(vars->line_tmp->args_built_in[vars->j], vars->i,
			ft_strlen(vars->line_tmp->args_built_in[vars->j]) - vars->i);
	vars->join = ft_strjoin(vars->var_name, vars->value, 2);
	vars->node = malloc(sizeof(t_env));
	vars->node->env = vars->join;
	vars->node->next = NULL;
	vars->node->deleted = 0;
	(*env)->next = vars->node;
	vars->j++;
}
