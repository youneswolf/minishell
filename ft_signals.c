/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:42:21 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/14 22:37:23 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_putstr(char *str)
{
    int i;

    while (str && str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
}

void    ft_ctr_c(int sig)
{
    write(1, "\n", 1);
    printf(RED"minishell$ "RESET);
    // write(1, "\n", 1);
    // ft_putstr("\nminishell$ ");
    signal(SIGINT, ft_ctr_c);
    fflush(stdout);
}