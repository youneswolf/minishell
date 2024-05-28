/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 01:52:27 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/28 02:41:43 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	join_exp_1dollar(t_exp *vars, t_env **env)
{
	vars->join = ft_strjoin(vars->join, expand(vars->split->str, env, 1, 0), 2);
	if (vars->split->next)
	{
		vars->join = ft_strjoin(vars->join, " ", 1);
	}
}

char	*handle_expand(char *line_str, t_env **env)
{
	t_exp	vars;

	vars.i = 0;
	vars.j = 0;
	vars.split = get_exp_node(line_str);
	free(line_str);
	vars.join = NULL;
	vars.str = NULL;
	vars.dollar_str = NULL;
	vars.node = vars.split;
	while (vars.split)
	{
		if (count_dollar(vars.split->str) > 1)
			join_exp(&vars, env);
		else 
			join_exp_1dollar(&vars, env);
		vars.split = vars.split->next;
	}
	ft_free_list2(&vars.node);
	if (!vars.join)
		return (ft_strdup(""));
	return (vars.join);
}

int	is_number(char *str)
{
	if (str[1] && str[1] >= '0' && str[1] <= '9')
		return (1);
	return (0);
}

char	*expand_nbr(char *str)
{
	char	*expanded;

	expanded = ft_sub_str(str, 2, ft_strlen(str) -2, 0);
	if (!expanded)
		return ("");
	return (expanded);
}

void	expand_vars(t_expan *vars)
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
