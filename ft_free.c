/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:57:13 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/17 15:17:25 by ybellakr         ###   ########.fr       */
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

void    ft_free_list(t_line **str, t_status *status)
{
	t_line *to_be_free;
	t_line	*prev;
	to_be_free = *str;
	while (to_be_free)
	{
		prev = to_be_free;
		to_be_free = to_be_free->next;
		if (prev->str)
			free(prev->str);
		free(prev->status1);
		free(prev);
	}
	free(status);
}

void	ft_free_holder(t_holder **str)
{
	t_holder	*to_be_free;
	t_holder	*prev;
	to_be_free = *str;
	int			i;
	while (to_be_free)
	{
		i = 0;
		prev = to_be_free;
		to_be_free = to_be_free->next;
		while (i < 1000)
		{	
			free(prev->args[i]);
			free(prev->file_in[i]);
			free(prev->file_out[i]);
			free(prev->append[i]);
			free(prev->her_doc[i]);
			free(prev->args_built_in[i]);
			i++;
		}
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
}
