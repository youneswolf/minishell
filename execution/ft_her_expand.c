/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_her_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:40:59 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/28 01:17:38 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_sgl_quote(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == 39)
			count++;
		i++;
	}
	return (count);
}

void	join_exp_1dollar_here(t_exp *vars, t_env **env)
{
	vars->join = ft_strjoin(vars->join, expand_here(vars->split->str, env), 2);
	if (vars->split->next)
		vars->join = ft_strjoin(vars->join, " ", 1);
}

void	isolate_specials_and_var(t_expan *vars)
{
	while (vars->sub && vars->sub[vars->i])
	{
		if (vars->sub[vars->i] == '.' || vars->sub[vars->i] == ',' 
			|| vars->sub[vars->i] == '/' || vars->sub[vars->i] == '-' 
			|| vars->sub[vars->i] == ':' || vars->sub[vars->i] == 34 
			|| vars->sub[vars->i] == 39)
		{
			vars->j = vars->i;
			while (vars->sub [vars->j] && vars->sub[vars->j] != '$')
				vars->j++;
			vars->special = ft_sub_str(vars->sub, vars->i,
					vars->j - vars->i, 0);
			vars->pre_var = ft_sub_str(vars->sub, 0, vars->i, 0);
			break ;
		}
		vars->i++;
	}
}

char	*expand_here(char *str, t_env **env)
{
	t_expan	vars;

	initialize_vars(&vars, env);
	while (str && str[vars.i] != '$')
		vars.i++;
	if (vars.i && vars.i != ft_strlen(str))
		vars.pre_special = ft_substr(str, 0, vars.i);
	vars.sub = ft_sub_str (str, vars.i + 1, (ft_strlen(str) - vars.i - 1), 0);
	vars.i = 0;
	isolate_specials_and_var(&vars);
	if (vars.pre_var)
	{
		vars.var = ft_strjoin(vars.pre_var, "=", 1);
		free(vars.sub);
	}
	else
		vars.var = ft_strjoin(vars.sub, "=", 1);
	if (expand_env(&vars))
		return (vars.var);
	free(vars.var);
	vars.i = 0;
	vars.j = 42;
	return (ft_strjoin(vars.pre_special, vars.special, 2));
}
