/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:51:57 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/26 13:54:37 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	main_utils1(t_line *str, t_env *mini_env)
{
	while (str)
	{
		if (if_dollar(str->str) && str->token != DELIMITER &&
			!ft_strnstr(str->str, "$?", ft_strlen(str->str)))
		{
			str->str = handle_expand(str->str, &mini_env);
			str->flag = 1;
			if (is_between_quotes(str->str))
				str->is_between_quote = 1;
		}
		if (ft_strnstr(str->str, "$?", ft_strlen(str->str)))
			str->str = put_status_in_str(str->str, 1337);
		str = str->next;
	}
}

void	main_utils(t_line *str, t_last *t, t_status *status, t_env *mini_env)
{
	t_line		*old;
	t_holder	*tmp;

	tmp = NULL;
	if (!ft_syntax(str, t))
		return ;
	old = str;
	main_utils1(str, mini_env);
	str = old;
	ft_skip_empty_expand(&str);
	ft_set_token_to_none(str);
	ft_give_token(str, status);
	ft_remove_quote(&str, t->line);
	ft_is_buil(str);
	tmp = ft_create_holder_node(str,t->line);
	ft_free_list(&str, status);
	if (tmp)
	{
		if (ft_oppen_files(tmp, t))
			execution(&tmp, mini_env,t);
	}
}

int	main_utils_1(t_line *str, t_env *mini_env)
{
	char *line;
	t_last t;

	if (signal(SIGQUIT, ft_handler_ctrl_c) == SIG_ERR || (signal(SIGINT, ft_handler_ctrl_c) == SIG_ERR))
		return (1);
	t.status = ft_status(0, 1337);
	line = readline("minishell$ ");
	if (line == NULL)
			(ft_free_list(&str, NULL), free(line), printf("exit\n"), exit(ft_status(0, 1)));
	if (ft_strlen(line) > 0)
		add_history(line);
	line = ft_add_space_to_command(line);
	ft_put(line, &str);
	t_status *status = malloc(sizeof(t_status)); 
	status->status = ft_status(0, 1);
	t.line = line;
	ft_give_token(str, status);
	ft_is_buil(str);
	main_utils(str, &t, status, mini_env);
	free(line);
	return (0);
}

int main(int ac, char **av, char **env)
{
	t_line 		*str;
	t_last		t;
	t_holder	*tmp;
	t_env		*mini_env;
	struct termios    attr;

	mini_env = NULL;
	str = NULL;
	tmp = NULL;
    tcgetattr(STDIN_FILENO, &attr);
	attr.c_lflag = ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &attr);
	t.status = ft_status(0, 1337);
    if (env[0])
        fiLL_env(&mini_env, env);
    else
        fill_null_env(&mini_env);
	while (1)
	{
		if (main_utils_1(str, mini_env))
			perror("signal");
		tcsetattr(STDIN_FILENO, TCSANOW, &attr);
	}
}
