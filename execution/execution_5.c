/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 03:50:10 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/28 05:07:49 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_quote(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == 39 || str[i] == 34)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_remove_dollar(char *str)
{
	int		i;
	char	*new_str;

	i = 1;
	new_str = NULL;
	if ((str && str[0] == '$') && ((str[1] && str[1] == 39) 
			|| (str[1] && str[1] == 34)))
	{
		new_str = malloc(ft_strlen(str));
		while (str && str[i])
		{
			new_str[i -1] = str[i];
			i++;
		}
		new_str[i -1] = '\0';
		free(str);
		return (new_str);
	}
	return (str);
}

void	here_doc_line(char **line, int pipe_fd[2], t_env **env, int i)
{
	if (if_dollar(*line) && !i && !ft_strnstr(*line, "$?",
			ft_strlen(*line)))
		*line = handle_expand_here(*line, env);
	else if (ft_strnstr(*line, "$?", ft_strlen(*line)))
		*line = put_status_in_str(*line, 1337);
	write(pipe_fd[1], *line, ft_strlen(*line));
	write(pipe_fd[1], "\n", 1);
	free(*line);
}

void	ft_here_doc(char *lim, int pipe_fd[2], t_holder *atmp,
	t_env **env)
{
	char	*line;
	char	*str;
	int		i;

	(1) && (i = 42, str = NULL);
	line = readline("here_doc> ");
	if (!line)
		exit(1);
	i = if_dollar(lim);
	if (i == 1)
		lim = ft_remove_dollar(lim);
	i = is_quote(lim);
	if (i == 1)
		lim = ft_remove_here(lim);
	while (ft_strncmp(lim, line, ft_strlen(lim))
		|| ft_strlen(line) != ft_strlen(lim))
	{
		here_doc_line(&line, pipe_fd, env, i);
		line = readline("here_doc> ");
		if (!line)
			(exit(1));
	}
	free(line);
	free(lim);
	exit(1);
}

void	here_piping(t_execution *vars)
{
	close(vars->pipe_fd[1]);
	dup2(vars->origin_in, STDIN_FILENO);
	close(vars->pipe_fd[0]);
}
