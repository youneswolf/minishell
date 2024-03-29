/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 21:08:37 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/29 22:09:11 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_handler_ctrl_c(int signum)
{
    printf("\n");
    rl_replace_line("", 1);
    rl_on_new_line();
    rl_redisplay();
}
