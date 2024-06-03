/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:51:57 by ybellakr          #+#    #+#             */
/*   Updated: 2024/06/03 13:18:30 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

char	*split_space_str(char *str)
{
	char	**new_str;
	char	*no_space_str;
	int		i;

	no_space_str = NULL;
	i = 0;
	new_str = ft_split(str, ' ');
	if (!str)
		return (NULL);
	while (new_str[i])
	{
		no_space_str = ft_strjoin(no_space_str, new_str[i], 1);
		no_space_str = ft_strjoin(no_space_str, " ", 1);
		i++;
	}
	free(str);
	ft_free_2d(new_str);
	if (!no_space_str)
		return (ft_strdup(""));
	return (no_space_str);
}

void	main_utils1(t_line *str, t_env *mini_env)
{
	int	*arr;
	int	i;

	(1) && (arr = NULL, i = 0);
	while (str)
	{
		if (if_dollar(str->str) && str->token != DELIMITER
			&& !ft_strnstr(str->str, "$?", ft_strlen(str->str)))
		{
			arr = ft_exe(str->str);
			str->str = handle_expand(str->str, &mini_env, arr);
			str->flag = 1;
			if (is_between_quotes(str->str))
				str->is_between_quote = 1;
			str->str = split_space_str(str->str);
			free(arr);
		}
		else if (ft_strnstr(str->str, "$?", ft_strlen(str->str)))
		{
			arr = ft_exe(str->str);
			printf("%d\n",arr[0]);
			str->str = put_status_in_str(str->str, 1337, &mini_env, arr);
			str->str = split_space_str(str->str);
			str->flag = 1;
			free(arr);
		}
		str = str->next;
	}
}

void	main_utils(t_line *str, t_last *t, t_status *status, t_env *mini_env)
{
	t_line		*old;
	t_holder	*tmp;

	tmp = NULL;
	if (!ft_syntax(str, t))
		return (ft_free_list(&str, status));
	old = str;
	main_utils1(str, mini_env);
	str = old;
	ft_skip_empty_expand(&str);
	ft_set_token_to_none(str);
	ft_give_token(str, status);
	ft_remove_quote(&str, t->line);
	ft_is_buil(str);
	tmp = ft_create_holder_node(str, t->line);
	ft_free_list(&str, status);
	if (tmp)
	{
		if (ft_oppen_files(tmp, t))
			execution(&tmp, mini_env, t);
	}
}

int	main_utils_1(t_line *str, t_env *mini_env)
{
	char		*line;
	t_status	*status;
	t_last		t;

	if (signal(SIGQUIT, ft_handler_ctrl_c) == SIG_ERR
		|| (signal(SIGINT, ft_handler_ctrl_c) == SIG_ERR))
		return (1);
	t.status = ft_status(0, 1337);
	line = readline("minishell$ ");
	if (line == NULL)
		(ft_free_list(&str, NULL), free(line), exit(ft_status(0, 1)));
	if (ft_strlen(line) > 0)
		add_history(line);
	line = ft_add_space_to_command(line);
	ft_put(line, &str);
	if (!str)
		return (free(line), 0);
	status = malloc(sizeof(t_status));
	if (!status)
		return (free(line), ft_free_list(&str, status), 0);
	(1) && (status->status = ft_status(0, 1), t.line = line);
	ft_give_token(str, status);
	ft_is_buil(str);
	main_utils(str, &t, status, mini_env);
	return (free(line), 0);
}

int	main(int ac, char **av, char **env)
{
	t_line			*str;
	t_last			t;
	t_holder		*tmp;
	t_env			*mini_env;
	struct termios	attr;

	(void)ac;
	(void)av;
	(1) && (tmp = NULL, str = NULL, mini_env = NULL);
	if (tcgetattr(STDIN_FILENO, &attr) == -1)
		perror("attributes");
	attr.c_lflag = ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &attr);
	t.status = ft_status(0, 1337);
	if (env[0])
		fill_env(&mini_env, env);
	else
		fill_null_env(&mini_env);
	while (1)
	{
		if (main_utils_1(str, mini_env))
			perror("signal");
		tcsetattr(STDIN_FILENO, TCSANOW, &attr);
	}
}
