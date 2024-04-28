/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:00:05 by ybellakr          #+#    #+#             */
/*   Updated: 2024/04/28 13:32:07 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_substr1(char *str, int start, int len, int not_)
{
	char	*sub;
	int		i;
	int		str_len;

	i = 0;
    str_len = ft_strlen(str);
    if (start + len > str_len)
        len = str_len - start;
    sub = (char *)malloc((len + 1) * sizeof(char));
	while (i < len)
		sub[i++] = str[start++];
    sub[len] = '\0';
	if (not_ == 1)
		free(str);
    return (sub);
}

char *ft_substr(char *str, int start, int len)
{
	char	*sub;
	int		i;
	int str_len;

	i = 0;
    str_len = ft_strlen(str);
    if (start + len > str_len)
        len = str_len - start;
    sub = (char *)malloc((len + 1) * sizeof(char));
	while (i < len)
		sub[i++] = str[start++];
    sub[len] = '\0';
    return (sub);
}

t_line	*ft_lstnew(char *str, int start, int end)
{
	t_line	*new;

	new = (t_line *)malloc(sizeof(t_line));
	new->status = (t_status *)malloc(sizeof(t_status));
	new->status->index = 0;
	new->status->lastdir = NULL;
	new->deja = 0;
	new->token = NONE;
	if (!new)
		return (NULL);
    new->str = ft_substr1(str, start, end - start, 0);
	if (new->str == NULL)
		exit(0);
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
		while (temp && temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

int		ft_strchr1(char *str, char c)
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

int	ft_put_utils(char *str, int j, int i, t_line **head)
{
	if (i == j)
		return (0);
	add_list(head, str, j, i);
	if (!str[i])
		return (0);
	return (1);
}

void	ft_put(char *str, t_line **head)
{
	int        flag;
	int			i;
	int			j;

    (1) && (i = 0, j = 0, flag = 0);
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
				if (str[i] == '\0')
					break;
                if (str[i] == flag)
                    flag = 0;
            }
			i++;
        }
		if (!ft_put_utils(str, j, i, head))
			break;
    }
}
