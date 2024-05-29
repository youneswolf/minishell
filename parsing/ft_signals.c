/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:42:21 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/29 10:00:51 by ybellakr         ###   ########.fr       */
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
	printf("minishell$ ");
	signal(SIGINT, ft_ctr_c);
	fflush(stdout);
}
