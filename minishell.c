/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:51:57 by ybellakr          #+#    #+#             */
/*   Updated: 2024/04/01 00:29:50 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

int is_there_exit(char *str)
{
	int i, j;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'e' && str[i+1] == 'x' && str[i+2] == 'i' && str[i+3] == 't')
			return (1);
		i++;
	}
	return (0);
}

int ft_strcmp(char *str, char *str1)
{
	int i;

	i = 0;
	while (str[i] && str1[i])
	{
		if (str[i] != str1[i])
			return (0);
		i++;
	}
	return (1);
}

void	ft_add_space_utils(char *new_line, char *str, int quote, int i, int j)
{
	int	flag;

	flag = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			(1) && (flag = 1, quote = str[i]);
		if (flag == 0 && ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<')))
		{
			(1) && ( new_line[j] = ' ', new_line[j + 1] = str[i]);
			(1) && (new_line[j + 2] = str[i], new_line[j + 3] = ' ');
			(1) && (j = j + 3, i++);
		}
		else if (flag == 0 && (str[i] == '|' || str[i] == '>' || str[i] == '<'))
		{
			(1) && (new_line[j] = ' ', new_line[j + 1] = str[i]);
			(1) && (new_line[j + 2] = ' ', j = j + 2);
		}
		else
			new_line[j] = str[i];
		(1) && (i++, j++);
		if (str[i] && str[i] == quote)
			(1) && (new_line[j] = str[i], i++, j++, flag = 0, quote = 0);
	}
	// return (new_line[j] = '\0', new_line);
	new_line[j] = '\0';
}

char    *ft_add_space_to_command(char *str)
{
	int i, count, quote = 0;
	char *new_line;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|' || str[i] == '>' || str[i] == '<'
		|| (str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
				count++;
			i++;
	}
	new_line = malloc(i + 1 + count * 2);
	if (!new_line)
		return (NULL);
		// return (free(str), perror("malloc"), NULL);
	i = 0;
	count = 0;
	ft_add_space_utils(new_line, str, quote, i, count);
	// return (free(str), new_line);
	return (new_line);
}

void    ft_ctr(int sig)
{
	(void)sig;
	printf(RED"\nminishell$ "RESET);
	return ;
}

int		ft_cmp_built_in(char *str)
{
	int	i;
	char **checker;

	checker = malloc(8 * sizeof(char *));
	if (!checker)
		return (perror("malloc"), 0);
	checker[0] = ft_strdup("echo");
	checker[1] = ft_strdup("cd");
	checker[2] = ft_strdup("pwd");
	checker[3] = ft_strdup("export");
	checker[4] = ft_strdup("unset");
	checker[5] = ft_strdup("env");
	checker[6] = ft_strdup("exit");
	checker[7] = NULL;
	i = 0;
	while (checker[i])
	{
		if (f_strcmp(checker[i], str))
			return (1);
			// return (ft_free_2d(checker), 1);
		i++;
	}
	return (0);
}

void leaks()
{
    fclose(gfp);
    system("leaks minishell");
    usleep(1000 * 100 *10000);
}

int main(int    ac, char **av, char **env)
{
	t_line  *str;
	int     i = 0;
	char    *line;
	char    *exp;
	t_holder* tmp;

	gfp = fopen("leaks", "w");
	atexit(leaks);

	str = NULL;
	tmp = NULL;
	// t_envi  *mini_env;
	rl_catch_signals = 0;
    if (signal(SIGINT, ft_handler_ctrl_c) == SIG_ERR ||
		signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
        perror("signal");
        return 1;
    }
	// t_env *mini_env = ft_get_env(env);
	while (1)
	{
		line = readline(RED"minishell$ "RESET);
		if (!SIGQUIT || line == NULL || is_there_exit(line))
				(ft_free_list(str), free(line), printf("exit!\n"), exit(0));
		if (ft_strlen(line) > 0)
			add_history(line);
		line = ft_add_space_to_command(line);
		ft_put(line, &str);
		ft_give_token(str);
		if (!ft_syntax(str))
			printf("failed\n");
		// ft_expand_argument(mini_env, &str);
		ft_remove_quote(&str, line);
		// ft_cd(line , mini_env);
		// tmp = ft_create_holder_node(str, line);
		// int i = 0;
		// while (tmp)
		// {
		// 	printf("test\n");
		// 	printf("%d\n", tmp->out[i]);
		// 	i++;
		// 	tmp = tmp->next;
		// }
		// ft_exec_built_ins(*tmp, mini_env);
		// ft_checking_files(tmp);
		while (str)
		{
			if (str->token == CMD)
				printf(BLUE"[%s]"RESET, "CMD");
			else if (str->token == ARGS)
				printf(YELLOW"[%s]"RESET, "ARGS");
			else if (str->token == PIPE)
				printf(MAGENTA"[%s]"RESET, "PIPE");
			else if (str->token == IN_REDIR)
				printf(CYAN"[%s]"RESET, "IN_REDIR");
			else if (str->token == OUT_REDIR)
				printf(WHT"[%s]"RESET, "OUT_REDIR");
			else if (str->token == HERDOC)
				printf(GREEN"[%s]"RESET, "HERDOC");
			else if (str->token == OUT_FILE)
				printf(MAGENTA"[%s]"RESET, "OUT_FILE");
			else if (str->token == IN_FILE)
				printf(YELLOW"[%s]"RESET, "IN_FILE");
			else if (str->token == FILE)
				printf(YELLOW"[%s]"RESET, "FILE");
			else if (str->token == APPEND)
				printf(YELLOW"[%s]"RESET, "APPEND");
			else if (str->token == DELIMITER)
				printf(YELLOW"[%s]"RESET, "DELIMITER");
			printf("--%s--", str->str);
			str = str->next;
		}
		printf("\n");
		// free(line);
	}
}