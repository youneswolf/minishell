/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:00:44 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/28 05:47:09 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_if_chars_digit(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') 
		|| (c >= 'A' && c <= 'Z') || c == '_');
}

char	*ft_strchr(char *s, int c)
{
	char	x;
	int		i;

	i = 0;
	x = (char)c;
	while (s[i])
	{
		if (s[i] == x)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (s[i] == x)
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}

char	*ft_allocate_for_var(int flag, char *str, int i)
{
	char	*ptr;

	ptr = NULL;
	if (flag == 1 && str != NULL)
	{
		str += (i + 1);
		ptr = ft_strdup(str);
		if (!ptr)
			return (NULL);
		str -= (i + 1);
		return (ptr);
	}
	return (ptr);
}

int	ft_surpass_chars(char *var)
{
	int	i;

	i = 0;
	while (var[i] && ft_check_if_chars_digit(var[i]))
		i++;
	return (i + 1);
}

void	ft_append_char(char **str, int c)
{
	int		len;
	char	*s;
	int		i;

	i = 0;
	len = ft_strlen(*str);
	s = *str;
	*str = malloc(sizeof(char) * (len + 2));
	if (!(*str))
		return ;
	while (s && s[i])
	{
		(*str)[i] = s[i];
		i++;
	}
	(1) && ((*str)[i++] = c, (*str)[i] = '\0');
	free(s);
}
