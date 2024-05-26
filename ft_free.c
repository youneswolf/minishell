/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:57:13 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/26 10:22:39 by ybellakr         ###   ########.fr       */
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

void	ft_free_list(t_line **str, t_status *status)
{
	t_line	*to_be_freed;

	while (*str)
	{
		to_be_freed = *str;
		*str = (*str)->next;
		if (to_be_freed->str)
			free(to_be_freed->str);
		free(to_be_freed->status1);
		free(to_be_freed);
	}
	free(status);
	status = NULL;
}

void	ft_free_holder_utils(t_holder *prev)
{
	free(prev->args);
	free(prev->file_in);
	free(prev->file_out);
	free(prev->append);
	free(prev->her_doc);
	free(prev->args_built_in);
	free(prev->cmd);
	free(prev->infile_index);
	free(prev->outfile_index);
	free(prev->append_index);
	free(prev->in);
	free(prev->out);
	free(prev->ap);
	free(prev->cmd_built_in);
	free(prev);
}

void	ft_free_holder(t_holder **str)
{
	t_holder	*to_be_free;
	t_holder	*prev;
	int			i;

	to_be_free = *str;
	while (to_be_free)
	{
		i = 0;
		prev = to_be_free;
		to_be_free = to_be_free->next;
		while (i < 1000)
		{
			free(prev->args[i]);
			if (prev->file_in)
				free(prev->file_in[i]);
			if (prev->file_out)
				free(prev->file_out[i]);
			if (prev->append)
				free(prev->append[i]);
			free(prev->her_doc[i]);
			free(prev->args_built_in[i]);
			i++;
		}
		ft_free_holder_utils(prev);
	}
}
