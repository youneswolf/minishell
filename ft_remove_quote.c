/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:36:17 by ybellakr          #+#    #+#             */
/*   Updated: 2024/04/08 19:50:21 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_remove_utils(t_line *tmp)
{
    int count;
    int flag;
    int i;

    count = ft_strlen(tmp->str) + 1;
    i = 0;
    while (tmp && tmp->str[i])
    {
        tmp->quote = 0;
        if (tmp->str[i] == '\"' || tmp->str[i] == '\'')
        {
            (1) && (flag = tmp->str[i], i++);
            tmp->quote = 1;
            while (tmp->str[i])
            {
                if (tmp->str[i] == flag)
                {
                    (1) && (count -= 2, flag = 0);
                    break;
                }
                i++;
            }
        }
        if(tmp->str[i])
            i++;
    }
    return (count);
}

char    *ft_remove_utils2(t_line *tmp, char *str, int j, int i)
{
    int flag;

    while (tmp && tmp->str[i] && tmp->str)
    {
        if (tmp->str[i] != '\'' && tmp->str[i] != '\"')
            (1) && (str[j] = tmp->str[i] , j++);
        else if (tmp->str[i] == '\"' || tmp->str[i] == '\'')
        {
            (1) && (flag = tmp->str[i], i++);
            while (tmp->str[i])
            {
                if (tmp->str[i] == flag)
                {
                    flag = 0;
                    break;
                }
                else if (tmp->str[i] != flag && tmp->str[i])
                    (1) && (str[j] = tmp->str[i], j++);
                i++;
            }
        }
        if (tmp->str[i])
            i++;
    }
    return (str[j] = '\0', free(tmp->str), str);
}

char    *ft_remove(t_line *tmp, char *line)
{
    int     j;
    int     count;
    char    *str = NULL;
    int     i;

    j = 0;
    i = 0;
    count = ft_remove_utils(tmp);
    if (count > 0)
        str = malloc(count + 1 * sizeof(char));
    if (!str)
        return (NULL);
        // return (free(str), ft_free_list(tmp), "");
    str = ft_remove_utils2(tmp, str, j, i);
    return (str);
}

void    ft_remove_quote(t_line **str, char *line)
{
    t_line  *tmp;
    int     i;

    tmp = *str;
    i = 0;
    while (tmp)
    {
        if (tmp && (tmp->token == CMD || tmp->token == ARGS))
        {
            // if (tmp->token == DELIMITER)
            //     tmp->delimiter_quote = 1;
            // free(tmp->str);
            tmp->str = ft_remove(tmp, line);
        }
        tmp = tmp->next;
    }
}