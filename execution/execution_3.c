/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 03:49:33 by asedoun           #+#    #+#             */
/*   Updated: 2024/06/03 12:30:52 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_dir(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			return (1);
		}
	}
	return (0);
}

void	no_such_file_or_dir_error(char *str)
{
	ft_putstr_fd("bash ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("  No such file or directory\n", 2);
	exit(127);
}

int	end_with_slash(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	if (i != 0 && str[i - 1] == '/')
		return (1);
	return (0);
}

void	cmd_file_stat(t_holder *holder, char **path)
{
	if (is_dir(holder->args[0]))
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(holder->args[0], 2);
		ft_putstr_fd(" is a directory\n", 2);
		exit(126);
	}
	if (!access(holder->args[0], X_OK))
	{
		*path = holder->args[0];
	}
	else if (!access(holder->args[0], F_OK))
	{
		if (access(holder->args[0], X_OK))
		{
			ft_putstr_fd("bash ", 2);
			ft_putstr_fd(holder->args[0], 2);
			ft_putstr_fd(" Permission denied\n", 2);
			exit(126);
		}
	}
	else
		no_such_file_or_dir_error(holder->args[0]);
}

void	cmd_null_path(char *path, t_holder *holder)
{
	if (!path)
	{
		ft_putstr_fd("bash ", 2);
		ft_putstr_fd(holder->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
}

void	init_vars_cmd(t_execution *vars)
{
	vars->i--;
	vars->k--;
	vars->j--;
}
