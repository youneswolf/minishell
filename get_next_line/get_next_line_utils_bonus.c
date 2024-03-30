/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:36:40 by asedoun           #+#    #+#             */
/*   Updated: 2024/03/28 23:02:39 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"


char	*ft_str_chr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *)&s[ft_str_len(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

char	*ft_str_join(char *static_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;
	size_t	len;

	len = ft_str_len(static_str);
	str = malloc(sizeof(char) * (len + ft_str_len(buff)) + 1);
	if (!str)
		return (ft_free(&static_str));
	i = 0;
	j = 0;
	while (static_str && static_str[i] != '\0')
	{
		str[i] = static_str[i];
		i++;
	}
	while (buff && buff[j] != '\0')
		str[i++] = buff[j++];
	str[i] = '\0';
	free(static_str);
	return (str);
}

char	*skip_nl(char *static_str)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	i = 0;
	while (static_str && static_str[i] && static_str[i] != '\n')
		i++;
	len = ft_str_len(static_str) - i;
	if (static_str && static_str[i] == '\0')
		return (ft_free(&static_str));
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (ft_free(&static_str));
	i++;
	j = 0;
	while (static_str[i])
		str[j++] = static_str[i++];
	str[j] = '\0';
	free(static_str);
	static_str = NULL;
	return (str);
}
