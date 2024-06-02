/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:37:04 by ybellakr          #+#    #+#             */
/*   Updated: 2024/06/02 20:44:13 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count1(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] && s[i] != '\0')
	{
		while ((s[i] == c || s[i] == '\t') && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\t' && s[i] != '\0')
		{
			count++;
			while (s[i] != c && s[i] != '\t' && s[i] != '\0')
				i++;
		}
	}
	return (count);
}

static char	*word1(const char *str, char c)
{
	int		i;
	char	*p;

	i = 0;
	while (str[i] && str[i] != '\t' && str[i] != c)
		i++;
	p = (char *)malloc(i + 1);
	if (!p)
		return (NULL);
	i = 0;
	while (str[i] != c && str[i] != '\t' && str[i] != '\0')
	{
		p[i] = str[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

static int	ft_free(char **array, const char *str, char c, int a)
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
		while ((*(str + j) == c || *(str + j) == '\t') && *(str + j))
			j++;
	else if (a == 1)
		while (*(str + j) != c && *(str + j) != '\t' && *(str + j))
			j++;
	return (j);
}

static char	**alloc1(int l)
{
	char	**array;

	array = (char **)malloc((l + 1) * sizeof(char *));
	if (!array)
		return (0);
	return (array);
}

char	**ft_split1(const char *str, char c)
{
	int		j;
	int		l;
	char	**array;

	j = 0;
	if (str == NULL)
		return (NULL);
	l = count1(str, c);
	array = alloc1(l);
	if (!array)
		return (NULL);
	while (j < l)
	{
		str += ft_free(array, str, c, 0);
		if (*str != c && *str != '\t' && *str)
		{
			array[j] = word1(str, c);
			if (!array[j] && !ft_free(array, str, c, 3))
				return (NULL);
			j++;
		}
		str += ft_free(array, str, c, 1);
	}
	array[j] = NULL;
	return (array);
}
