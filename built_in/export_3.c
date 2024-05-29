/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 23:29:15 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/29 10:40:31 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_vars(t_export *vars, t_env **env)
{
	vars->var_name = ft_substr(vars->line_tmp->args_built_in[vars->j], 0,
			vars->i);
	while (*env)
	{
		if (!ft_strncmp(vars->var_name, (*env)->env, ft_strlen((*env)->env)))
		{
			if ((*env)->deleted == 1)
			{
				(*env) = (*env)->next;
				continue ;
			}
			vars->value = ft_substr(vars->line_tmp->args_built_in[vars->j],
					vars->i, ft_strlen(vars->line_tmp->args_built_in[vars->j])
					- vars->i);
			vars->join = ft_strjoin(vars->var_name, vars->value, 2);
			free((*env)->env);
			(*env)->env = vars->join;
			break ;
		}
		*env = (*env)->next;
	}
	if (!(*env))
		if_not_in_env(vars, env);
	(1)  && (vars->j++, vars->i = 0);
	*env = vars->tmp;
}

void	print_error(t_export *vars)
{
	printf("bash: export: `%s' not a valid identifier\n",
		vars->line_tmp->args_built_in[vars->j]);
	vars->j++;
	vars->i = 0;
	vars->is_invalid = 1;
	ft_status(1, 1);
}

void	check_validity(t_export *vars, t_env **env)
{
	if (vars->i == 0 
		&& (vars->line_tmp->args_built_in[vars->j][vars->i] == '='))
	{
		print_error(vars);
	}
	else
	{
		while (vars->line_tmp->args_built_in[vars->j][vars->i]
				&& vars->line_tmp->args_built_in[vars->j][vars->i] != '=')
		{
			if (vars->line_tmp->args_built_in[vars->j][vars->i] == '.'
					|| vars->line_tmp->args_built_in[vars->j][vars->i] == ','
					|| vars->line_tmp->args_built_in[vars->j][vars->i] == '/'
					|| vars->line_tmp->args_built_in[vars->j][vars->i] == '-'
					|| vars->line_tmp->args_built_in[vars->j][vars->i] == ':')
			{
				print_error(vars);
				break ;
			}
			vars->i++;
		}
	}
}

void	put_env_value(t_export *vars, t_env **env)
{
	int	i;

	i = 1;
	vars->var_name = ft_substr(vars->line_tmp->args_built_in[vars->j], 0,
			vars->i - 1);
	while (*env)
	{
		if (!ft_strncmp(vars->var_name, (*env)->env, ft_strlen((*env)->env)))
		{
			if ((*env)->deleted == 1)
			{
				(*env) = (*env)->next;
				continue ;
			}
			vars->value = ft_substr(vars->line_tmp->args_built_in[vars->j],
					vars->i + 1,
					ft_strlen(vars->line_tmp->args_built_in[vars->j])
					- vars->i - 1);
			(*env)->env = ft_strjoin((*env)->env, vars->value, 2);
			free(vars->var_name);
			i = 0;
			break ;
		}
		(*env) = (*env)->next;
	}
	if (i)
		if_not_in_env1(vars, env);
	else
		vars->j++;
}

void	export_vars(t_export *vars, t_holder **holder, t_env **env)
{
	vars->is_invalid = 0;
	vars->line_tmp = *holder;
	vars->tmp = *env;
	vars->value = NULL;
	vars->i = 0;
	vars->j = 1;
}
