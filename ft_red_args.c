/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:28:57 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/03 17:32:52 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_red_args(t_line *head)
{
   t_line *tmp;
   t_line *tmp1;
   int  i, flag;

    tmp = head;
    while (tmp)
    {
        if (tmp->token == CMD)
            flag = 1;
        if (tmp->token == IN_REDIR || tmp->token == OUT_REDIR || tmp->token == APPEND)
        {
            tmp1 = tmp;
            if (tmp1->next->next)
                tmp1 = tmp1->next->next;
            else
                return ;
            while (tmp1 && tmp1->token == CMD)
            {
                if (tmp1 && tmp1->token == CMD && flag == 1)
                    tmp1->token = ARGS;
                tmp1 = tmp1->next;
            }
            flag = 0;
        }
        tmp = tmp->next;
    }
}