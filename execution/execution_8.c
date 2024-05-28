/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_8.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 03:51:14 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/28 03:57:36 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void closing_files(t_execution *vars)
{
	while(vars->tmp->out[vars->j] && vars->tmp->out[vars->j] != -42 
	&& vars->tmp->out[vars->j] != -1)
	{
		close(vars->tmp->out[vars->j]);
		vars->j++;
	}
	while(vars->tmp->in[vars->i] && vars->tmp->in[vars->i] != -42 
	&& vars->tmp->in[vars->i] != -1)
	{
		close(vars->tmp->in[vars->i]);
		vars->i++;
	}
	while(vars->tmp->ap[vars->k] && vars->tmp->ap[vars->k] != -42 
	&& vars->tmp->ap[vars->k] != -1)
	{
		close(vars->tmp->ap[vars->k]);
		vars->k++;
	}
}
int    execution_cmd(t_execution *vars, t_env *env, t_last *status)
{
    if (vars->tmp->in[vars->i] != -42 && vars->tmp->in[vars->i] != -1)
        vars->i++;
    if (vars->tmp->out[vars->j] != -42 && vars->tmp->out[vars->j] != -1)
        vars->j++;
    if (vars->tmp->ap[vars->k] != -42 && vars->tmp->ap[vars->k] != -1)
        vars->k++;
    vars->pid = fork();
    if (vars->pid == -1)
        return (0) ;
    if (!vars->pid)
        exec_cmd(vars->tmp, env, vars->pipe_fd,vars);
	exec_cmd_vars_init(vars);
	closing_files(vars);
    return (1);
}

void initial_vars(t_execution *vars, t_holder **holder)
{
	(vars->i = 0, vars->j = 0, vars->k = 0, vars->n = 0, vars->wait_i = 0);
	vars->tmp = *holder;
	vars->origin_in = dup(STDIN_FILENO);
	vars->origin_out = dup(STDOUT_FILENO);
}

void piping(t_execution *vars)
{
	close (vars->pipe_fd[1]);
	dup2 (vars->pipe_fd[0], STDIN_FILENO);
	close(vars->pipe_fd[0]); 
}
void cleaning_execution(t_execution *vars, t_holder **holder)
{
	dup2(vars->origin_in, STDIN_FILENO);
	close(vars->origin_in);
    close(vars->origin_out);
	if (vars->pipe_fd[0])
		close(vars->pipe_fd[0]);
	close(vars->pipe_fd[1]);
	ft_free_holder(holder);	
}
