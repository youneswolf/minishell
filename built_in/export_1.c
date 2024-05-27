/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 23:27:22 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/27 23:39:32 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sort_list(t_env **env)
{
	t_env	*first;
	t_env	*second;
	char	*tmp;

	first = *env;
	while (first != NULL && first->next != NULL)
	{
		second = *env;
		while (second != NULL && second->next != NULL)
		{
			if (ft_strcmp_asd(second->env, second->next->env) > 0)
			{
				tmp = second->env;
				second->env = second->next->env;
				second->next->env = tmp;
			}
			second = second->next;
		}
		first = first->next;
	}
}

void	ft_print_export(t_env *head)
{
	while (head)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_export(head->env);
		write(1, "\n", 1);
		head = head->next;
	}
}
