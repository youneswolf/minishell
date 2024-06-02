/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 22:32:00 by asedoun           #+#    #+#             */
/*   Updated: 2024/06/02 20:33:10 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_first_is_nbr(char *str)
{
	int	i;
	int j;

	j = 0;
	i = 0;
	if (str && str[0] && str[0] >= '0' && str[0] <= '9')
		return (0);
	while (str && str[i] && str[i] != '=')
	{
		if (str[i] == '+')
			j++;
		if (j && str[i] == '+')
			return (0);
		i++;
	}                                
	return (1);
}

void	check_first_is_nbr2(t_export *vars)
{
	printf("bash: export: `%s': not a valid identifier\n",
		vars->line_tmp->args_built_in[vars->j]);
	vars->j++;
	ft_status(1, 1);
}

int	check_if_addition(char **str, t_export *vars)
{
	if (str && vars->i != 0 && str[vars->j][vars->i - 1] == '+')
		return (1);
	return (0);
}

void	check_env_vars(t_export *vars, t_env **env)
{
	if (check_if_addition(vars->line_tmp->args_built_in, vars))
		put_env_value(vars, env);
	else
		add_vars(vars, env);
}

void	exec_export(t_holder **holder, t_env **env)
{
	t_export	vars;

	export_vars(&vars, holder, env);
	if (!vars.line_tmp->args_built_in[1])
		declare_export(*env);
	else
	{
		while (vars.line_tmp->args_built_in[vars.j])
		{
			if (!check_first_is_nbr(vars.line_tmp->args_built_in[vars.j]))
			{
				check_first_is_nbr2(&vars);
				continue ;
			}
			check_validity(&vars, env);
			if (vars.is_invalid == 1)
			{
				vars.is_invalid = 0;
				continue ;
			}
			check_env_vars(&vars, env);
			ft_status(1, 0);
		}
	}
}
