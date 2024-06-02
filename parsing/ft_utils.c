/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:54:12 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/29 16:02:36 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	f_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (0);
	while (str1 && str2 && str2[i] != '\0' && str1[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

void	ft_ctr(int sig)
{
	(void)sig;
	printf("\nminishell$ ");
	return ;
}

static	char	*conv(int n)
{
	int		i;
	char	*a;
	long	num;

	if (n == 0)
		return (ft_strdup("0"));
	i = int_len(n);
	num = n;
	a = (char *)malloc(sizeof(char) * (i + 1));
	if (!a)
		return (NULL);
	a[i--] = '\0';
	if (num < 0)
	{
		num *= -1;
		a[0] = '-';
	}
	while (num > 0)
	{
		a[i] = num % 10 + 48;
		num = num / 10;
		i--;
	}
	return (a);
}

char	*ft_itoa(int n)
{
	char	*str;

	str = conv(n);
	return (str);
}
