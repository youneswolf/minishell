/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:36:17 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/29 09:51:36 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_remove_utils(t_line *tmp)
{
	t_remove	t;

	t.count = ft_strlen(tmp->str);
	t.i = 0;
	while (tmp && tmp->str[t.i])
	{
		(1) && (tmp->quote = 0, tmp->type_quote = 0);
		if (tmp->str[t.i] == '\"' || tmp->str[t.i] == '\'')
		{
			(1) && (tmp->quote = 1, tmp->type_quote = tmp->str[t.i]);
			(1) && (t.flag = tmp->str[t.i], t.i++);
			while (tmp->str[t.i])
			{
				if (tmp->str[t.i] == t.flag)
				{
					(1) && (t.count -= 2, t.flag = 0);
					break ;
				}
				t.i++;
			}
		}
		if (tmp->str[t.i])
			t.i++;
	}
	return (t.count + 1);
}

char	*ft_remove_utils2(t_line *tmp, char *str, int j, int i)
{
	int	flag;

	while (tmp && tmp->str[i] && tmp->str)
	{
		if (tmp->str[i] != '\'' && tmp->str[i] != '\"')
			(1) && (str[j] = tmp->str[i], j++);
		else if (tmp->str[i] == '\"' || tmp->str[i] == '\'')
		{
			(1) && (flag = tmp->str[i], i++);
			while (tmp->str[i])
			{
				if (tmp->str[i] == flag)
				{
					flag = 0;
					break ;
				}
				else if (tmp->str[i] != flag && tmp->str[i])
					(1) && (str[j] = tmp->str[i], j++);
				i++;
			}
		}
		if (tmp->str[i])
			i++;
	}
	return (str[j] = '\0', free(tmp->str), str);
}

char	*ft_remove(t_line *tmp, char *line)
{
	int		j;
	int		count;
	char	*str;
	int		i;

	(void)line;
	str = NULL;
	j = 0;
	i = 0;
	count = ft_remove_utils(tmp);
	if (count > 0)
		str = malloc(count * sizeof(char) + 1);
	if (!str)
		return (free(str), ft_free_list(&tmp, NULL), NULL);
	str = ft_remove_utils2(tmp, str, j, i);
	if (str[0] == '\0' && tmp->flag != 1)
		ft_putstr_fd("bash: :command not found\n", 2);
	return (str);
}

char	*ft_strchr2(char *s, int c)
{
	char	x;
	int		i;

	i = 0;
	x = (char)c;
	while (s[i])
	{
		if (s[i] == x)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == x)
		return ((char *)&s[i]);
	return (NULL);
}

void	ft_remove_quote(t_line **str, char *line)
{
	t_line	*tmp;
	int		i;

	tmp = *str;
	i = 0;
	while (tmp)
	{
		if (ft_strchr1(tmp->str, '*'))
			;
		else if (tmp->token == DELIMITER)
			;
		else if (tmp && tmp->token != DELIMITER && (tmp->token == CMD
				|| tmp->token == ARGS || tmp->token == OUT_FILE
				|| tmp->token == IN_FILE)
			&& (ft_strchr1(tmp->str, '\'') || ft_strchr1(tmp->str, '\"')))
			tmp->str = ft_remove(tmp, line);
		tmp = tmp->next;
	}
}
