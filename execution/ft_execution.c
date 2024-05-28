/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:50:26 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/28 06:00:52 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	command_first_exec(t_execution *vars, t_env *env, t_last *status)
{
	if (!execution_cmd(vars, env, status))
	{
		ft_putstr_fd("minishell: fork: Resource \
		temporarily unavailable\n", 2);
		return (0);
	}
	return (1);
}

void	after_exec(t_holder **holder, t_execution *vars, t_last *status)
{
	status->status = ft_status(0, 1);
	waitpid(vars->pid, &status->status, 0);
	if (WIFEXITED(status->status))
	{
		status->status = WEXITSTATUS(status->status);
		ft_status(1, status->status);
	}
	else if (WIFSIGNALED(status->status) && (WTERMSIG(status->status) == SIGINT 
			|| WTERMSIG(status->status) == SIGQUIT))
	{
		if (WTERMSIG(status->status) == SIGQUIT)
		{
			printf("Quit: 3\n");
			ft_status(1, 131);
		}
		if (WTERMSIG(status->status) == SIGINT)
		{
			ft_status(1, 130);
		}
	}
	while (waitpid(-1, 0, 0) != -1)
		;
	cleaning_execution(vars, holder);
}

void	execution(t_holder **holder, t_env *env, t_last *status)
{
	t_execution	vars;

	initial_vars(&vars, holder);
	while (vars.tmp)
	{
		status->status = ft_status(0, 1);
		pipe(vars.pipe_fd);
		if (vars.tmp->her_doc[vars.n])
		{
			(close(vars.pipe_fd[0]), close(vars.pipe_fd[1]));
			if (here_doc_exec(&vars, env) == 500)
				break ;
		}
		if ((vars.tmp->cmd_built_in && vars.tmp->file_out[vars.j]) 
			|| vars.tmp->cmd_built_in)
			built_in_exec(&vars, env);
		if ((vars.tmp && vars.tmp->cmd))
		{
			if (!command_first_exec(&vars, env, status))
				break ;
		}
		piping(&vars);
		vars.tmp = vars.tmp->next;
	}
	after_exec(holder, &vars, status);
}
