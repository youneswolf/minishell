/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utlils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:54:59 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/26 13:37:54 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}


// char	*ft_strjoin(char *s1, char *s2)
// {
// 	int			size;
// 	int			i;
// 	char		*str;
// 	int			j;

// 	size = ft_strlen(s1) + ft_strlen(s2);
// 	str = (char *)malloc((size + 1) * sizeof(char));
// 	if (str == NULL)
// 		return (s1 = NULL, NULL);
// 	i = 0;
// 	while (s1 && s1[i])
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2 && s2[j])
// 		str[i++] = s2[j++];
// 	str[i] = '\0';
// 	return (s1 = NULL, str);
// }

static	char	*free2darray(char **array, int n);

static	size_t	count_seps(const char *str, char c)
{
	size_t	i;
	size_t	k;
	size_t	j;

	k = 0;
	i = 0;
	if (c == '\0')
		return (1);
	if (str[0] == '\0')
		return (0);
	j = ft_strlen(str);
	while (i <= j)
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i])
		{
			k++;
			while (str[i] != c && str[i])
				i++;
		}
		i++;
	}
	return (k);
}

static	char	*to_alloc(size_t word_len, const char *start,
char **new_strs, int k)
{
	char	*new_str;

	new_str = (char *)malloc(sizeof(char) * (word_len + 1));
	if (!new_str)
	{
		return (free2darray(new_strs, k));
	}
	memcpy(new_str, start, word_len);
	new_str[word_len] = '\0';
	return (new_str);
}

static	char	*free2darray(char **array, int n)
{
	while (n--)
		free(array[n]);
	free(array);
	return (NULL);
}

static	char	**f25lnorm(const char *s, char c, char **new_strs)
{
	const char	*start;
	size_t		k;
	char		*new_str;
	size_t		word_len;

	k = 0;
	while (*s)
	{
		if (*s != c)
		{
			start = s;
			while (*s && *s != c)
				s++;
			word_len = s - start;
			new_str = to_alloc(word_len, start, new_strs, k);
			if (!new_str)
				return (NULL);
			new_strs[k++] = new_str;
		}
		else
			s++;
	}
	new_strs[k] = NULL;
	return (new_strs);
}

char	**ft_split(char *s, char c)
{
	size_t	i;
	size_t	k;
	char	**new_strs;

	if (!s)
		return (NULL);
	k = 0;
	i = count_seps(s, c);
	new_strs = (char **)malloc(sizeof(char *) * (i + 1));
	if (new_strs == NULL)
		return (NULL);
	new_strs = f25lnorm(s, c, new_strs);
	return (new_strs);
}