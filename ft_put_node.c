/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:00:05 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/14 22:53:36 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_alloc_string(char *str, int i)
{
    int     j, k, flag = 0, flag1 = 0;
    char    *new = NULL;

    j = i;
    k = 0;
    while (str && str[i] != '\0' && str[i] != ' ')
    {
		if (str[i] && (str[i] == '\'' || str[i] == '\"'))
		{
			flag = str[i];
			i++;
			k++;
			break;
		}
        if (str[i])
            i++;
        k++;
    }
	if (flag != 0)
	{
		while (str && str[i] && str[i] != flag)
		{
			i++;
			k++;
		}
		if (str[i])
		{
			i++;
			k++;
		}
		if (str[i] == '\'' || str[i] == '\"' || str[i])
		{
			flag = str[i];
			while (str[i] && str[i] != ' ')
			{
				i++;
				k++;
			}
		}
	}
	if (str[i] == flag)
		k++;
    new = malloc((k + 1) * sizeof(char));
    if (!new)
        return (NULL);
    i = 0;
	while (str && str[j] != '\0' && str[j] != ' ')
	{
		if (str[j] == '\"' || str[j] == '\'')
		{
			flag = str[j];
			new[i] = flag;
			if (str[j] && new[i])
				(j++, i++);
			break;
		}
		new[i] = str[j];
		i++;
		j++;
	}
	if (flag)
	{
		while (str && str[j] != '\0' && str[j] != flag)
		{
			new[i] = str[j];
			i++;
			j++;
		}
		if (str && str[j] && str[j] == flag)
		{
			while (str && str[j] != '\0' && str[j] != ' ')
			{
				new[i] = str[j];
				i++;
				j++;
			}
		}
	}
    if (new == NULL)
	    return(NULL);
	else
	    new[i] = '\0';
    return (new);
}

int	ft_strlen1(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

t_line	*ft_lstnew(char *str, int i, char flag)
{
	t_line	*new;

	new = (t_line *)malloc(sizeof(t_line));
	if (!new)
		return (NULL);
    new->str = ft_alloc_string(str, i);
	new->next = NULL;
	return (new);
}

void	add_list(t_line **lst, char *str, char flag, int i)
{
	t_line	*new = NULL;
	t_line	*temp = NULL;

	new = ft_lstnew(str, i, flag);
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

t_line	*ft_put(char *str)
{
    int i = 0;
	char *str1 = NULL;
    t_line  *head = NULL;

	while (str[i])
	{
        while (str[i] && str[i] == ' ')
			i++;
		str1 = ft_alloc_string(str, i);
        add_list(&head, str, ' ', i);
		i += ft_strlen1(str1);
		if (str[i])
			i++;
	}
    return (head);
}
