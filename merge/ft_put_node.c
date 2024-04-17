/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:00:05 by ybellakr          #+#    #+#             */
/*   Updated: 2024/04/17 18:12:03 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_substr(char *str, int start, int len)
{
	char	*sub;
	int		i;

	i = 0;
    // if (str == NULL || start < 0 || len < 0)
    //     return NULL;
    int str_len = ft_strlen(str);
    // if (start >= str_len)
    //     return NULL;
    if (start + len > str_len)
        len = str_len - start;
    sub = (char *)malloc((len + 1) * sizeof(char));
    // if (sub == NULL)
    //     return (NULL);
	while (i < len)
		sub[i++] = str[start++];
    sub[len] = '\0';
    return (sub);
}

t_line	*ft_lstnew(char *str, int start, int end)
{
	t_line	*new;

	new = (t_line *)malloc(sizeof(t_line));
	if (!new)
		return (NULL);
    new->str = ft_substr(str, start, end - start);
	if (new->str == NULL)
	new->next = NULL;
	return (new);
}

void	add_list(t_line **lst, char *str, int start, int end)
{
	t_line	*new = NULL;
	t_line	*temp = NULL;

	new = ft_lstnew(str, start, end);
	if (!new)
		(*lst)->status->status = 255;
	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
	}
	else
	{
        if (*lst)
		    temp = *lst;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
}

static int		ft_strchr1(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_put(char *str, t_line **head)
{
	int        flag;
	int			i;
	int			j;
	t_status	*status;

    (1) && (i = 0, j = 0, flag = 0);
	// status = malloc(sizeof(t_status));
	// (*head)->status = status;
    while (str && str[i])
    {
        while (str[i] && ft_strchr1(" \t\n\v\f\r", str[i]))
            i++;
        j = i;
        while (str[i] && !ft_strchr1(" \t\n\v\f\r", str[i]))
        {
            if (str[i] && (str[i] == '\"' || str[i] == '\''))
            {
                flag = str[i++];
                while (str[i] && str[i] != flag)
                    i++;
                if (str[i] == flag)
                    flag = 0;
            }
            i++;
        }
        add_list(head, str, j, i);
        if (!str[i])
            break ;
    }
}