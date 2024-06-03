/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_holder_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:24:09 by ybellakr          #+#    #+#             */
/*   Updated: 2024/06/02 22:44:16 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_ut2(t_holder *new, int a)
{
	if (a == 11)
		return (ft_free_2dd(new->args_built_in),
			ft_free_2dd(new->file_in),
			ft_free_2dd(new->file_out), ft_free_2dd(new->append),
			free(new->ap), free(new->out), free(new->outfile_index),
			free(new->infile_index), free(new->append_index), free(new));
	else if (a == 12)
		return (ft_free_2dd(new->args_built_in),
			ft_free_2dd(new->file_in),
			ft_free_2dd(new->file_out), ft_free_2dd(new->append),
			free(new->ap), free(new->out), free(new->outfile_index),
			free(new->infile_index), free(new->append_index), free(new->in), 
			free(new));
}

void	ft_free_ut(t_holder *new, int a)
{
	if (a == 7)
		return (ft_free_2dd(new->args_built_in), 
			ft_free_2dd(new->file_in), 
			ft_free_2dd(new->file_out), ft_free_2dd(new->append),
			free(new->ap), free(new));
	if (a == 8)
		return (ft_free_2dd(new->args_built_in), 
			ft_free_2dd(new->file_in), 
			ft_free_2dd(new->file_out), ft_free_2dd(new->append),
			free(new->ap), free(new->out), free(new));
	if (a == 9)
		return (ft_free_2dd(new->args_built_in), 
			ft_free_2dd(new->file_in), 
			ft_free_2dd(new->file_out), ft_free_2dd(new->append),
			free(new->ap), free(new->out), free(new->outfile_index), free(new));
	if (a == 10)
		return (ft_free_2dd(new->args_built_in), 
			ft_free_2dd(new->file_in), 
			ft_free_2dd(new->file_out), ft_free_2dd(new->append),
			free(new->ap), free(new->out), free(new->outfile_index), 
			free(new->infile_index), free(new));
	else
		ft_free_ut2(new, a);
}

char	*ft_free_if_need(t_holder *new, int a)
{
	if (a == 0)
		return (NULL);
	else if (a == 1)
		return (free(new), new = NULL, NULL);
	else if (a == 2)
		return (ft_free_2dd(new->args), free(new), new = NULL, NULL);
	else if (a == 3)
		return (ft_free_2dd(new->args),
			ft_free_2dd(new->args_built_in), free(new), new = NULL, NULL);
	else if (a == 4)
		return (ft_free_2dd(new->args), ft_free_2dd(new->args_built_in),
			ft_free_2dd(new->file_in), free(new), new = NULL, NULL);
	else if (a == 5)
		return (ft_free_2dd(new->args), 
			ft_free_2dd(new->args_built_in), 
			ft_free_2dd(new->file_in), 
			ft_free_2dd(new->file_out), free(new), new = NULL, NULL);
	else if (a == 6)
		return (ft_free_2dd(new->args), 
			ft_free_2dd(new->args_built_in), 
			ft_free_2dd(new->file_in), ft_free_2dd(new->file_out), 
			ft_free_2dd(new->append), free(new), new = NULL, NULL);
	else
		ft_free_ut(new, a);
	return (new = NULL, NULL);
}
