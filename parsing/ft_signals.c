/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:42:21 by ybellakr          #+#    #+#             */
/*   Updated: 2024/06/03 13:31:13 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	ft_ctr_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	ft_putstr("minishell$ ");
	signal(SIGINT, ft_ctr_c);
}

int	check_for_first_elem(char *str)
{
	int	i;

	i = 0;
	if (str && str[0] && str[0] == '$')
		return (0);
	while (str && str[i] && str[i] != '$')
	{
		if (str[i] != '.' || str[i] != ',' || str[i] != '/'
			|| str[i] != '-' || str[i] != ':')
			return (1);
		i++;
	}
	return (0);
}

int	is_number(char *str)
{
	if (str[1] && str[1] >= '0' && str[1] <= '9')
		return (1);
	return (0);
}

int	is_only_special(char *str)
{
	int	i;

	i = 0;
	if (str && str[0] && str[0] == '$')
		i++;
	if (!str[i])
		return (0);
	while (str && str[i])
	{
		if (str[i] != '.' && str[i] != ',' && str[i] != '/' 
			&& str[i] != '-' && str[i] != ':')
		{
			return (1);
		}
		i++;
	}
	return (0);
}
