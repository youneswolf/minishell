/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:51:57 by ybellakr          #+#    #+#             */
/*   Updated: 2024/04/06 20:25:00 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	ft_print_tokens(t_line *node)
{
	t_line *head = node;
	while (head)
	{
		if (head->token == CMD && head->str)
			printf(BLUE"[%s]"RESET, "CMD");
		else if (head->token == ARGS && head->str)
			printf(YELLOW"[%s]"RESET, "ARGS");
		else if (head->token == PIPE && head->str)
			printf(MAGENTA"[%s]"RESET, "PIPE");
		else if (head->token == IN_REDIR && head->str)
			printf(CYAN"[%s]"RESET, "IN_REDIR");
		else if (head->token == OUT_REDIR && head->str)
			printf(WHT"[%s]"RESET, "OUT_REDIR");
		else if (head->token == HERDOC && head->str)
			printf(GREEN"[%s]"RESET, "HERDOC");
		else if (head->token == OUT_FILE && head->str)
			printf(MAGENTA"[%s]"RESET, "OUT_FILE");
		else if (head->token == IN_FILE && head->str)
			printf(YELLOW"[%s]"RESET, "IN_FILE");
		else if (head->token == FILE && head->str)
			printf(YELLOW"[%s]"RESET, "FILE");
		else if (head->token == APPEND && head->str)
			printf(YELLOW"[%s]"RESET, "APPEND");
		else if (head->token == DELIMITER && head->str)
			printf(YELLOW"[%s]"RESET, "DELIMITER");
		printf("{%s}\n", head->str);
		head = head->next;
	}
	printf("\n");
}

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
	new_line[j] = '\0';
}

char    *ft_add_space_to_command(char *str)
{
	int		i;
	int		count;
	int		quote;
	char	*new_line;

	i = 0;
	count = 0;
	quote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|' || str[i] == '>' || str[i] == '<'
		|| (str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
				count++;
			i++;
	}
	new_line = malloc(i + 1 + count * 2);
	if (!new_line)
		return (free(str), perror("malloc"), NULL);
	i = 0;
	count = 0;
	ft_add_space_utils(new_line, str, quote, i, count);
	return (free(str), new_line);
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
			return (ft_free_2d(checker), 1);
		i++;
	}
	return (ft_free_2d(checker), 0);
}

// void leaks()
// {
//     fclose(gfp);
//     system("leaks minishell");
//     usleep(1000 * 100 *10000);
// }

void	ft_is_buil(t_line *str)
{
	t_line *tmp = str;

	while (tmp)
	{
		tmp->is_it_built_in = 0;
		if (tmp->token == CMD && ft_cmp_built_in(tmp->str) == 1)
			tmp->is_it_built_in = 1;
		tmp = tmp->next;
	}
	// ft_print_tokens(str);
}

int main(int    ac, char **av, char **env)
{
	t_line  *str;
	int     i = 0;
	char    *line;
	char    *exp;
	t_holder* tmp;

	// gfp = fopen("leaks", "w");
	// atexit(leaks);

	str = NULL;
	tmp = NULL;
	// str->status = 0;
	// t_envi  *mini_env;
	rl_catch_signals = 0;
    if (signal(SIGINT, ft_handler_ctrl_c) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
        return (perror("signal"), 1);
	// else
	// 	str->status = 131;
	// t_env *mini_env = ft_get_env(env);
	while (1)
	{
		line = readline(RED"minishell$ "RESET);
		if (!SIGQUIT || line == NULL || (is_there_exit(line) && ft_strlen(line) == 4))
				(ft_free_list(&str), free(line), printf("exit!\n"), exit(0));
		if (ft_strlen(line) > 0)
			add_history(line);
		line = ft_add_space_to_command(line);
		// if (!line)
		// 	str->status = 255;
		ft_put(line, &str);
		ft_give_token(str);
		ft_is_buil(str);
		if (ft_syntax(str))
		{
			// ft_expand_argument(mini_env, &str);
			ft_remove_quote(&str, line);
			// ft_cd(line , mini_env);
			tmp = ft_create_holder_node(str, line);
			int k = 0, z = 0;
			while (tmp)
			{
				if (tmp->cmd_built_in)
					printf("cmd built in {%s}\n", tmp->cmd_built_in);
				if (tmp->args_built_in[k])
				{
					while (tmp->args_built_in[k])
					{
						printf("args built in (%s)\n", tmp->args_built_in[k]);
						k++;
					}
				}
				if (tmp->args[z])
				{
					while (tmp->args[z])
					{
						printf("args in (%s)\n", tmp->args[z]);
						z++;
					}
				}
				if (tmp->cmd)
					printf("cmd %s\n", tmp->cmd);
				tmp = tmp->next;
			}
		}
		// ft_print_tokens(str);
		// else
		// 	(ft_free_list(&str),free(str), free(line));
		// int i = 0;
		// ft_exec_built_ins(*tmp, mini_env);
		// ft_checking_files(tmp);
		ft_free_list(&str);
		str = NULL;
		free(line);
	}
}