/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 03:50:51 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/29 11:07:58 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_built_fcts(t_execution *vars, t_env *env, t_holder *holder)
{
	(1) && (vars->i = 0, vars->j = 0, vars->k = 0);
	closing_files(vars);
	check_which_built_in(vars, env, holder);
	dup2(vars->origin_out, STDOUT_FILENO);
}

int	here_doc_exec(t_execution *vars, t_env *env)
{
	while (vars->tmp->her_doc[vars->n])
	{
		dup2(vars->origin_in, STDIN_FILENO);
		pipe(vars->pipe_fd);
		vars->pid = fork();
		if (!vars->pid)
			here_doc_child(vars, env);
		else
		{
			waitpid(vars->pid, &vars->child_stat, 0);
			if (WIFSIGNALED(vars->child_stat) 
				&& WTERMSIG(vars->child_stat) == SIGINT)
				break ;
			if (WIFEXITED(vars->child_stat))
			{
				if (check_if_ctrl_c(vars) == 100)
					return (500);
				if (check_if_ctrl_c(vars) == 1)
					return (1);
			}
			exec_dups_here(vars);
		}
		vars->n++;
	}
	return (0);
}

void	check_which_built_in(t_execution *vars, t_env *env, t_holder *holder)
{
	vars->exit = count_nodes(holder);
	if (vars->tmp->next)
		dup2(vars->pipe_fd[1], STDOUT_FILENO);
	if (!ft_strcmp_asd(vars->tmp->args_built_in[0], "export"))
		exec_export(&vars->tmp, &env);
	else if (!ft_strcmp_asd(vars->tmp->args_built_in[0], "echo"))
		exec_echo(vars->tmp);
	else if (!ft_strcmp_asd(vars->tmp->args_built_in[0], "unset"))
		exec_unset(&env, vars->tmp);
	else if (!ft_strcmp_asd(vars->tmp->args_built_in[0], "env"))
		exec_env(&env, holder);
	else if (!ft_strcmp_asd(vars->tmp->args_built_in[0], "exit")
		&& vars->exit == 1)
		ft_exit(vars->tmp, vars->exit);
	else if (!ft_strcmp_asd(vars->tmp->args_built_in[0], "exit")
		&& vars->exit > 1)
		ft_exit2(vars->tmp, vars->exit);
	else if (!ft_strcmp_asd(vars->tmp->args_built_in[0], "pwd"))
		ft_pwd(env);
	else if (!ft_strcmp_asd(vars->tmp->args_built_in[0], "cd"))
		if (vars->tmp->args_built_in[1])
			ft_cd(vars->tmp->args_built_in[1], &env);
}

void	built_in_exec(t_execution *vars, t_env *env, t_holder *holder)
{
	(1) && (vars->i = 0, vars->j = 0, vars->k = 0);
	if (vars->tmp->in[vars->i] != -42 && vars->tmp->in[vars->i] != -1)
		vars->i++;
	if (vars->tmp->out[vars->j] != -42 && vars->tmp->out[vars->j] != -1)
		vars->j++;
	if (vars->tmp->ap[vars->k] != -42 && vars->tmp->ap[vars->k] != -1)
		vars->k++;
	else if (vars->j != 0 && vars->tmp->out[vars->j -1] >= 0 
		&& vars->tmp->in[vars->j -1] < 1024 
		&& vars->tmp->out[vars->j -1] != -42 
		&& vars->tmp->out[vars->j -1] != -1)
	{
		while (vars->tmp->out[vars->j -1] != -42)
			vars->j++;
		redirect_output(vars->tmp->out[vars->j -2]);
	}
	else if (vars->k != 0 && vars->tmp->ap[vars->k -1] >= 0
		&& vars->tmp->in[vars->k -1] < 1024 && vars->tmp->ap[vars->k -1] != -42 
		&& vars->tmp->ap[vars->k -1] != -1)
	{
		while (vars->k != 0 && vars->tmp->ap[vars->k -1] != -42)
			vars->k++;
		redirect_append(vars->tmp->ap[vars->k -2]);
	}
	exec_built_fcts(vars, env, holder);
}

void	exec_cmd_vars_init(t_execution *vars)
{
	vars->j = 0;
	vars->i = 0;
	vars->k = 0;
}
