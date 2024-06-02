/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_holder2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:42:04 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/29 18:00:36 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_pipe(t_line *head)
{
	int		i;
	t_line	*tmp;

	i = 0;
	tmp = head;
	while (tmp)
	{
		if (tmp->token == PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	ft_count_word(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] >= 33 && str[i] <= 126 && (str[i + 1] == ' '
				|| str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

int	ft_count_2d(char **a)
{
	int	i;

	i = 0;
	while (a && a[i])
		i++;
	return (i);
}

int	ft_create_holder_utils(t_holder *new_, t_line *tmp, int *flag, int *j)
{
	int		zz;
	int		mm;
	char	**array;

	zz = 0;
	mm = 0;
	if (new_ && tmp->flag == 1 && tmp->is_between_quote != 1)
	{
		zz = ft_count_word(tmp->str);
		if (zz >= 1)
		{
			array = ft_split1(tmp->str, ' ');
			if (array)
				new_->cmd = ft_strdup(array[0]);
			while (array && array[mm])
			{
				new_->args[*j] = ft_strdup(array[mm]);
				(1) && (mm++, *j = *j + 1);
			}
			ft_free_2d(array);
		}
		*flag = 0;
		return (1);
	}
	return (0);
}

void	ft_create_holder_utils1(t_holder *new_, t_line *tmp, int *j, int *flag)
{
	int		qq;
	char	**a;
	int		ee;

	if (new_ && ft_is_there(tmp->str))
	{
		a = ft_does_it_matche(tmp->str);
		qq = ft_count_2d(a);
		ee = 0;
		if (qq >= 1)
		{
			if (a)
				new_->cmd = ft_strdup(a[0]);
			while (a && a[ee])
				(1) && (new_->args[(*j)++] = ft_strdup(a[ee]), ee++);
		}
		ft_free_2d(a);
	}
	else if (new_)
	{
		new_->cmd = ft_strdup(tmp->str);
		new_->args[(*j)++] = ft_strdup(tmp->str);
	}
	*flag = 0;
}
