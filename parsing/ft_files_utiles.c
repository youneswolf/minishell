/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files_utiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:28:03 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/29 10:01:09 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_ambiguous(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str && !str[0])
		return (1);
	if (str && str[0] == 32)
	{
		while (str[i] && str[i] == 32)
			i++;
		if (!str[i])
			return (1);
	}
	i = 0;
	while (str && str[i])
	{
		if (str[i] == ' ')
			j = 1;
		if (j == 1 && ft_isalnum(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_free_2d_am(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
}

void	ft_null_tmp(t_holder **tmp)
{
	if ((*tmp)->cmd)
	{
		free((*tmp)->cmd);
		(*tmp)->cmd = NULL;
	}
	if ((*tmp)->args[0])
	{
		ft_free_2d_am((*tmp)->args);
		(*tmp)->args[0] = NULL;
	}
	if ((*tmp)->cmd_built_in)
	{
		free((*tmp)->cmd_built_in);
		(*tmp)->cmd_built_in = NULL;
	}
	if ((*tmp)->args_built_in[0])
	{
		ft_free_2d_am((*tmp)->args_built_in);
		(*tmp)->args_built_in[0] = NULL;
	}
}

void	ft_oppen_files_utiles1(t_holder *tmp, t_file *t)
{
	(void)t;
	ft_putstr_fd("bash: : ambiguous redirect\n", 2);
	ft_null_tmp(&tmp);
	ft_status(1, 1);
}
