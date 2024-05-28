/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 00:20:42 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/28 00:21:28 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_append(int fd)
{
	int	i;

	if (fd == -1)
	{
		perror("Error opening file");
	}
	i = dup2(fd, STDOUT_FILENO);
	if (i == -1)
	{
		perror("Error duplica33ting file descriptor");
		close(fd);
	}
}
