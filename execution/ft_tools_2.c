/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 01:50:07 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/29 21:42:12 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	if (dstsize == 0)
	{
		return (ft_strlen(src));
	}
	len = 0;
	i = 0;
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[len])
	{
		len++;
	}
	return (len);
}

char	*ft_sub_str(char *s, unsigned int start, size_t len, int is_free)
{
	size_t	i;
	char	*dst;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if (start > i)
		return (ft_strdup(""));
	if (i - start < len)
		len = i - start;
	dst = (char *)malloc(sizeof(char) * (len) + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = s[start];
		i++;
		start++;
	}
	if (is_free == 1)
		free(s);
	dst[i] = '\0';
	return (dst);
}

static	int	start_finder(char *s1, char *set)
{
	size_t	i;
	size_t	len;

	if (!set)
		return (ft_strlen(s1) - 1);
	if (s1[0] == '\0')
	{
		return (0);
	}
	len = ft_strlen(s1);
	i = 0;
	while (i < len && ft_strchr(set, s1[i]))
	{
		i++;
	}
	return (i);
}

static	int	end_finder(char *s1, char *set)
{
	size_t	i;
	size_t	len;

	if (!set)
		return (0);
	if (s1[0] == '\0')
	{
		return (0);
	}
	len = ft_strlen(s1) - 1;
	i = start_finder(s1, set);
	while (len > i && ft_strchr(set, s1[len]))
	{
		len--;
	}
	return (len);
}

char	*ft_strtrim(char *s1, char *set, int arg)
{
	size_t	start;
	size_t	end;
	size_t	res_len;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	if (s1[0] == '\0')
		return (ft_strdup(""));
	start = start_finder(s1, set);
	end = end_finder(s1, set);
	res_len = end - start + 1;
	result = (char *)malloc(((res_len + 1)) * sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1 + start, res_len + 1);
	result[res_len] = '\0';
	if (arg == 0)
		free(s1);
	return (result);
}
