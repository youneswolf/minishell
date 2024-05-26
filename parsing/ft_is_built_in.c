/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:46:23 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/26 13:48:11 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_cmp_built_in(char *str)
{
	int	i;
	char **checker;

	checker = malloc(8 * sizeof(char *));
	if (!checker)
		return (perror("malloc"), 0);
	checker[0] = ft_strdup("echo");
	checker[1] = ft_strdup("cd");
	checker[2] = ft_strdup("pwd");
	checker[3] = ft_strdup("export");
	checker[4] = ft_strdup("unset");
	checker[5] = ft_strdup("env");
	checker[6] = ft_strdup("exit");
	checker[7] = NULL;
	i = 0;
	while (checker[i])
	{
		if (f_strcmp(checker[i], str) && ft_strlen(checker[i]) == ft_strlen(str))
			return (ft_free_2d(checker), 1);
		i++;
	}
	return (ft_free_2d(checker), 0);
}

void	ft_is_buil(t_line *str)
{
	t_line *tmp = str;

	while (tmp)
	{
		tmp->is_it_built_in = 0;
		if ((tmp->token == CMD) && ft_cmp_built_in(tmp->str) == 1)
			tmp->is_it_built_in = 1;
		tmp = tmp->next;
	}
}

int	ft_handle_issue_herdoc_utils(t_line *tmp, char *s1)
{
	if (!ft_strcmp(s1, tmp->next->str))
	{
		if (tmp->next->str[0] == '$')
		{
			tmp->deja = 1;
			tmp->next->str = ft_substr1(tmp->next->str, 1, ft_strlen(tmp->next->str), 1);
		}
		free(s1);
		return (0);
	}
	return (1);
}

void	ft_handle_issue_herdoc(t_line *str)
{
	t_line *tmp;
	char	*s1;

	tmp = str;
	while (tmp)
	{
		if (tmp->token == HERDOC && tmp->next && tmp->next->token == DELIMITER)
		{
			if (tmp->next->str[0] == '$')
				return ;
			s1 = ft_strdup(tmp->next->str);
			tmp->next->str = ft_remove3(tmp->next->str);
			if ((s1[0] == '\'' || s1[0] == '\"') && s1[1] == '$')
			{
				free (s1);
				return ;
			}
			else if (!ft_handle_issue_herdoc_utils(tmp, s1))
				return ;
		}
		tmp = tmp->next;
	}
}

void	ft_set_token_to_none(t_line *str)
{
	t_line	*tmp;

	tmp = str;
	while (tmp)
	{
		tmp->token = NONE;
		tmp = tmp->next;
	}
}
