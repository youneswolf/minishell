/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 01:51:11 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/28 01:55:50 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_line *ft_lst_new(char *str)
{
	t_line *line;
	
	line = malloc(sizeof(t_line));
	if (!line)
		return (NULL);
	line->str = str;
	line->next = NULL;
	return (line);
}

int	if_dollar(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && str[i + 1])
			return (1);
		i++;
	}
	return (0);
}

int is_char(char *str)
{
	int i = 0;
	while (str && str[i])
	{
		if (ft_isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void    ft_free_list3(t_line **str)
{
	t_line *to_be_free;
	t_line	*prev;
	to_be_free = *str;
	while (to_be_free)
	{
		prev = to_be_free;
		to_be_free = to_be_free->next;
		free(prev->str);
		free(prev);
	}
}

void    ft_free_list2(t_line **str)
{
	t_line *to_be_free;
	t_line	*prev;
	to_be_free = *str;
	while (to_be_free)
	{
		prev = to_be_free;
		to_be_free = to_be_free->next;
		free(prev->str);
		free(prev);
	}
}
