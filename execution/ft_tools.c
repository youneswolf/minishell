/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 01:48:55 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/28 02:38:00 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_sgl(char *str, int i)
{
	int	count;

	if (str[i] && str[i] == 39)
		i = i + 1;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == 39)
			count++;
		i++;
	}
	return (count);
}

int	is_sgl_quote_ex(char *str, int last)
{
	int			i;
	static int	sgl;
	int			j;

	if (last == 1)
		sgl = 0;
	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (str[i] == 39)
			(1) && sgl++, j = 1;
		if (str[i] == 39 && str[i + 1] && str[i + 1] == 34)
			return (sgl += count_sgl(str, i), 1);
		if (str[i] == 34 && str[i + 1] && str[i + 1] == 39)
			return (sgl += count_sgl(str, i), 0);
		if (j && check_sgl_parity(str, i, sgl))
			return (sgl += count_sgl(str, i), 1);
		if (str[i] == '$' && j)
			return (sgl += count_sgl(str, i), 1);
		i++;
	}
	return (0);
}

void	env_list(t_env **mini_env, char *line)
{
	t_env	*node;
	t_env	*last_node;

	node = malloc(sizeof(t_env));
	if (!node)
		(ft_free_nodes(mini_env), exit(1));
	node->env = line;
	node->printed = 0;
	node->deleted = 0;
	node->next = NULL;
	if (!(*mini_env))
		*mini_env = node;
	else
	{
		last_node = get_last(mini_env);
		last_node->next = node;
	}
}

void	append_dollar_if_check(t_exp *vars, int check)
{
	if (check == 0)
			vars->dollar_str_space = ft_strjoin("$", 
					vars->dollar_str_space, 3);
}
