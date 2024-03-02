/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utlils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:54:59 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/02 14:36:18 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}


char	*ft_strjoin(char *s1, char *s2)
{
	int			size;
	int			i;
	char		*str;
	int			j;

	size = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc((size + 1) * sizeof(char));
	if (str == NULL)
		return (s1 = NULL, NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (s1 = NULL, str);
}

int	count(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] && s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (count);
}

char	*word(const char *str, char c)
{
	int		i;
	char	*p;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	p = (char *)malloc(i + 1);
	if (!p)
		return (NULL);
	i = 0;
	while (str[i] != c && str[i] != '\0')
	{
		p[i] = str[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

int	ft_free(char **array, const char *str, char c, int a)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (a == 3)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
		return (0);
	}
	else if (a == 0)
		while (*(str + j) == c && *(str + j))
			j++;
	else if (a == 1)
		while (*(str + j) != c && *(str + j))
			j++;
	return (j);
}

char	**alloc(int l)
{
	char	**array;

	array = (char **)malloc((l + 1) * sizeof(char *));
	if (!array)
		return (0);
	return (array);
}

char	**ft_split(const char *str, char c)
{
	int		j;
	int		l;
	char	**array;

	j = 0;
	if (str == NULL)
		return (NULL);
	l = count(str, c);
	array = alloc(l);
	if (!array)
		return (NULL);
	while (j < l)
	{
		str += ft_free(array, str, c, 0);
		if (*str != c && *str)
		{
			array[j] = word(str, c);
			if (!array[j] && !ft_free(array, str, c, 3))
				return (NULL);
			j++;
		}
		str += ft_free(array, str, c, 1);
	}
	array[j] = NULL;
	return (array);
}