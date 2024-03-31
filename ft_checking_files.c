/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checking_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:06:44 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/30 18:34:37 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void    ft_checking_files(t_holder *node)
// {
// 	t_holder    *tmp;
// 	int         i, j, k, check;


// 	tmp = node;
// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	while (tmp)
// 	{
// 		check  = 0;
// 		if (tmp->file_in[i])
// 		{
// 			tmp->in[i] = open(tmp->file_in[i], O_RDONLY);
// 			if (tmp->in[i] == -1)
// 			{
// 				// ft_putstr_fd(2, in[i]);
// 				write(2, "such file or directory\n", 24);
// 				check  = -42;
// 			}
// 			i++;
// 		}
// 		if (tmp->file_out[j])
// 		{
// 			if (check != -42)
// 			{
// 				tmp->out[j] = open(tmp->file_out[j], O_CREAT| O_RDWR, 0644);
// 				if (tmp->out[j] == -1)
// 					write(2, "such file or directory\n", 26);
// 				j++;
// 			}
// 		}
// 		else if (tmp->append[k])
// 		{
// 			tmp->ap[k] = open(tmp->append[k], O_CREAT| O_RDWR | O_APPEND, 0644);
// 			if (tmp->ap[k] == -1)
// 				write(2, "such file or directory\n", 26);
// 			k++;
// 		}
// 		tmp = tmp->next;
// 	}
// }

void    ft_checking_files(t_holder *node)
{
    t_holder    *tmp;
    int         i, j, k, check, b, n, z;


    tmp = node;
    i = 0;
    j = 0;
    b = 0;
    k = 0;
    n = 0;
    z = 0;
    while (tmp)
    {
        check  = 0;
        while (tmp->file_in[b])
        {
            if (tmp->file_in[i])
            {
                tmp->in[i] = open(tmp->file_in[i], O_RDONLY);
                if (tmp->in[i] == -1)
                {
                    // ft_putstr_fd(2, in[i]);
                    write(2, "such file or directory\n", 24);
                    check  = -42;
                }
                i++;
            }
            b++;
        }
        while (tmp->file_out[n])
        {
            if (tmp->file_out[j])
            {
                if (check != -42)
                {
                    tmp->out[j] = open(tmp->file_out[j], O_CREAT| O_RDWR, 0644);
                    if (tmp->out[j] == -1)
                        write(2, "such file or directory\n", 26);
                    j++;
                }
            }
            n++;
        }
        while (tmp->append[z])
        {
            if (tmp->append[k])
            {
                tmp->ap[k] = open(tmp->append[k], O_CREAT| O_RDWR | O_APPEND, 0644);
                if (tmp->ap[k] == -1)
                    write(2, "such file or directory\n", 26);
                k++;
            }
            z++;
        }
        tmp = tmp->next;
    }
}