/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_her_expand_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 01:15:17 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/28 01:17:32 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_dollar(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

char	*handle_expand_here(char *line_str, t_env **env)
{
	t_exp	vars;

	vars.i = 0;
	vars.j = 0;
	vars.split = get_exp_node(line_str);
	vars.join = NULL;
	vars.str = NULL;
	vars.dollar_str = NULL;
	vars.node = vars.split;
	while (vars.split)
	{
		if (count_dollar(vars.split->str) > 1)
			join_exp_here(&vars, env);
		else 
			join_exp_1dollar_here(&vars, env);
		vars.split = vars.split->next;
	}
	ft_free_list3(&vars.node);
	free(line_str);
	if (!vars.join)
		return ("");
	return (vars.join);
}

void	here_exp_init_vars(t_exp *vars, int *check)
{
	vars->i = 0;
	vars->dollar_str = ft_split(vars->split->str, '$');
	*check = check_for_first_elem(vars->dollar_str[0]);
}

void	sending_var_to_expand(t_exp *vars, t_env **env)
{
	vars->dollar_str_space = ft_strjoin("$",
			vars->dollar_str_space, 3);
	vars->join = ft_strjoin(vars->join,
			expand_here(vars->dollar_str_space, env), 2);
}

void	join_exp_here(t_exp *vars, t_env **env)
{
	int	check;

	here_exp_init_vars(vars, &check);
	while (vars->dollar_str[vars->i])
	{
		vars->j = 0;
		vars->dollar_str_space = ft_strtrim(vars->dollar_str[vars->i], " ", 1);
		if (vars->i == 0)
		{
			if (check == 0)
				vars->dollar_str_space = ft_strjoin("$",
						vars->dollar_str_space, 3);
		}
		else
			sending_var_to_expand(vars, env);
		while (vars->dollar_str[vars->i] && vars->dollar_str[vars->i][vars->j]
				&& vars->dollar_str[vars->i][vars->j] == ' ')
		{
			vars->join = ft_strjoin(vars->join, " ", 1);
			vars->j++;
		}
		vars->i++;
		free(vars->dollar_str_space);
	}
	ft_free_2d(vars->dollar_str);
}
