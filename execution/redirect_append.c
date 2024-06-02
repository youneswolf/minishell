/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 00:20:42 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/29 11:48:03 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_append(int fd)
{
	int	i;

	if (fd == -1)
	{
		perror("Error opening file");
	}
	i = dup2(fd, STDOUT_FILENO);
	if (i == -1)
	{
		perror("Error duplica33ting file descriptor");
		close(fd);
	}
}

int	count_nodes(t_holder *holder)
{
	int	i;

	i = 0;
	while (holder)
	{
		i++;
		holder = holder->next;
	}
	return (i);
}

void	put_var_in_env(t_export *vars, t_env **env)
{
	vars->value = ft_substr(vars->line_tmp->args_built_in[vars->j],
			vars->i + 1,
			ft_strlen(vars->line_tmp->args_built_in[vars->j])
			- vars->i - 1);
	(*env)->env = ft_strjoin((*env)->env, vars->value, 2);
	free(vars->var_name);
}
