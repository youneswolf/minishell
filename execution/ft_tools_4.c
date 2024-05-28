/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 01:52:01 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/28 02:37:52 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_line	*get_exp_node(char *line_str)
{
	t_exp	vars;

	vars.split = NULL;
	(1) && (vars.i = 0, vars.j = 0);
	while (line_str && line_str[vars.i])
	{
		if (line_str[vars.i] == '$')
		{
			vars.str = ft_split(line_str, 32);
			while (vars.str[vars.j])
			{
				if (!vars.split)
					vars.split = ft_lst_new(ft_strdup(vars.str[vars.j]));
				else
				{
					vars.node = get_last_l(&vars.split);
					vars.node->next = ft_lst_new(ft_strdup(vars.str[vars.j]));
				}
				vars.j++;
			}
			ft_free_2d(vars.str);
		}
		vars.i++;
	}
	return (vars.split);
}

int	check_for_first_elem(char *str)
{
	int	i;

	i = 0;
	if (str && str[0] && str[0] == '$')
		return (0);
	while (str && str[i] && str[i] != '$')
	{
		if (str[i] != '.' || str[i] != ',' || str[i] != '/' 
			|| str[i] != '-' || str[i] != ':')
			return (1);
		i++;
	}
	return (0);
}

int	check_quotes(char *str)
{
	int		i;
	char	quote;
	int		parity;

	parity = 0;
	i = 0;
	if (str && str[0] && (str[0] == 39 || str[0] == 34))
	{
		quote = str[0];
		while (str[parity] == quote)
			parity++;
		i = parity;
		while (str[i])
			i++;
		i--;
		while (str[i] == quote)
		{
			i--;
			parity--;
		}
		if (parity == 0)
			return (quote);
	}
	return (0);
}

void	expanding(t_exp *vars, int check, int quotes, t_env **env)
{
	while (vars->dollar_str[vars->i])
	{
		vars->j = 0;
		vars->dollar_str_space = ft_strtrim(vars->dollar_str[vars->i], " ", 1);
		if (vars->i == 0)
			append_dollar_if_check(vars, check);
		else
			vars->dollar_str_space = ft_strjoin("$", vars->dollar_str_space, 3);
		if (vars->i == 0)
			vars->join = ft_strjoin(vars->join,
					expand(vars->dollar_str_space, env, 1, quotes), 2);
		else
			vars->join = ft_strjoin(vars->join,
					expand(vars->dollar_str_space, env, 0, quotes), 2);
		while (vars->dollar_str[vars->i] && vars->dollar_str[vars->i][vars->j]
			&& vars->dollar_str[vars->i][vars->j] == ' ')
		{
			vars->join = ft_strjoin(vars->join, " ", 1);
			vars->j++;
		}
		vars->i++;
		free(vars->dollar_str_space);
	}
}

void	join_exp(t_exp *vars, t_env **env)
{
	int	check ;
	int	quotes;
	int	dollar;

	quotes = 42;
	vars->i = 0;
	vars->dollar_str = ft_split(vars->split->str, '$');
	check = check_for_first_elem(vars->split->str);
	quotes = check_quotes(vars->split->str);
	if (quotes == 39)
		quotes = 1;
	else if (quotes == 34)
		quotes = 2;
	expanding(vars, check, quotes, env);
	ft_free_2d(vars->dollar_str);
}
