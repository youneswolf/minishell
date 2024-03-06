/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:00:05 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/06 12:22:41 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_alloc_for_quote(char *str, int i, char flag)
{
    int j, k;
    char    *new;

    j = i;
    k = 0;
    while (str[i] && str[i] != flag)
    {
        i++;
        k++;
    }
    // if (k == 0)
    // {
        
    // }
    new = malloc(k + 3);
    if (!new)
        return (NULL);
    i = 1;
    new[0] = flag;
    while (str[j] != '\0' && str[j] != flag)
    {
        new[i] = str[j];
        i++;
        j++;
    }
    if (str[j] == flag)
        new[i] = flag;
    new[i + 1] = '\0';
    return (new);
}

char    *ft_alloc_string(char *str, int i)
{
    int     j, k;
    char    *new;

    j = i;
    k = 0;
    while (str[i] != '\0' && str[i] != ' ')
    {
        i++;
        k++;
    }
    new = malloc((k + 1) * sizeof(char));
    if (!new)
        return (NULL);
    i = 0;
    while (str[j] != '\0' && str[j] != ' ')
    {
        new[i] = str[j];
        i++;
        j++;
    }
    new[i] = '\0';
    return (new);
}

t_line	*ft_lstnew(char *str, int i, char flag)
{
	t_line	*new;

	new = (t_line *)malloc(sizeof(t_line));
	if (!new)
		return (NULL);
    if (flag == '\"' || flag == '\'')
        new->str = ft_alloc_for_quote(str, i, flag);
    else
        new->str = ft_alloc_string(str, i);
	new->next = NULL;
	return (new);
}

void	add_list(t_line **lst, char *str, char flag, int i)
{
	t_line	*new;
	t_line	*temp;

	new = ft_lstnew(str, i, flag);
	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
	}
	else
	{
		temp = *lst;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
}

t_line    *ft_put(char *line)
{
    int i, j, flag;
    t_line  *head;

    head = NULL;
    i = 0;
    j = 0;
    while (line[i])
    {
        while (line[i] && line[i] == ' ')
            i++;
        if (line[i] == '\0')
            break;
        if (line[i] != '\0' && (line[i] == '\"' || line[i] == '\''))
        {
            flag = line[i];
            i++;
            add_list(&head, line, flag, i);
            while (line[i] && line[i] != flag)
                i++;
        }
        else if (line[i] != '\0' && line[i] != '\"' && line[i] != '\'')
        {
            add_list(&head, line, ' ', i);
            while (line[i] && line[i] != ' ')
                i++;
        }
        if (line[i] == '\0')
            break;
        i++;
    }
    return (head);
}
