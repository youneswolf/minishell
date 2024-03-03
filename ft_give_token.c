/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_give_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:02:53 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/03 13:22:20 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_strcmp(char *str, char *str1)
{
    int i;

    i = 0;
    while (str[i] || str1[i])
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
    while (tmp)
    {
        if (ft_strcmp(tmp->str, "|"))
            tmp->token = PIPE;
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
            tmp->token = HERDOC;
            if (tmp->next != NULL)
                tmp->next->token = DELIMITER;
        }
        else
        {
            if (tmp->token == ARGS || tmp->token == FILE || tmp->token == DELIMITER 
            || tmp->token == IN_FILE || tmp->token == OUT_FILE)
            {
                if (tmp->next && tmp->token != ARGS)
                    tmp->next->token = CMD;
                else if (tmp->next && tmp->token == ARGS)
                    tmp->next->token = ARGS;
            }
            else
            {
                tmp->token = CMD;
                if (tmp->next != NULL)
                    tmp->next->token = ARGS;
            }
        }
        tmp = tmp->next;
    }
}
