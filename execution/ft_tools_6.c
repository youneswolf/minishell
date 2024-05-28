/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 01:53:11 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/28 02:49:29 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_env(t_expan *vars)
{
	while (vars->tmp && vars->var)
	{
		if (!ft_strncmp(vars->var, vars->tmp->env, ft_strlen(vars->var)))
		{
			if (vars->tmp->deleted == 1)
				return (NULL);
			vars->i = 0;
			free(vars->var);
			vars->var = ft_strjoin(vars->tmp->env, vars->special, 3);
			while (vars->var && vars->var[vars->i] != '=')
				vars->i++;
			vars->var = ft_sub_str(vars->var, vars->i + 1,
					ft_strlen(vars->var) - vars->i - 1, 1);
			vars->var = ft_strjoin(vars->pre_special, vars->var, 2);
			return (vars->var);
		}
		vars->tmp = vars->tmp->next;
	}
	return (NULL);
}

void	initialize_vars(t_expan *vars, t_env **env)
{
	vars->special = NULL;
	vars->pre_special = NULL;
	vars->sub = NULL;
	vars->pre_var = NULL;
	vars->tmp = *env;
	vars->i = 0;
	vars->j = 0;
}

void	get_var(t_expan *vars)
{
	vars->var = ft_strjoin(vars->pre_var, "=", 1);
	free(vars->sub);
}

char	*expand(char *str, t_env **env, int last, int quotes)
{
	t_expan	vars;

	initialize_vars(&vars, env);
	if ((is_sgl_quote_ex(str, last) && is_char(str) && quotes != 2) 
		|| quotes == 1)
		return (ft_strdup(str));
	if (!if_dollar(str))
		return (ft_strdup(str));
	if (is_number(str))
		return (expand_nbr(str));
	while (str && str[vars.i] && str[vars.i] != '$')
		vars.i++;
	if (vars.i && vars.i != ft_strlen(str))
		vars.pre_special = ft_sub_str(str, 0, vars.i, 0);
	vars.sub = ft_sub_str(str, vars.i + 1, (ft_strlen(str) - vars.i -1), 0);
	vars.i = 0;
	expand_vars(&vars);
	if (vars.pre_var)
		get_var(&vars);
	else
		vars.var = ft_strjoin(vars.sub, "=", 1);
	if (expand_env(&vars))
		return (vars.var);
	free(vars.var);
	return (ft_strjoin(vars.pre_special, vars.special, 2));
}

void	fill_null_env(t_env **mini_env)
{
	t_env	*node;
	char	*line;
	int		len;
	int		i;
	char	*first;

	i = 0;
	first = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	node = malloc(sizeof(t_env));
	if (!node)
		(ft_free_nodes(mini_env), exit(1));
	node->env = first;
	node->printed = 0;
	node->deleted = 0;
	node->next = NULL;
	*mini_env = node;
	fill_second_null_env(mini_env);
}
