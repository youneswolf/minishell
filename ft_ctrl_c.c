/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 21:08:37 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/08 09:56:55 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_f(int signum)
{
    (void) signum;
    return;
}

void    ft_handler_ctrl_c(int signum)
{
    if (signum == SIGINT)
    {
        if (waitpid(-1, NULL, WNOHANG) == 0)
            return ;
        printf("\n");
        // rl_replace_line("", 1);
        rl_on_new_line();
        rl_redisplay();
    }
    else if (signum == SIGQUIT)
    {
        if (waitpid(-1, NULL, WNOHANG) == 0)
        {
            if (tcsetattr(STDIN_FILENO, TCSANOW, &attr) == -1)
                perror("tcsetattr");
            printf("\n");
            return ;
        }
        rl_redisplay();
    }
}
