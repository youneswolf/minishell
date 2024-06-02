/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:51:57 by ybellakr          #+#    #+#             */
/*   Updated: 2024/06/02 22:15:50 by asedoun          ###   ########.fr       */
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
	while(new_str[i])
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
int	ft_size_dollar(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

int    ft_exec_util(char *str, t_exec *t)
{
    (1) && (t->quote = str[t->i], t->i++);
    if (str[t->i] == '\0')
        return (0);
    while (str[t->i] && str[t->i] != t->quote)
    {
        if (str[t->i] == '$' && t->quote == '\"')
            (1) && (t->a[t->k] = 1, t->k++);
        else if (str[t->i] == '$' && t->quote == '\'')
            (1) && (t->a[t->k] = 0, t->k++);
        t->i++;
    }
    if (str[t->i + 1] && (str[t->i + 1] == '\"' || str[t->i + 1] == '\''))
        t->quote = str[t->i];
    else
        (1) && (t->quote = 0, t->i++);
    return (1);
}

int    *ft_exe(char *str)
{
    t_exec    t;

    t.a = malloc((ft_size_dollar(str)) * sizeof(int));
    if (!t.a)
        return (NULL);
    (1) && (t.quote = 0, t.i = 0, t.k = 0);
    while (str && str[t.i])
    {
        if (str[t.i] == '\'' || str[t.i] == '\"')
        {
            if (!ft_exec_util(str, &t))
                break ;
        }
        if (str[t.i] == '\0')
            break ;
        else if (t.quote == 0)
        {
            if (str[t.i] == '$')
                (1) && (t.a[t.k] = 1, t.k++);
        }
        if (str[t.i])
             t.i++;
    }
    return (t.a);
}

void	main_utils1(t_line *str, t_env *mini_env)
{
	int *arr;
	while (str)
	{
		if (if_dollar(str->str) && str->token != DELIMITER
			&& !ft_strnstr(str->str, "$?", ft_strlen(str->str)))
		{
			arr = ft_exe(str->str);
			int i = 0;
			str->str = handle_expand(str->str, &mini_env, arr);
			str->flag = 1;
			if (is_between_quotes(str->str))
				str->is_between_quote = 1;
			str->str = split_space_str(str->str);
			free(arr);
		}
		if (ft_strnstr(str->str, "$?", ft_strlen(str->str)))
		{
			str->str = put_status_in_str(str->str, 1337, &mini_env, arr);
			str->str = split_space_str(str->str);
			str->flag = 1;
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
