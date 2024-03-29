/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checking_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:06:44 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/28 19:43:27 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/fcntl.h>

void    ft_checking_files(t_holder *node)
{
    t_holder    *tmp;
    int         i, j, k;

    tmp = node;
    i = 0;
    j = 0;
    k = 0;
    while (tmp)
    {
        if (tmp->her_doc[k])
        {
            tmp->ap[k] = open(tmp->her_doc[k], O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (tmp->ap[k] == -1)
                write(2, "error in oppening the file\n", 26);
            k++;
        }
        tmp = tmp->next;
    }
}