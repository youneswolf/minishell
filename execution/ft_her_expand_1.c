/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_her_expand_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 01:14:25 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/28 01:20:36 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_str_join(char *static_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;
	size_t	len;

	if (!static_str && !buff)
		return (NULL);
	if (!static_str && buff)
		return (ft_strdup(buff));
	if (!buff && static_str)
		return (ft_strdup(static_str));
	len = ft_strlen(static_str);
	str = malloc(sizeof(char) * (len + ft_strlen(buff)) + 1);
	if (!str)
		return (NULL);
	(1) && (i = 0, j = 0);
	while (static_str && static_str[i] != '\0')
	{
		str[i] = static_str[i];
		i++;
	}
	while (buff && buff[j] != '\0')
		str[i++] = buff[j++];
	str[i] = '\0';
	return (str);
}

int	ft_isalpha(int c)
{
	if (((unsigned char )c >= 65 && (unsigned char )c <= 90)
		|| ((unsigned char )c >= 97 && (unsigned char )c <= 122))
	{
		return (1);
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if ((char )c >= 48 && (char )c <= 57)
	{
		return (1);
	}
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}
