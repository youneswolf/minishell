/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checking_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:06:44 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/14 17:42:28 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
        if (tmp->file_in[i])
        {
            tmp->in[i] = open(tmp->file_in[i], O_RDONLY);
            if (tmp->in[i] == -1)
                write(2, "No such file or directory\n", 26);
            i++;
        }
        else if (tmp->file_out[j])
        {
            tmp->out[j] = open(tmp->file_out[j], O_RDONLY);
            if (tmp->out[j] == -1)
                write(2, "No such file or directory\n", 26);
            j++;
        }
        else if (tmp->append[k])
        {
            tmp->ap[k] = open(tmp->append[k], O_RDONLY);
            if (tmp->ap[k] == -1)
                write(2, "No such file or directory\n", 26);
            k++;
        }
        tmp = tmp->next;
    }
}