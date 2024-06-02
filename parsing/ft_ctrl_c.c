/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 21:08:37 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/28 15:41:51 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_f(int signum)
{
	(void) signum;
	return ;
}

void	ft_heredoc(int signum)
{
	(void)signum;
	ft_status(1, 1);
	close (STDIN_FILENO);
	exit (100);
}

void	ft_handler_ctrl_c(int signum)
{
	if (signum == SIGINT)
	{
		if (waitpid(-1, NULL, WNOHANG) == 0)
			return ;
		printf("\n");
		ft_status(1, 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		if (waitpid(-1, NULL, WNOHANG) == 0)
		{
			if (isatty(STDIN_FILENO) == 0)
				open("dev/tty", O_CREAT | O_RDONLY);
			ft_status(1, 0);
			return ;
		}
		rl_redisplay();
	}
}
