/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:42:54 by ybellakr          #+#    #+#             */
/*   Updated: 2024/06/02 13:43:41 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	int_len(int n)
{
	int		i;
	long	num;

	num = n;
	i = 0;
	if (num < 0)
	{
		num *= -1;
		i++;
	}
	while (num > 0)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

int	is_between_quotes(char *str)
{
	int	i;

	i = 0;
	if (str && str[0] == 34 && str[1] && str[1] != 34)
	{
		while (str && str[i])
			i++;
		if (str[i - 1] == 34)
			return (1);
	}
	return (0);
}

int	ft_status(int a, int status)
{
	static int	s;

	if (a == 1)
		s = status;
	return (s);
}

void	ft_skip_empty_expand_utils(t_line *head, t_line *previous, t_line *tmp)
{
	if (head)
	{
		while (head)
		{
			if (head && head->flag == 1 && head->str && head->str[0] == '\0'
				&& head->token != OUT_FILE && head->token != IN_FILE
				&& head->token != APPEND && head->token != DELIMITER)
			{
				while (head && head->flag == 1 && !head->str[0])
				{
					tmp = head;
					head = head->next;
					free(tmp->str);
					free(tmp->status1);
					free(tmp);
				}
				previous->next = head;
			}
			if (head)
			{
				previous = head;
				head = head->next;
			}
		}
	}
}

void	ft_skip_empty_expand(t_line **node)
{
	t_line	*head;
	t_line	*tmp;
	t_line	*previous;

	tmp = NULL;
	if ((*node) && (*node)->token != OUT_FILE && (*node)->token != IN_FILE
		&& (*node)->token != APPEND && (*node)->token != DELIMITER
		&& (*node)->flag == 1 && (*node)->str && !(*node)->str[0])
	{
		(1) && (previous = (*node), (*node) = (*node)->next);
		free(previous->str);
		free(previous->status1);
		free(previous);
		while ((*node) && (*node)->flag == 1 && !(*node)->str[0])
		{
			previous = (*node);
			(*node) = (*node)->next;
			free(previous->str);
			free(previous->status1);
			free(previous);
		}
	}
	head = *node;
	previous = *node;
	ft_skip_empty_expand_utils(head, previous, tmp);
}
