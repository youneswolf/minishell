/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:47:58 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/03 15:08:48 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_syntax(t_line *head)
{
    int i;
    int flag;
    t_line  *tmp;
    int count;

    i = 0;
    count = 0;
    tmp = head;
    while (tmp)
    {
        flag = tmp->token;
        if (tmp->next && flag == tmp->next->token && flag != ARGS)
        {
            perror("parse error");
            return ;
        }
        else if ((tmp->token == PIPE || tmp->token == HERDOC || tmp->token == IN_REDIR 
        || tmp->token == OUT_REDIR || tmp->token == APPEND) && !tmp->next)
        {
            perror("parse error");
            return ;
        }
        tmp = tmp->next;
    }
}