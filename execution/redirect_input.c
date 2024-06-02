/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 00:20:39 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/28 00:21:41 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_input(int fd)
{
	int	i;

	if (fd == -1)
	{
		perror("Error opening file");
	}
	i = dup2(fd, STDIN_FILENO);
	if (i == -1)
	{
		perror("Error dupli33cating file descriptor");
		close(fd);
	}
}
