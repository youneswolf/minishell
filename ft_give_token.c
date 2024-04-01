/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_give_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:02:53 by ybellakr          #+#    #+#             */
/*   Updated: 2024/04/01 00:33:15 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_strcmp(char *str, char *str1)
{
    int i;

    i = 0;
    while (str && str1 && (str[i] || str1[i]))
    {
        if (str[i] != str1[i])
            return (0);
        i++;
    }
    return (1);
}

void    ft_give_token(t_line *head)
{
    t_line  *tmp;

    tmp = head;
    int flag1;

    flag1 = 0;
    while (tmp)
    {
        if (ft_strcmp(tmp->str, "|"))
            (tmp->token = PIPE, flag1 = 0);
        else if (ft_strcmp(tmp->str, ">"))
        {
            tmp->token = OUT_REDIR;
            if (tmp->next != NULL)
                tmp->next->token = OUT_FILE;
        }
        else if (ft_strcmp(tmp->str, "<"))
        {
            tmp->token = IN_REDIR;
            if (tmp->next != NULL)
                tmp->next->token = IN_FILE;
        }
        else if (ft_strcmp(tmp->str, ">>"))
        {
            tmp->token = APPEND;
            if (tmp->next != NULL)
                tmp->next->token = FILE;
        }
        else if (ft_strcmp(tmp->str, "<<"))
        {
            flag1 = 0;
            tmp->token = HERDOC;
            if (tmp->next != NULL)
                tmp->next->token = DELIMITER;
        }
        else
        {
            if (tmp->token == ARGS || tmp->token == FILE || tmp->token == DELIMITER 
            || tmp->token == IN_FILE || tmp->token == OUT_FILE)
            {
                if ((tmp->token == IN_FILE || tmp->token == OUT_FILE ) && tmp->next && flag1 == 1)
                {
                    tmp->next->token = ARGS;
                    // flag1 = 0;
                }
                if (tmp->next && tmp->token != ARGS && tmp->next->token != ARGS)
                {
                    tmp->next->token = CMD;
                    if (ft_cmp_built_in(tmp->next->str))
                        tmp->next->is_it_built_in = 1;
                    else
                        tmp->next->is_it_built_in = 0;
                }
                else if (tmp->next && tmp->token == ARGS)
                    tmp->next->token = ARGS;
            }
            else
            {
                flag1 = 1;
                tmp->token = CMD;
                 if (ft_cmp_built_in(tmp->str))
                        tmp->is_it_built_in = 1;
                else
                    tmp->is_it_built_in = 0;
                if (tmp->next != NULL)
                    tmp->next->token = ARGS;
            }
        }
        tmp = tmp->next;
    }
}
