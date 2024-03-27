/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:39:00 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/14 22:36:21 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_pwd()
{
    char    buf[1024];
    if (getcwd(buf, sizeof(buf)) != NULL)
        printf("Current working directory:%s\n", buf);
    else
    {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }
}