/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:00:44 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/26 13:41:12 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(char *s1)
{
	size_t	i;
	char	*dest;

	i = ft_strlen(s1);
	dest = (char *)malloc(sizeof(char) *(i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int ft_check_if_chars_digit(char c)
{
    return ((c >= '0' && c <= '9')||(c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
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

