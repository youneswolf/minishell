/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:51:51 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/29 21:50:30 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_there_exit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'e' && str[i + 1] == 'x'
			&& str[i + 2] == 'i' && str[i + 3] == 't')
			return (1);
		i++;
	}
	return (0);
}

void	ft_add_space_utils(char *new_line, char *str, int quote, t_add_space t)
{
	while (str && str[t.i])
	{
		if (str[t.i] == '\'' || str[t.i] == '\"')
			(1) && (t.flag = 1, quote = str[t.i]);
		if (t.flag == 0 && ((str[t.i] == '>' && str[t.i + 1] == '>')
				|| (str[t.i] == '<' && str[t.i + 1] == '<')))
		{
			(1) && (new_line[t.count] = ' ', new_line[t.count + 1] = str[t.i]);
			(1) && (new_line[t.count + 2] = str[t.i]);
			(1) && (new_line[t.count + 3] = ' ', t.count = t.count + 3, t.i++);
		}
		else if (t.flag == 0 && (str[t.i] == '|'
				|| str[t.i] == '>' || str[t.i] == '<'))
		{
			(1) && (new_line[t.count] = ' ', new_line[t.count + 1] = str[t.i]);
			(1) && (new_line[t.count + 2] = ' ', t.count = t.count + 2);
		}
		else
			new_line[t.count] = str[t.i];
		(1) && (t.i++, t.count++);
		if (str[t.i] && str[t.i] == quote)
			(1) && (new_line[t.count] = str[t.i], t.i++,
				t.count++, t.flag = 0, quote = 0);
	}
	new_line[t.count] = '\0';
}

char	*ft_add_space_to_command(char *str)
{
	t_add_space	t;
	char		*new_line;
	int			quote;

	(1) && (t.i = 0, t.count = 0, t.flag = 0, quote = 0); 
	while (str && str[t.i] != '\0')
	{
		if (str[t.i] == '|' || str[t.i] == '>' || str[t.i] == '<'
			|| (str[t.i] == '<' && str[t.i + 1] == '<')
			|| (str[t.i] == '>' && str[t.i + 1] == '>'))
			t.count++;
		t.i++;
	}
	new_line = malloc(t.i + 1 + t.count * 2);
	if (!new_line)
		return (free(str), perror("malloc"), NULL);
	t.i = 0;
	t.count = 0;
	ft_add_space_utils(new_line, str, quote, t);
	return (free(str), new_line);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*src;

	src = (char *)haystack;
	j = 0;
	i = 0;
	if (needle[0] == '\0')
	{
		return (src);
	}
	while (i < len && haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (i + j) < len)
		{
			if (needle[j + 1] == '\0')
			{
				return (&src[i]);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}
