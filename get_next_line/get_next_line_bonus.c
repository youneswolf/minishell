/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:36:33 by asedoun           #+#    #+#             */
/*   Updated: 2024/03/28 23:02:54 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_str_len(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

int	find_nl(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
		return (i - 1);
	return (i);
}

char	*ft_substr(char *s, int start, int (*fct)(char *))
{
	int		i;
	char	*dst;
	int		len;

	if (!s || s[0] == '\0')
		return (NULL);
	i = ft_str_len(s);
	len = fct(s);
	dst = (char *)malloc(sizeof(char) * (len) + 2);
	if (!dst)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		dst[i] = s[start];
		i++;
		start++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*read_in_static(int fd, char *static_str)
{
	int		i;
	char	*buffer;

	i = 1;
	buffer = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&static_str));
	buffer[0] = '\0';
	while (i > 0 && !ft_str_chr(buffer, '\n'))
	{
		i = read (fd, buffer, BUFFER_SIZE);
		if (i == -1)
			return (free(buffer), ft_free(&static_str));
		if (i > 0)
		{
			buffer[i] = '\0';
			static_str = ft_str_join(static_str, buffer);
			if (!static_str)
				return (ft_free(&buffer), ft_free(&static_str));
		}
	}
	free(buffer);
	return (static_str);
}

char	*get_next_line(int fd)
{
	char		*to_return;
	static char	*static_str[OPEN_MAX];

	to_return = NULL;
	if (fd < 0 || fd > OPEN_MAX)
		return (NULL);
	if (BUFFER_SIZE < 1 || (size_t)BUFFER_SIZE > INT_MAX)
		return (ft_free(&static_str[fd]));
	static_str[fd] = read_in_static(fd, static_str[fd]);
	if (!static_str[fd])
		return (NULL);
	to_return = ft_substr(static_str[fd], 0, &find_nl);
	if (!to_return)
		return (ft_free(&static_str[fd]));
	static_str[fd] = skip_nl(static_str[fd]);
	return (to_return);
}
