/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 03:51:45 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/28 05:04:08 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_piping(int pipe_fd[2])
{
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	redirection_cmd(t_holder *holder, t_execution *vars, int pipe_fd[2])
{
	init_vars_cmd(vars);
	if (vars->i >= 0 && vars->i < 1024 && holder->in[vars->i] != -42
		&& holder->in[vars->i] != -1)
	{
		while (holder->in[vars->i] != -42)
			vars->i++;
		redirect_input(holder->in[vars->i -1]);
	}
	if (vars->j >= 0 && vars->j < 1024 && holder->out[vars->j] != -42
		&& holder->out[vars->j] != -1)
	{
		while (holder->out[vars->j] != -42)
			vars->j++;
		redirect_output(holder->out[vars->j -1]);
	}
	if (vars->k >= 0 && vars->k < 1024 && holder->ap[vars->k] != -42
		&& holder->ap[vars->k] != -1)
	{
		while (holder->ap[vars->k] != -42)
			vars->k++;
		redirect_append(holder->ap[vars->k -1]);
	}
	else if (holder->next)
		cmd_piping(pipe_fd);
}

void	exec_cmd(t_holder *holder, t_env *env,
	int pipe_fd[2], t_execution *vars)
{
	char	*path;
	char	**array;

	path = NULL;
	array = NULL;
	redirection_cmd(holder, vars, pipe_fd);
	if (is_slash(holder->args[0]))
		cmd_file_stat(holder, &path);
	else
		path = get_path(env, holder->args[0]);
	cmd_null_path(path, holder);
	array = ft_put_env_string(array, env);
	execve(path, holder->args, array);
	ft_free_2d(array);
	exit(1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		res;

	res = 0;
	i = 0;
	while (i < n)
	{
		if (s1 && s1[i] == '\0' && s2[i] == '\0')
		{
			return (0);
		}
		if (s1 && s2 && (unsigned char)s1[i] != (unsigned char)s2[i])
		{
			res = (unsigned char)s1[i] - (unsigned char)s2[i];
			return (res);
		}
		i++;
	}
	return (res);
}

int	ft_strcmp_asd(char *s1, char *s2)
{
	size_t	i;
	int		res;

	res = 0;
	i = 0;
	while (s1 && s1[i])
	{
		if (s1 && s1[i] == '\0' && s2[i] == '\0')
		{
			return (0);
		}
		if (s1 && s2 && (unsigned char)s1[i] != (unsigned char)s2[i])
		{
			res = (unsigned char)s1[i] - (unsigned char)s2[i];
			return (res);
		}
		i++;
	}
	return (res);
}
