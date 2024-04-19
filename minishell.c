/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:51:57 by ybellakr          #+#    #+#             */
/*   Updated: 2024/04/19 10:43:30 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int f_strcmp(char *str1, char *str2)
{
    int i;

    i = 0;
    while (str1 && str2 && str2[i] != '\0' && str1[i] != '\0')
    {
        if (str1[i] != str2[i])
            return (0);
        i++;
    }
    return (1);
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

// int ft_strcmp(char *str, char *str1)
// {
// 	int i;

// 	i = 0;
// 	while (str[i] && str1[i])
// 	{
// 		if (str[i] != str1[i])
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

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
		return (free(str), perror("malloc"), NULL);
		// return (NULL);
	i = 0;
	count = 0;
	ft_add_space_utils(new_line, str, quote, i, count);
	return (free(str), new_line);
	// return (new_line);
}

void    ft_ctr(int sig)
{
	(void)sig;
	printf(RED"\nminishell$ "RESET);
	return ;
}

// int		ft_cmp_built_in(char *str)
// {
// 	int	i;
// 	char **checker;

// 	checker = malloc(8 * sizeof(char *));
// 	if (!checker)
// 		return (perror("malloc"), 0);
// 	checker[0] = ft_strdup("echo");
// 	checker[1] = ft_strdup("cd");
// 	checker[2] = ft_strdup("pwd");
// 	checker[3] = ft_strdup("export");
// 	checker[4] = ft_strdup("unset");
// 	checker[5] = ft_strdup("env");
// 	checker[6] = ft_strdup("exit");
// 	checker[7] = NULL;
// 	i = 0;
// 	while (checker[i])
// 	{
// 		if (f_strcmp(checker[i], str))
// 			return (ft_free_2d(checker), 1);
// 			// return (1);
// 		i++;
// 	}
// 	return (ft_free_2d(checker), 0);
// 	// return (0);
// }


char	*find_path(t_env *env)
{
	char	*dest;
	t_env *tmp;

	tmp = env;
	dest = NULL;
	while (!dest)
	{
		dest = strnstr(tmp->env, "PATH=", 5);
		tmp = tmp->next;
	}
	return (dest);
}
char	*skip_path(char *str)
{
	char	*new_str;
	int		j;
	int		i;

	j = 0;
	i = 0;
	new_str = malloc(ft_strlen(str) - 4);
	if (!new_str)
		return (NULL);
	while (str[i] && i < 5)
		i++;
	while (str[i])
	{
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	free (str);
	return (new_str);
}
char	*ft_strjoin_path(char *static_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;
	size_t	len;

	if (!static_str && !buff)
		return (NULL);
	if (!static_str && buff)
		return (ft_strdup(buff));
	if (!buff && static_str)
		return (ft_strdup(static_str));
	len = ft_strlen(static_str);
	str = malloc(sizeof(char) * (len + ft_strlen(buff)) + 2);
	if (!str)
		exit(1);
	i = 0;
	j = 0;
	while (static_str && static_str[i] != '\0')
	{
		str[i] = static_str[i];
		i++;
	}
	str[i] = '/';
	i++;
	while (buff && buff[j] != '\0')
		str[i++] = buff[j++];
	str[i] = '\0';
	free(static_str);
	return (str);
}

char	*get_path(t_env *env, char *cmd)
{
	int		k;
	int		i;
	char	**path;

	i = -1;
	path = ft_split(find_path(env), ':');
	path[0] = skip_path(path[0]);
	while (cmd && path[++i])
	{
		path[i] = ft_strjoin_path(path[i], cmd);
	}
	i = 0;
	while (path && path[i])
	{
		if (access(path[i], X_OK) == 0)
			break ;
		free(path[i++]);
	}
	if (!path[i])
		return (NULL);
	k = i + 1;
	while (path[k] && path)
		free(path[k++]);
	return (path[i]);
}

char **ft_put_env_string(char **array, t_env *env)
{
    int        i, l;
    t_env    *tmp;
	l = 0;
    tmp = env;
    i = 0;
    while (tmp)
    {
        l++;
        tmp = tmp->next;
    }
    tmp = env;
	printf("%p",tmp);
    array = malloc((l + 1)* sizeof(char *));
    while (tmp)
    {
        array[i] = ft_strdup(tmp->env);
        i++;
        tmp = tmp->next;
    }
    array[i] = NULL;
    return (array);
}

void  exec_cmd(t_holder *holder, t_env *env, int pipe_fd[2], int i, int j, int k)
{
	char *path;
	char **array;

	// if (pipe(pipe_fd) == -1)
	// 	perror("pipe");
	if (i >= 0 && j < 1024 && holder->in[i] != -42 && holder->in[i] != -1)
	{
		redirect_input(holder->in[i]);
	}
	if (j >= 0 && j < 1024 && holder->out[j] != -42 && holder->out[j] != -1)
	{
		while (holder->out[j] != -42)
			j++;
		redirect_output(holder->out[j-1]);
	}
	if (k >= 0 && k < 1024 && holder->ap[k] != -42 && holder->ap[k] != -1)
	{
		while (holder->ap[k] != -42)
			k++;
		redirect_append(holder->ap[k-1]);
	}
	else if (holder->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}

	if (!access(holder->args[0], X_OK))
	{
		path = holder->args[0];
	}
	else
		path = get_path(env, holder->args[0]);
	if (!path)
	{
		printf("bash: %s: command not found\n", holder->args[0]);
		exit(127);
	}
	array = ft_put_env_string(array, env);
    execve(path, holder->args, array);
    ft_free_2d(array);
	exit(1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		res;

	res = 0;
	i = 0;
	while (i < n)
	{
		if (s1 && s1[i] == '\0' && s2[i] == '\0')
		{
			return (0);
		}
		if ( s1 && s2 && (unsigned char)s1[i] != (unsigned char)s2[i])
		{
			res = (unsigned char)s1[i] - (unsigned char)s2[i];
			return (res);
		}
		i++;
	}
	return (res);
}

int	ft_strcmp_asd(char *s1,  char *s2)
{
	size_t	i;
	int		res;

	res = 0;
	i = 0;
	while (s1 && s1[i])
	{
		if (s1 && s1[i] == '\0' && s2[i] == '\0')
		{
			return (0);
		}
		if ( s1 && s2 && (unsigned char)s1[i] != (unsigned char)s2[i])
		{
			res = (unsigned char)s1[i] - (unsigned char)s2[i];
			return (res);
		}
		i++;
	}
	return (res);
}
int is_quote(char *str)
{
	int i = 0;
	while (str && str[i])
	{
		if (str[i] == 39 || str[i] == 34)
			return (1);
		i++;
	}
	return (0);
}
void ft_here_doc(char *lim, int pipe_fd[2], t_holder *tmp, t_env **env, int origin_in)
{
	char	*line;
	char	*str;
	int		i = 42;
	// write(1, "here_doc> ", 11);
	// dup2(origin_in, STDIN_FILENO);
	// if (signal(SIGINT, ft_handler_ctrt_herdoc) == SIG_ERR)
    //     exit(255);
	line = readline("here_doc> ");
	i = is_quote(lim);
	if (i == 1)
	{
		lim = ft_remove_here(lim);
	}
	while (ft_strncmp(lim, line, ft_strlen(line))
		|| ft_strlen(line) != ft_strlen(lim))
	{
		// write(1, "here_doc> ", 11);
		if (if_dollar(line) && !i)
		{
			line = handle_expand_here(line, env);
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
		line = readline("here_doc> ");
		if (!line)
			exit(2) ;
	}
	free(line);
	exit(1);
}

void execution(t_holder **holder ,t_env *env)
{
	t_holder *tmp;
	int child_stat;
	int pipe_fd[2];
	int i ,j , k, n, wait_i;
	(i = 0, j = 0, k = 0, n = 0, wait_i = 0);
	int pid;
	tmp = *holder;
	int origin_in = dup(STDIN_FILENO);
	tmp = *holder;
	t_holder *doc_tmp = NULL;
	struct termios    attr;
    tcgetattr(STDIN_FILENO, &attr);
	while (tmp)
	{
		wait_i = 0;
		pipe(pipe_fd);
		if (tmp->her_doc[n])
		{
			while (tmp->her_doc[n])
			{
		dup2(origin_in, STDIN_FILENO);

			if (n > 0)
				pipe(pipe_fd);
			pid = fork();
			if (!pid)
			{
				signal(SIGINT, SIG_DFL);
				ft_here_doc(tmp->her_doc[n], pipe_fd, tmp, &env, origin_in);
			}
			else
			{
				waitpid(pid, &child_stat, 0);
				if (WIFEXITED(child_stat))
				{
        			int exit_status = WEXITSTATUS(child_stat);
					if (exit_status == 255)
					{
						tmp = tmp->next;
						break;
					}
				}
			close(pipe_fd[1]);
			if (tmp->cmd)
			{
			if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
				(perror("dup2 doc"));
			close(pipe_fd[0]);
			}
			else
			{
				close(pipe_fd[ 1]);
				dup2(pipe_fd[0], STDIN_FILENO);
				pipe(pipe_fd);
			}
			}
				n++;
			}
 		}
		if ((tmp->cmd_built_in &&tmp->file_out[j]) || (tmp->args_built_in[0] && tmp->cmd_built_in))
		{
			exec_export(&tmp, &env);
		}
		if (tmp && tmp->cmd || tmp->file_out[j] ||tmp->args[0] && tmp->args[0][0])
		{
			if (tmp->in[i] != -42 && tmp->in[i] != -1)
				i++;
			if (tmp->out[j] != -42 && tmp->out[j] != -1)
			{
				j++;
			}
			if (tmp->ap[k] != -42 && tmp->ap[k] != -1)
				k++;
			pid = fork();
			if (!pid)
			{
				exec_cmd(tmp, env, pipe_fd,i-1,j-1,k-1);
			}
		}
		close (pipe_fd[1]);
				// close (tmp->out[j - 1]);
				// close (tmp->in[i - 1]);
				// close (tmp->ap[k - 1]);
		dup2 (pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		tmp = tmp->next;
	}
	tmp = *holder;
	while (tmp)
	{
		wait (NULL);
		tmp = tmp->next;
	}
	dup2(origin_in, STDIN_FILENO);
	close(origin_in);
	if (pipe_fd[0])
		close(pipe_fd[0]);
	if (WIFSIGNALED(child_stat) && (WTERMSIG(child_stat) == SIGINT) || WTERMSIG(child_stat) == SIGQUIT)
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &attr);
    }
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

void lek()
{
	system("leaks minishell");
}

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

int main(int    ac, char **av, char **env)
{
	t_line  *str;
	int     i = 0;
	char    *line;
	char *a;
	char    *exp;
	t_holder* tmp;
	t_line *old;
	t_env *mini_env = NULL;
	str = NULL;
	tmp = NULL;
	// atexit(lek);
	rl_catch_signals = 0;
	if (signal(SIGINT, ft_handler_ctrl_c) == SIG_ERR
        || signal(SIGQUIT, ft_handler_ctrl_c) == SIG_ERR)
        return (perror("signal"), 1);
    if (env[0])
        fiLL_env(&mini_env, env);
    else
        fill_null_env(&mini_env);
	while (1)
	{
		line = readline(RED"minishell$ "RESET);
		if (!SIGQUIT || line == NULL || (is_there_exit(line) && ft_strlen(line) == 4))
				(ft_free_list(&str), free(line), printf("exit!\n"), exit(0));
		if (ft_strlen(line) > 0)
			add_history(line);
		line = ft_add_space_to_command(line); //add space between special carahcteres like | >< ...
		// if (!line)
			// str->status = 255;
		ft_put(line, &str); //create linked list 
		ft_give_token(str); //give token to each node
		ft_is_buil(str);
		if (ft_syntax(str))  //check the syntax
		{
			old = str;
			// ft_expand_argument(mini_env, &str); //expand nta3 ismail
			while (str)
			{
				if (if_dollar(str->str) && str->token != DELIMITER)
				{
					// free(str->str);
					str->str = handle_expand(str->str, &mini_env);
					str->flag = 1;
					// free(str->str);
					// ft_put(str->str, &str); //create linked list 
					// printf("str = %s\n", str->str);
					// ft_give_token(str); //give token to each node
				}
				str = str->next;
			}
			str = old;
			while (str && !str->str[0])
			{
				str = str->next;
			}
			// printf("%d\n",str->token);
			ft_remove_quote(&str, line); //removing quotes for command and args
			tmp = ft_create_holder_node(str,line);
			ft_checking_files(tmp);
			execution(&tmp, mini_env);
		}
		ft_print_tokens(str);
		ft_free_list(&str);
		str = NULL;
		free(line);
	}
}