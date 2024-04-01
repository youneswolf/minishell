/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:57:13 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/30 02:35:39 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_2d(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void    ft_free_list(t_line *str)
{
	t_line *to_be_free;
	t_line *next;

	to_be_free = str;
	while (to_be_free)
	{
		if (to_be_free->next)
			next = to_be_free->next;
		free(to_be_free->str);
		free(to_be_free);
		to_be_free = next;
	}
	free(to_be_free);
}