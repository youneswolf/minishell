/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 00:20:36 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/28 00:21:53 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_output(int fd)
{
	int	i;

	if (fd == -1)
	{
		perror("Error opening file");
	}
	i = dup2(fd, STDOUT_FILENO);
	close(fd);
	if (i == -1)
	{
		perror("Error ;l file descriptor");
	}
}
