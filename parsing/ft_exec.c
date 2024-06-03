/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:08:52 by ybellakr          #+#    #+#             */
/*   Updated: 2024/06/03 10:15:04 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_size_dollar(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

int	ft_exec_util(char *str, t_exec *t)
{
	(1) && (t->quote = str[t->i], t->i++);
	if (str[t->i] == '\0')
		return (0);
	while (str[t->i] && str[t->i] != t->quote)
	{
		if (str[t->i] == '$' && t->quote == '\"')
			(1) && (t->a[t->k] = 1, t->k++);
		else if (str[t->i] == '$' && t->quote == '\'')
			(1) && (t->a[t->k] = 0, t->k++);
		t->i++;
	}
	if (str[t->i + 1] && (str[t->i + 1] == '\"' || str[t->i + 1] == '\''))
		t->quote = str[t->i];
	else
		(1) && (t->quote = 0, t->i++);
	return (1);
}

int	*ft_exe(char *str)
{
	t_exec	t;

	t.a = malloc((ft_size_dollar(str)) * sizeof(int));
	if (!t.a)
		return (NULL);
	(1) && (t.quote = 0, t.i = 0, t.k = 0);
	while (str && str[t.i])
	{
		if (str[t.i] == '\'' || str[t.i] == '\"')
		{
			if (!ft_exec_util(str, &t))
				break ;
		}
		if (str[t.i] == '\0')
			break ;
		else if (t.quote == 0)
		{
			if (str[t.i] == '$')
				(1) && (t.a[t.k] = 1, t.k++);
		}
		if (str[t.i])
			t.i++;
	}
	return (t.a);
}
