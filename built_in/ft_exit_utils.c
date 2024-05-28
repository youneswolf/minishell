/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:26:52 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/28 16:27:11 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit2(t_holder *str, int count)
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
		(ft_status(0, 1));
	else if (i > 2 && ft_is_numeric(tmp1->args_built_in[1]))
		(write(2, "bash: exit: too many arguments\n",
				32), ft_status(1, 1));
	else if (i == 2 && ft_is_numeric(tmp1->args_built_in[1])
		&& ((size_t)ft_atoi(tmp1->args_built_in[1]) <= 9223372036854775807
			|| (size_t)ft_atoi(tmp1->args_built_in[1]) >= -922337203685477588))
		(ft_status(1, ft_atoi(tmp1->args_built_in[1]) % 256));
	else if (tmp1->args_built_in[1] && !ft_is_numeric(tmp1->args_built_in[1]))
		ft_exit_utils(0);
	else if (tmp1->args_built_in[1] && ft_is_numeric(tmp1->args_built_in[1])
		&& ((size_t)ft_atoi(tmp1->args_built_in[1]) > 9223372036854775807
			|| (size_t)ft_atoi(tmp1->args_built_in[1]) < -922337203685477588))
		ft_exit_utils(0);
}
