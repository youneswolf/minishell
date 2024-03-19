/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:51:57 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/19 04:59:08 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_line	*ft_lstnew(char *str)
// {
// 	t_line	*new;

// 	new = (t_line *)malloc(sizeof(t_line));
//     new->str = strdup(str);
// 	if (!new)
// 		return (NULL);
// 	new->next = NULL;
// 	return (new);
// }

// void	add_list(t_line **lst, char *str)
// {
// 	t_line	*new;
// 	t_line	*temp;

// 	new = ft_lstnew(str);
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		new->next = NULL;
// 	}
// 	else
// 	{
// 		temp = *lst;
// 		while (temp->next != NULL)
// 		{
// 			temp = temp->next;
// 		}
// 		temp->next = new;
// 	}
// }


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

char    *ft_add_space_to_command(char *str)
{
	int i, count, j;
	char *new_line;

	i = 0;
	count = 0;
	j = 0;
	
	while (str[i] != '\0')
	{
		if (str[i] == '|' || str[i] == '>' || str[i] == '<'
		|| (str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
			 count++;
		i++;
	}
	new_line = malloc(i + 1 + count * 2);
	if (!new_line)
		return (perror("malloc"), NULL);
	i = 0;
	while (str[i])
	{
		if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
		{
			new_line[j] = ' ';
			new_line[j + 1] = str[i];
			new_line[j + 2] = str[i];
			new_line[j + 3] = ' ';
			j = j + 3;
			i++;
		}
		else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			new_line[j] = ' ';
			new_line[j + 1] = str[i];
			new_line[j + 2] = ' ';
			j = j + 2;
		}
		else
			new_line[j] = str[i];
		j++;
		i++;
	}
	new_line[j] = '\0';
	return (new_line);
}

void    ft_ctr(int sig)
{
	(void)sig;
	printf(RED"\nminishell$ "RESET);
	return ;
}

char	*find_path(t_env *env)
{
	char	*dest;
	t_env *tmp;

	tmp = env;
	dest = NULL;
	while (!dest)
	{
		dest = strnstr(tmp->value, "PATH", 4);
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
	// free(static_str);
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
	return (NULL);
}
void  exec_cmd(t_holder *holder, t_env *env, int pipe_fd[2], int i, int j, int k)
{
	char *path;
	// if (pipe(pipe_fd) == -1)
	// 	perror("pipe");
	if (holder->in[i] != -42 && holder->in[i] != -1)
	{
		redirect_input(holder->in[i]);
	}
	if (holder->out[j] != -42 && holder->out[j] != -1)
	{
		redirect_output(holder->out[j]);
	}
	// else if (holder->ap[k] != -42 && holder->ap[k] != -1)
	// {
	// 	printf("aaaaaaaa%d\n",holder->ap[k]);
	// 	redirect_append(holder->ap[k]);
	// }
	else if (holder->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	// char a[1024];
	// int ss = read (0 ,a, 100);
	// printf("%d\n",ss);
	// write(1,a,ss);
	// printf("%s\n",holder->args[0]);
	if (!access(holder->args[0], X_OK))
		path = holder->args[0];
	else
		path = get_path(env, holder->cmd);
	execve(path, holder->args, NULL);
	perror("execve error");
	exit(1);
}
void execution(t_holder **holder ,t_env **env)
{
	t_holder *tmp;
	int pipe_fd[2];
	int i ,j , k;
	(i = 0, j = 0, k = 0);
	int pid;
	tmp = *holder;
	int origin_in = dup(STDIN_FILENO);
	// while (tmp)
	// {
	// 	if (tmp->cmd)
	// 	{
	// 		if (tmp->in[i] != -42 && tmp->in[i] != -1)
	// 			i++;
	// 		if (tmp->out[j] != -42 && tmp->out[i] != -1)
	// 			j++;
	// 		if (tmp->ap[k] != -42 && tmp->ap[i] != -1)
	// 			k++;
	// 		pipe(pipe_fd);
	// 		pid = fork();
	// 		if (!pid)
	// 		{
	// 			// printf("%s\n",tmp->args[0]);
	// 			exec_cmd(tmp, *env, pipe_fd,i-1,j-1,k-1);
	// 		}
	// 		else if(pid > 0)
	// 		{
	// 			close (pipe_fd[1]);
	// 			close (tmp->out[j - 1]);
	// 			close (tmp->in[i - 1]);
	// 			close (tmp->ap[k - 1]);
	// 			dup2 (pipe_fd[0], STDIN_FILENO);
	// 			close(pipe_fd[0]);
	// 		}
	// 	}
	// 	tmp = tmp->next;
	// }
	// // char a[1024];
	// // int ss = read (0 ,a, 100);
	// // write(1,a,ss);
	// tmp = *holder;
	// while (tmp)
	// {
	// 	wait (NULL);
	// 	tmp = tmp->next;
	// }
	dup2(origin_in, STDIN_FILENO);
	close(origin_in);
	close(pipe_fd[0]);
}
int main(int    ac, char **av, char **env)
{
	t_line  *str;
	int     i = 0;
	char    *line;
	char    *exp;
	t_holder* tmp;

	str = NULL;
	tmp = NULL;
	// t_envi  *mini_env;
	t_env *mini_env = ft_get_env(env);
	while (1)
	{
		line = readline(RED"minishell$ "RESET);
		if (!SIGQUIT || line == NULL || is_there_exit(line))
		{
			if (line == NULL)
				(printf("exit!\n"), exit(0));
		}
		if (ft_strlen(line) > 0)
			add_history(line);
		line = ft_add_space_to_command(line); //add space between special carahcteres like | >< ...
		str = ft_put(line); //create linked list 
		ft_give_token(str); //give token to each node
		ft_syntax(str);  //check the syntax
		ft_remove_quote(&str); //removing quotes for command and args
		// ft_expand_argument(mini_env, &str); //expand nta3 ismail
		tmp = ft_create_holder_node(str);
		ft_checking_files(tmp);
		execution(&tmp, &mini_env);
		while (str)
		{
			// if (str->token == CMD)
			// 	printf(BLUE"[%s]"RESET, "CMD");
			// else if (str->token == ARGS)
			// 	printf(YELLOW"[%s]"RESET, "ARGS");
			// else if (str->token == PIPE)
			// 	printf(MAGENTA"[%s]"RESET, "PIPE");
			// else if (str->token == IN_REDIR)
			// 	printf(CYAN"[%s]"RESET, "IN_REDIR");
			// else if (str->token == OUT_REDIR)
			// 	printf(WHT"[%s]"RESET, "OUT_REDIR");
			// else if (str->token == HERDOC)
			// 	printf(GREEN"[%s]"RESET, "HERDOC");
			// else if (str->token == OUT_FILE)
			// 	printf(MAGENTA"[%s]"RESET, "OUT_FILE");
			// else if (str->token == IN_FILE)
			// 	printf(YELLOW"[%s]"RESET, "IN_FILE");
			// else if (str->token == FILE)
			// 	printf(YELLOW"[%s]"RESET, "FILE");
			// else if (str->token == APPEND)
			// 	printf(YELLOW"[%s]"RESET, "APPEND");
			// else if (str->token == DELIMITER)
			// 	printf(YELLOW"[%s]"RESET, "DELIMITER");
			// printf("--%s--", str->str);
			str = str->next;
		}
		// printf("\n");
		free(line);
	}
}