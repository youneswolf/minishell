/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 03:50:32 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/28 15:41:55 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_ctrl_c(t_execution *vars)
{
	int	exit_status;

	exit_status = WEXITSTATUS(vars->child_stat);
	if (exit_status == 100)
	{
		ft_status(1, 1);
		return (write(1, "\n", 1), 100);
	}
	if (exit_status == 255)
	{
		vars->tmp = vars->tmp->next;
		return (1);
	}
	return (0);
}

void	dup2cmd_here(t_execution *vars)
{
	close(vars->pipe_fd[1]);
	if (dup2(vars->pipe_fd[0], STDIN_FILENO) == -1)
		(perror("dup2 doc"));
	close(vars->pipe_fd[0]);
}

void	here_doc_child(t_execution *vars, t_env *env)
{
	signal(SIGINT, ft_heredoc);
	signal(SIGQUIT, &ft_f);
	ft_here_doc(vars->tmp->her_doc[vars->n], vars->pipe_fd, vars->tmp, &env);
}

void	exec_dups_here(t_execution *vars)
{
	if (vars->tmp->cmd)
		dup2cmd_here(vars);
	else
		here_piping(vars);
	ft_status(1, 0);
}
