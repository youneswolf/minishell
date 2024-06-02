/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:03:38 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/29 18:36:33 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr1(char *str, int start, int len, int not_)
{
	char	*sub;
	int		i;
	int		str_len;

	i = 0;
	str_len = ft_strlen(str);
	if (start + len > str_len)
		len = str_len - start;
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	while (i < len)
		sub[i++] = str[start++];
	sub[len] = '\0';
	if (not_ == 1)
		free(str);
	return (sub);
}

char	*ft_substr(char *str, int start, int len)
{
	char	*sub;
	int		i;
	int		str_len;

	i = 0;
	str_len = ft_strlen(str);
	if (start + len > str_len)
		len = str_len - start;
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	while (i < len)
		sub[i++] = str[start++];
	sub[len] = '\0';
	return (sub);
}
