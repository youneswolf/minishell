/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 21:08:37 by ybellakr          #+#    #+#             */
/*   Updated: 2024/04/16 19:31:12 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_handler_ctrl_c(int signum)
{

    if (signum == SIGINT)
    {
        if (waitpid(-1, NULL, WNOHANG) == 0)
        {
            printf("\n");
            return;
        }
        printf("\n");
        rl_replace_line("", 1);
        rl_on_new_line();
        rl_redisplay();
    }
    if (signum == SIGQUIT)
    {
        if (waitpid(-1, NULL, WNOHANG) == 0)
        {
            printf("\n");
            return;
        }
    }
}

// void    ft_handler_ctrt_herdoc(int signum)
// {

//     if (signum == SIGINT)
//     {
//         if (waitpid(-1, NULL, WNOHANG) == 0)
//         {
//             write(1, "\n",)
//             return;
//         }
//         printf("\n");
//         rl_replace_line("", 1);
//         rl_on_new_line();
//         rl_redisplay();
//         return ;
//     }
// }