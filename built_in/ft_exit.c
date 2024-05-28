/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:20:58 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/28 16:27:07 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmp(char *s, char *s1)
{
	int	i;

	i = 0;
	while (s && s1 && s[i] && s1[i] && s[i] == s1[i])
		i++;
	return (s[i] - s1[i]);
}

int	ft_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str && str[i])
	{
		if (str && (str[i] < 48 || str[i] > 57))
			return (0);
		i++;
	}
	return (1);
}

unsigned long	ft_atoi(char *str)
{
	unsigned long		j;
	int					sign;
	int					i;

	j = 0;
	sign = 0;
	i = 0;
	if (str[0] == '+' || str[0] == '-')
	{
		if (str[0] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		j = j * 10 + str[i] - 48;
		i++;
	}
	if (sign == -1)
		return (-j);
	return (j);
}

void	ft_exit_utils(int k)
{
	if (k == 1)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("exit: : numeric argument required\n", 2);
		ft_status(1, 255);
		exit(255);
	}
	else
	{
		ft_putstr_fd("exit: : numeric argument required\n", 2);
		ft_status(1, 255);
	}
}

void	ft_exit(t_holder *str, int count)
{
	t_holder		*tmp1;
	unsigned long	t;
	int				i;
	char			*s;

	tmp1 = str;
	i = 0;
	while (tmp1 && tmp1->args_built_in[i])
		i++;
	if (i == 1)
		(ft_putstr_fd("exit\n", 2), exit(ft_status(0, 1)));
	else if (i > 2 && ft_is_numeric(tmp1->args_built_in[1]))
		(write(2, "exit\n", 6), write(2, "bash: exit: too many arguments\n",
				32), ft_status(1, 1));
	else if (i == 2 && ft_is_numeric(tmp1->args_built_in[1])
		&& ((size_t)ft_atoi(tmp1->args_built_in[1]) <= 9223372036854775807
			|| (size_t)ft_atoi(tmp1->args_built_in[1]) >= -922337203685477588))
		(ft_putstr_fd("exit\n", 2), ft_status(1, ft_atoi(tmp1->args_built_in[1]))
			, exit(ft_atoi(tmp1->args_built_in[1])));
	else if (tmp1->args_built_in[1] && !ft_is_numeric(tmp1->args_built_in[1]))
		ft_exit_utils(1);
	else if (tmp1->args_built_in[1] && ft_is_numeric(tmp1->args_built_in[1])
		&& ((size_t)ft_atoi(tmp1->args_built_in[1]) > 9223372036854775807
			|| (size_t)ft_atoi(tmp1->args_built_in[1]) < -922337203685477588))
		ft_exit_utils(1);
}
