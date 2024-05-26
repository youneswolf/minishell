/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_give_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:02:53 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/26 13:41:04 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *str, char *str1)
{
	int	i;

	i = 0;
	while (str && str1 && (str[i] || str1[i]))
	{
		if (str[i] != str1[i])
			return (0);
		i++;
	}
	return (1);
}

void	ft_give_token_else(t_line *tmp, int *flag1)
{
	if (tmp->token == ARGS || tmp->token == FILE || tmp->token == DELIMITER
		|| tmp->token == IN_FILE || tmp->token == OUT_FILE)
	{
		if ((tmp->token == IN_FILE || tmp->token == OUT_FILE
				|| tmp->token == FILE || tmp->token == DELIMITER)
			&& tmp->next && *flag1 == 1)
			tmp->next->token = ARGS;
		else if (tmp->next && tmp->token != ARGS && tmp->next->token != ARGS)
			tmp->next->token = CMD;
		else if (tmp->next && tmp->token == ARGS)
			tmp->next->token = ARGS;
	}
	else
	{
		*flag1 = 1;
		tmp->token = CMD;
		if (tmp->next != NULL)
			tmp->next->token = ARGS;
	}
}

void	ft_give_redire(t_line *tmp, int *flag1, int *index, t_status *status)
{
	if (ft_strcmp(tmp->str, ">>"))
	{
		tmp->token = APPEND;
		if (tmp->next != NULL)
		{
			status->index = *index + 1;
			tmp->next->token = FILE;
		}
	}
	else if (ft_strcmp(tmp->str, "<<"))
	{
		tmp->token = HERDOC;
		if (tmp->next != NULL)
			tmp->next->token = DELIMITER;
	}
	else if (ft_strcmp(tmp->str, "<"))
	{
		tmp->token = IN_REDIR;
		if (tmp->next != NULL)
			(1) && (status->index = (*index)++, tmp->next->token = IN_FILE);
	}
	else
		ft_give_token_else(tmp, flag1);
}

void	ft_give_token(t_line *head, t_status *status)
{
	t_line	*tmp;
	int		index;
	int		flag1;

	tmp = head;
	flag1 = 0;
	index = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->str, "|"))
			(1) && (tmp->token = PIPE, flag1 = 0, index = 0);
		else if (ft_strcmp(tmp->str, ">"))
		{
			tmp->token = OUT_REDIR;
			if (tmp->next != NULL)
				(1) && (status->index = index++, tmp->next->token = OUT_FILE);
		}
		else
			ft_give_redire(tmp, &flag1, &index, status);
		tmp = tmp->next;
	}
}
