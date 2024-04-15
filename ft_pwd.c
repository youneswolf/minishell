/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:39:00 by ybellakr          #+#    #+#             */
/*   Updated: 2024/04/15 10:08:30 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_pwd()
{
    char    buf[1024];
    if (getcwd(buf, sizeof(buf)) != NULL)
        printf("Current working directory:%s\n", buf);
    else
        perror("getcwd");
}
