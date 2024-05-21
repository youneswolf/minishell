/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:51:57 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/21 14:18:43 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include <stdlib.h>
#include <sys/signal.h>


char *get_status_str(char *str, int i, int status_int)
{
    char *status_str_pre;
    char *status_str_after;
    char *status;
	if (status_int == 1337)
    	status = ft_itoa(ft_status(0, 1337));
	else
	 	status = ft_itoa(status_int);
    status_str_pre = ft_sub_str(str, 0, i - 1, 0);
    if (!status_str_pre)
        perror("malloc_error");
    status_str_after = ft_sub_str(str, i + 2, ft_strlen(str) - i - 2, 0);
    if (!status_str_after)
        perror("malloc_error");
    status = ft_strjoin(status_str_pre, status, 2);
    status = ft_strjoin(status, status_str_after, 2);
    free(str);
    return (status);
}
char *put_status_in_str(char *str, int status_int)
{
    int    i;
    i = 0;
    while (str[i])
    {
        if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
        {
            str = get_status_str(str, i+1, status_int);
        }
        i++;
    }
    return (str);
}
// struct termios    attr;

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
	while (str && str[i])
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
	int 	i;
	char 	*new_line;
	int		count;
	int		quote;

	(1) && (i = 0, count = 0, quote = 0); 
	while (str && str[i] != '\0')
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

char	*find_path(t_env *env)
{
	char	*dest = NULL;
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
	if (!path)
		return(NULL);
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

int is_slash(char *str)
{
    int    i;

    i = 0;
    while (str && str[i])
    {
        if (str[i] == '/')
            return (1);
        i++;
    }
    return (0);
}
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
int is_dir(char *path)
{
	struct stat path_stat;
    if (stat(path, &path_stat) == 0)
	{
    if (S_ISDIR(path_stat.st_mode))
	{
        return (1);
    }
	}
    return (0);
}
// void  exec_cmd(t_holder *holder, t_env *env, int pipe_fd[2], int i, int j, int k, t_last *status)
// {
//     char *path;
//     char **array;

//     // if (pipe(pipe_fd) == -1)
//     //     perror("pipe");
//     // if (holder->out[j] && holder->out[j] == -7)
//     //     exit(1);
//     // else if ((holder->in[i] && holder->in[i] == -7 )||( holder->ap[k] && holder->ap[k] == -7))
//     //     exit(1);
// 	status->status = 0;
//     if (i >= 0 && j < 1024 && holder->in[i] != -42 && holder->in[i] != -1)
//     {
//         redirect_input(holder->in[i]);
//     }
//     if (j >= 0 && j < 1024 && holder->out[j] != -42 && holder->out[j] != -1)
//     {
//         while (holder->out[j] != -42)
//             j++;
//         redirect_output(holder->out[j-1]);
//     }
//     if (k >= 0 && k < 1024 && holder->ap[k] != -42 && holder->ap[k] != -1)
//     {
//         while (holder->ap[k] != -42)
//             k++;
//         redirect_append(holder->ap[k-1]);
//     }
//     else if (holder->next)
//     {
//         dup2(pipe_fd[1], STDOUT_FILENO);
//         close(pipe_fd[0]);
//         close(pipe_fd[1]);
//     }
//     if (is_slash(holder->args[0]))
//     {
// 	if (is_dir(holder->args[0]))
// 	{
// 		ft_putstr_fd("bash: ",2);
// 		ft_putstr_fd(holder->args[0],2);
// 		ft_putstr_fd(" is a directory\n",2);
// 		status->status = 126;
// 		exit(126);
// 	}
//     if (!access(holder->args[0], X_OK))
//     {
//         path = holder->args[0];
//     }
// 	else if (!access(holder->args[0] ,F_OK))
// 	{
// 		if (access(holder->args[0], X_OK))
// 		{
// 			ft_putstr_fd("bash ",2);
// 			ft_putstr_fd(holder->args[0],2);
// 			ft_putstr_fd(" Permission denied\n",2);
// 			status->status = 126;
// 			exit(126);
// 		}
// 	}
//     else
//         (printf("bash: %s: No such file or directory\n",holder->args[0]), exit(127));
//     }
//     else
//         path = get_path(env, holder->args[0]);
//     if (!path)
//     {
//         printf("bash: %s: command not found\n", holder->args[0]);
// 		status->status= 127;
//         exit(127);
//     }
//     array = ft_put_env_string(array, env);
//     execve(path, holder->args, array);
//     ft_free_2d(array);
//     exit(1);
// }

void cmd_file_stat(t_holder *holder, char **path)
{
	if (is_dir(holder->args[0]))
    {
        ft_putstr_fd("bash: ",2);
        ft_putstr_fd(holder->args[0],2);
        ft_putstr_fd(" is a directory\n",2);
        exit(126);
    }
    if (!access(holder->args[0], X_OK))
    {
        *path = holder->args[0];
    }
    else if (!access(holder->args[0] ,F_OK))
    {
        if (access(holder->args[0], X_OK))
        {
            ft_putstr_fd("bash ",2);
            ft_putstr_fd(holder->args[0],2);
            ft_putstr_fd(" Permission denied\n",2);
            exit(126);
        }
	}
	 else
        (printf("bash: %s: No such file or directory\n",holder->args[0]), exit(127));
}

void cmd_null_path(char *path, t_holder *holder)
{
 if (!path)
    {
        ft_putstr_fd("bash ",2);
        ft_putstr_fd(holder->args[0],2);
        ft_putstr_fd(": command not found\n",2);
        exit(127);
    }
}
void init_vars_cmd(t_execution *vars)
{
	vars->i--;
	vars->k--;
	vars->j--;
}

void cmd_piping(int pipe_fd[2])
{
 	dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
}
void redirection_cmd(t_holder *holder , t_execution *vars, int pipe_fd[2])
{
	init_vars_cmd(vars);
	if (vars->i >= 0 && vars->i < 1024 && holder->in[vars->i] != -42 && holder->in[vars->i] != -1)
    {
		while (holder->in[vars->i] != -42)
			vars->i++;
        redirect_input(holder->in[vars->i-1]);
    }
     if (vars->j  >= 0 && vars->j < 1024 && holder->out[vars->j] != -42 && holder->out[vars->j] != -1)
    {
        while (holder->out[vars->j] != -42)
            vars->j++;
        redirect_output(holder->out[vars->j-1]);
    }
    if (vars->k >= 0 && vars->k < 1024 && holder->ap[vars->k] != -42 && holder->ap[vars->k] != -1)
    {
        while (holder->ap[vars->k] != -42)
            vars->k++;
        redirect_append(holder->ap[vars->k-1]);
    }
    else if (holder->next)
		cmd_piping(pipe_fd);
}

void  exec_cmd(t_holder *holder, t_env *env, int pipe_fd[2], t_execution *vars)
{
    char *path;
    char **array;

    redirection_cmd(holder, vars, pipe_fd);
    if (is_slash(holder->args[0]))
		cmd_file_stat(holder, &path);
    else
        path = get_path(env, holder->args[0]);
	cmd_null_path(path, holder);
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
char *ft_remove_dollar(char *str)
{
    int i = 1;
    char *new_str;

    if ((str && str[0] == '$') && (str[1] && str[1] == 39 || str[1] && str[1] == 34))
    {
        new_str = malloc(ft_strlen(str));
        while (str && str[i])
        {
            new_str[i-1] = str[i];
            i++;
        }
        new_str[i-1] = '\0';
        free(str);
    return (new_str);
    }
    return (str);

}

void here_doc_line(char *line, int pipe_fd[2], t_env **env, int i)
{
	if (if_dollar(line) && !i && !ft_strnstr(line, "$?", ft_strlen(line)))
        	line = handle_expand_here(line, env);
		else if (ft_strnstr(line, "$?", ft_strlen(line)))
			line = put_status_in_str(line, 1337);
        write(pipe_fd[1], line, ft_strlen(line));
        write(pipe_fd[1], "\n", 1);
        free(line);
}

void ft_here_doc(char *lim, int pipe_fd[2], t_holder *tmp, t_env **env, int origin_in)
{
    char    *line;
    char    *str;
    int        i;

	i = 42;
    line = readline("here_doc> ");
	if (!line)
		exit(1);
    i = if_dollar(lim);
    if (i == 1)
        lim = ft_remove_dollar(lim);
    i = 42;
    i = is_quote(lim);
    if (i == 1)
        lim = ft_remove_here(lim);
    while (ft_strncmp(lim, line, ft_strlen(lim))
        || ft_strlen(line) != ft_strlen(lim))
    {
		here_doc_line(line, pipe_fd, env, i);
		line = readline("here_doc> ");
        if (!line)
            (exit(1));
    }
    free(line);
    free(lim);
    exit(1);
}

int here_doc_exec(t_execution *vars ,t_env *env)
{
	// status = ft_status(0, 1337);
	// printf("%d\n",status);
	while (vars->tmp->her_doc[vars->n])
	{
		dup2(vars->origin_in, STDIN_FILENO);
		// if (vars->n > 0)
			pipe(vars->pipe_fd);
		vars->pid = fork();
		if (!vars->pid)
		{
			signal(SIGINT, heredoc);
			signal(SIGQUIT, &ft_f);
			ft_here_doc(vars->tmp->her_doc[vars->n],vars-> pipe_fd, vars->tmp, &env, vars->origin_in);
		}
		else
		{
			waitpid(vars->pid, &vars->child_stat, 0);
			if (WIFSIGNALED(vars->child_stat) && WTERMSIG(vars->child_stat) == SIGINT)
			{
				break ;
			}
			if (WIFEXITED(vars->child_stat))
			{
				int exit_status = WEXITSTATUS(vars->child_stat);
				if (exit_status == 100)
					return (write(1, "\n", 1), 500);
				if (exit_status == 255)
				{
					vars->tmp = vars->tmp->next;
					break;
				}
			}
			// break;
			close(vars->pipe_fd[1]);
			if (vars->tmp->cmd)
			{
				if (dup2(vars->pipe_fd[0], STDIN_FILENO) == -1)
					(perror("dup2 doc"));
				close(vars->pipe_fd[0]);
				// pipe(vars->pipe_fd);
			}
			else
			{
				close(vars->pipe_fd[1]);
				dup2(vars->origin_in, STDIN_FILENO);
				pipe(vars->pipe_fd);
			}
			}
			vars->n++;
		}
		// if (!isatty(STDIN_FILENO))
		// 	open(STDIN_FILENO, O_CREAT);
		return (0);
}

// void here_doc_exec_1(t_execution *vars ,t_env *env)
// {
// 	while (vars->tmp->her_doc[vars->n])
// 	{
// 		dup2(vars->origin_in, STDIN_FILENO);
// 		// if (vars->n > 0)
// 			pipe(vars->pipe_fd);
// 		vars->pid = fork();
// 		if (!vars->pid)
// 		{
// 			signal(SIGINT, SIG_DFL);
// 			signal(SIGQUIT, &ft_f);
// 			ft_here_doc(vars->tmp->her_doc[vars->n],vars-> pipe_fd, vars->tmp, &env, vars->origin_in);
// 		}
// 		else
// 		{
// 			waitpid(vars->pid, &vars->child_stat, 0);
// 			if (WIFSIGNALED(vars->child_stat) && WTERMSIG(vars->child_stat) == SIGINT)
// 				break ;
// 			if (WIFEXITED(vars->child_stat))
// 			{
// 				int exit_status = WEXITSTATUS(vars->child_stat);
// 				if (exit_status == 255)
// 				{
// 					vars->tmp = vars->tmp->next;
// 					break;
// 				}
// 			}
// 			close(vars->pipe_fd[1]);
// 			if (vars->tmp->cmd)
// 			{
// 				if (dup2(vars->pipe_fd[0], STDIN_FILENO) == -1)
// 					(perror("dup2 doc"));
// 				close(vars->pipe_fd[0]);
// 				// pipe(vars->pipe_fd);
// 			}
// 			else
// 			{
// 				close(vars->pipe_fd[1]);
// 				dup2(vars->origin_in, STDIN_FILENO);
// 				// pipe(vars->pipe_fd);
// 			}
// 			}
// 			vars->n++;
// 		}
// }

void built_in_exec(t_execution *vars, t_env *env, t_last *status)
{
	// status->status = ft_status(0, 11);
	// printf("=={%d}==\n", status->status);
	int fd;
	(vars->i = 0, vars->j = 0, vars->k = 0);
	if (vars->tmp->in[vars->i] != -42 && vars->tmp->in[vars->i] != -1)
		vars->i++;
	if (vars->tmp->out[vars->j] != -42 && vars->tmp->out[vars->j] != -1)
		vars->j++;
	if (vars->tmp->ap[vars->k] != -42 && vars->tmp->ap[vars->k] != -1)
		vars->k++;
	// if (vars->tmp->in[vars->i-1] >= 0 && vars->tmp->in[vars->i-1] < 1024 && vars->tmp->in[vars->i-1] != -42 && vars->tmp->in[vars->i-1] != -1)
	// {
	// 	redirect_input(vars->tmp->in[vars->i-2]);
	// }
	else if (vars->j != 0 && vars->tmp->out[vars->j-1] >= 0 && vars->tmp->in[vars->j-1] < 1024 && vars->tmp->out[vars->j-1] != -42 && vars->tmp->out[vars->j-1] != -1)
	{
		while (vars->tmp->out[vars->j-1] != -42)
			vars->j++;
		redirect_output(vars->tmp->out[vars->j-2]);
	}
	else if (vars->k != 0 && vars->tmp->ap[vars->k-1] >= 0 && vars->tmp->in[vars->k-1] < 1024 && vars->tmp->ap[vars->k-1] != -42 && vars->tmp->ap[vars->k-1] != -1)
	{
	while (vars->k != 0 && vars->tmp->ap[vars->k-1] != -42)
				vars->k++;
		redirect_append(vars->tmp->ap[vars->k-2]);
	}
	if (vars->tmp->next)
	{
		dup2(vars->pipe_fd[1], STDOUT_FILENO);
		// close(vars->pipe_fd[0]);
		// close(vars->pipe_fd[1]);
	}
	if (!ft_strcmp_asd(vars->tmp->args_built_in[0], "export"))
		exec_export(&vars->tmp, &env);
	else if (!ft_strcmp_asd(vars->tmp->args_built_in[0], "echo"))
	{
		exec_echo(vars->tmp, status);
	}
	else if (!ft_strcmp_asd(vars->tmp->args_built_in[0], "unset"))
		exec_unset(&env, vars->tmp);
	else if (!ft_strcmp_asd(vars->tmp->args_built_in[0], "env"))
		exec_env(&env);
	else if (!ft_strcmp_asd(vars->tmp->args_built_in[0], "exit"))
	{
		ft_exit(vars->tmp);
	}
	else if (!ft_strcmp_asd(vars->tmp->args_built_in[0], "pwd"))
	{
		ft_pwd(env);
	}
	else if (!ft_strcmp_asd(vars->tmp->args_built_in[0], "cd"))
	{
		if (vars->tmp->args_built_in[1])
			ft_cd(vars->tmp->args_built_in[1], &env);
	}
	status->status = ft_status(0, 1);
	dup2(vars->origin_out, STDOUT_FILENO);
}

int    execution_cmd(t_execution *vars, t_env *env, t_last *status)
{
    if (vars->tmp->in[vars->i] != -42 && vars->tmp->in[vars->i] != -1)
        vars->i++;
    if (vars->tmp->out[vars->j] != -42 && vars->tmp->out[vars->j] != -1)
        vars->j++;
    if (vars->tmp->ap[vars->k] != -42 && vars->tmp->ap[vars->k] != -1)
        vars->k++;
    vars->pid = fork();
    if (vars->pid == -1)
    {
        //  printf("minishell: fork: Resource temporarily unavailable\n");
        return(0) ;
    }
    if (!vars->pid)
    {
        exec_cmd(vars->tmp, env, vars->pipe_fd,vars);
    }
	// while(vars->tmp->in[vars->i-1] != -42)
	// {
    // 	close(vars->tmp->in[vars->i-1]);
	// 	vars->i++;
	// }
	// while(vars->tmp->out[vars->j-1] != -42)
	// {
    // 	 close(vars->tmp->out[vars->j-1]);
	// 	vars->j++;
	// }
	// while(close(vars->tmp->ap[vars->k-1]) != -42)
	// {
   	//  close(vars->tmp->ap[vars->k-1]);
	// 	vars->k++;
	// }
    return (1);
}
void initial_vars(t_execution *vars, t_holder **holder)
{
	(vars->i = 0, vars->j = 0, vars->k = 0, vars->n = 0, vars->wait_i = 0);
	vars->tmp = *holder;
	vars->origin_in = dup(STDIN_FILENO);
	vars->origin_out = dup(STDOUT_FILENO);
}
void piping(t_execution *vars)
{
	close (vars->pipe_fd[1]);
	dup2 (vars->pipe_fd[0], STDIN_FILENO);
	close(vars->pipe_fd[0]); 
}
void cleaning_execution(t_execution *vars, t_holder **holder)
{
	dup2(vars->origin_in, STDIN_FILENO);
	close(vars->origin_in);
    close(vars->origin_out);
	if (vars->pipe_fd[0])
		close(vars->pipe_fd[0]);
	ft_free_holder(holder);	
}

int command_first_exec(t_execution *vars, t_env *env, t_last *status)
{
	if (!execution_cmd(vars, env,status))
		{
			printf("minishell: fork: Resource temporarily unavailable\n");
			return (0);
		}
	return (1);
}

void after_exec(t_holder **holder , t_execution *vars, t_last *status)
{
	status->status = ft_status(0, 1);
	waitpid(vars->pid, &status->status, 0);
	if (WIFEXITED(status->status)) {
		status->status = WEXITSTATUS(status->status);
		ft_status(1, status->status);
	}
	else if (WIFSIGNALED(status->status) && (WTERMSIG(status->status) == SIGINT ||  WTERMSIG(status->status) == SIGQUIT))
	{
		if (WTERMSIG(status->status) == SIGQUIT)
		{
			printf("Quit: 3\n");
			ft_status(1, 131);
		}
		if (WTERMSIG(status->status) == SIGINT)
		{
			ft_status(1, 130);
		}
	}
	while (waitpid(-1, 0, 0) != -1);
	cleaning_execution(vars, holder);
}

void execution(t_holder **holder ,t_env *env, t_last *status)
{
	t_execution vars;
	initial_vars(&vars, holder);
	int pid;
	while (vars.tmp)
	{
		vars.wait_i = 0;
		// (vars.i = 0, vars.j = 0, vars.k = 0, vars.n = 0, vars.wait_i = 0);
		pipe(vars.pipe_fd);
		if (vars.tmp->her_doc[vars.n])
			here_doc_exec(&vars, env);
		if ((vars.tmp->cmd_built_in && vars.tmp->file_out[vars.j]) || vars.tmp->cmd_built_in)
			built_in_exec(&vars, env, status);
		if (vars.tmp && vars.tmp->cmd || vars.tmp->file_out[vars.j] ||vars.tmp->args[0] && vars.tmp->args[0][0])
		{
			if(!command_first_exec(&vars, env, status))
				break;
		}
		piping(&vars);
		vars.tmp = vars.tmp->next;
	}
	after_exec(holder, &vars, status);
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
		if (f_strcmp(checker[i], str) && ft_strlen(checker[i]) == ft_strlen(str))
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
		if ((tmp->token == CMD) && ft_cmp_built_in(tmp->str) == 1)
			tmp->is_it_built_in = 1;
		tmp = tmp->next;
	}
}

void	ft_print_tokens(t_line *node, t_status *status)
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
		printf("{%s} index\n", head->str);
		head = head->next;
	}
}

int	ft_handle_issue_herdoc_utils(t_line *tmp, char *s1)
{
	if (!ft_strcmp(s1, tmp->next->str))
	{
		if (tmp->next->str[0] == '$')
		{
			tmp->deja = 1;
			tmp->next->str = ft_substr1(tmp->next->str, 1, ft_strlen(tmp->next->str), 1);
		}
		free(s1);
		return (0);
	}
	return (1);
}

void	ft_handle_issue_herdoc(t_line *str)
{
	t_line *tmp;
	char	*s1;

	tmp = str;
	while (tmp)
	{
		if (tmp->token == HERDOC && tmp->next && tmp->next->token == DELIMITER)
		{
			if (tmp->next->str[0] == '$')
				return ;
			s1 = ft_strdup(tmp->next->str);
			tmp->next->str = ft_remove3(tmp->next->str);
			if ((s1[0] == '\'' || s1[0] == '\"') && s1[1] == '$')
			{
				free (s1);
				return ;
			}
			else if (!ft_handle_issue_herdoc_utils(tmp, s1))
				return ;
		}
		tmp = tmp->next;
	}
}

void	ft_set_token_to_none(t_line *str)
{
	t_line	*tmp;

	tmp = str;
	while (tmp)
	{
		tmp->token = NONE;
		tmp = tmp->next;
	}
}

void	ft_skip_empty_expand_utils(t_line *head, t_line *previous, t_line *tmp)
{
	if (head)
	{
		while (head)
		{
			if (head && head->flag == 1 && head->str[0] == '\0' && head->token != OUT_FILE
				&& head->token != IN_FILE && head->token != APPEND
				&& head->token != DELIMITER)
			{
				while (head && head->flag == 1 && !head->str[0])
				{
					tmp = head;
					head = head->next;
					free(tmp->str);
					free(tmp->status1);
					free(tmp);
				}
				previous->next = head;
			}
			if (head)
			{
				previous = head;
				head = head->next;
			}
		}
	}
}

void	ft_skip_empty_expand(t_line **node)
{
	t_line	*head;
	t_line	*tmp;
	t_line	*previous;

	if ((*node) && (*node)->token != OUT_FILE && (*node)->token != IN_FILE && (*node)->token != APPEND
		&& (*node)->token != DELIMITER && (*node)->flag == 1 && !(*node)->str[0])
	{
		previous = (*node);
		(*node) = (*node)->next;
		free(previous->str);
		free(previous->status1);
		free(previous);
		while ((*node) && (*node)->flag == 1 && !(*node)->str[0])
		{
			previous = (*node);
			(*node) = (*node)->next;
			free(previous->str);
			free(previous->status1);
			free(previous);
		}
	}
	head = *node;
	previous = *node;
	ft_skip_empty_expand_utils(head, previous, tmp);
}

int is_between_quotes(char *str)
{
	int i = 0;
	if (str && str[0] == 34 && str[1] && str[1] != 34)
	{
	while (str && str[i])
	{
		i++;
	}
	if (str[i - 1] == 34)
		return (1);
	}
	return (0);
}
// void	leaks()
// {
// 	fclose(gfp);
// 	system("leaks minishell");
// 	usleep(1000 * 100 *10000);
// }

void	ft_print_holder(t_holder *tmp)
{
	t_holder *tmp1 = tmp;
	while (tmp1)
	{
		int kk = 0;
		int zz = 0;
		if (tmp1->cmd)
			printf("holder cmd %s\n", tmp1->cmd);
		if (tmp1->cmd_built_in)
			printf("holder cmd %s\n", tmp1->cmd_built_in);
		while (tmp1->args_built_in[kk])
		{
			printf("holder args_buit_in %s\n", tmp1->args_built_in[kk]);
			kk++;
		}
		kk = 0;
		while (tmp1->args[kk])
		{
			printf("holder args %s\n", tmp1->args[kk]);
			kk++;
		}
		while (tmp1->file_out[zz])
		{
			printf("holder outfile %s\n", tmp1->file_out[zz]);
			zz++;
		}
		tmp1 = tmp1->next;
	}
}

int	ft_status(int a, int status)
{
	static	int	s;

	if (a == 1)
		s = status;
	return (s);
}

static    int    int_len(int n)
{
    int        i;
    long    num;

    num = n;
    i = 0;
    if (num < 0)
    {
        num *= -1;
        i++;
    }
    while (num > 0)
    {
        num = num / 10;
        i++;
    }
    return (i);
}

static    char    *conv(int n)
{
    int        i;
    char    *a;
    long    num;

    if (n == 0)
        return (ft_strdup("0"));
    i = int_len(n);
    num = n;
    a = (char *)malloc(sizeof(char) * (i + 1));
    if (!a)
        return (NULL);
    a[i--] = '\0';
    if (num < 0)
    {
        num *= -1;
        a[0] = '-';
    }
    while (num > 0)
    {
        a[i] = num % 10 + 48;
        num = num / 10;
        i--;
    }
    return (a);
}

char    *ft_itoa(int n)
{
    char    *str;

    str = conv(n);
    return (str);
}

char    *ft_strnstr(const char *haystack, const char *needle, size_t len)
{
    size_t    i;
    size_t    j;
    char    *src;

    src = (char *)haystack;
    j = 0;
    i = 0;
    if (needle[0] == '\0')
    {
        return (src);
    }
    while (i < len && haystack[i])
    {
        j = 0;
        while (haystack[i + j] == needle[j] && (i + j) < len)
        {
            if (needle[j + 1] == '\0')
            {
                return (&src[i]);
            }
            j++;
        }
        i++;
    }
    return (NULL);
}

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
			execution(&tmp, mini_env, t);
	}
}

int	main_utils_1(t_line *str, t_env *mini_env)
{
	char *line;
	t_last t;

	if (signal(SIGQUIT, ft_handler_ctrl_c) == SIG_ERR || (signal(SIGINT, ft_handler_ctrl_c) == SIG_ERR))
		return (perror("signal"), 1);
	t.status = ft_status(0, 1337);
	line = readline("minishell$ ");
	if (line == NULL)
			(ft_free_list(&str, NULL), free(line), printf("exit\n"), exit(ft_status(0, 1)));
	if (ft_strlen(line) > 0)
		add_history(line);
	line = ft_add_space_to_command(line);
	ft_put(line, &str);
	t_status *status = malloc(sizeof(t_status)); 
	// status->node = str;
	status->status = 1337;
	t.line = line;
	ft_give_token(str, status);
	ft_is_buil(str);
	main_utils(str, &t, status, mini_env);
	str = NULL;
	free(line);
	return (0);
}

int main(int ac, char **av, char **env) // QUITE , exit status CTLC 
{
	// gfp = fopen("leaks.t", "w");
	// atexit(leaks);
	
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
