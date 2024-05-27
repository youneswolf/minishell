/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:50:26 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/27 10:18:43 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*find_path(t_env *env)
{
	char	*dest = NULL;
	t_env *tmp;

	tmp = env;
	dest = NULL;
	while (!dest)
	{
		if (tmp->deleted != 1)
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
	t_join vars;

	if (!static_str && !buff)
		return (NULL);
	if (!static_str && buff)
		return (ft_strdup(buff));
	if (!buff && static_str)
		return (ft_strdup(static_str));
	vars.len = ft_strlen(static_str);
	vars.str = malloc(sizeof(char) * (vars.len + ft_strlen(buff)) + 2);
	if (!vars.str)
		exit(1);
	vars.i = 0;
	vars.j = 0;
	while (static_str && static_str[vars.i] != '\0')
	{
		vars.str[vars.i] = static_str[vars.i];
		vars.i++;
	}
	(1) && (vars.str[vars.i] = '/', vars.i++);
	while (buff && buff[vars.j] != '\0')
		vars.str[vars.i++] = buff[vars.j++];
	vars.str[vars.i] = '\0';
	free(static_str);
	return (vars.str);
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
		path[i] = ft_strjoin_path(path[i], cmd);
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
        (ft_putstr_fd("bash: : No such file or directory\n", 2), exit(127));
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
	static int i;
	i++;
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

	array = NULL;
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
	return (42);
}
char *ft_remove_dollar(char *str)
{
    int i = 1;
    char *new_str;

	new_str = NULL;
    if ((str && str[0] == '$') && ((str[1] && str[1] == 39) || (str[1] && str[1] == 34)))
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

void ft_here_doc(char *lim, int pipe_fd[2], t_holder *atmp, t_env **env, int origin_in)
{
    char    *line;
    char    *str;
    int        i;

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
		here_doc_line(line, pipe_fd, env, i);
		line = readline("here_doc> ");
        if (!line)
            (exit(1));
    }
    free(line);
    free(lim);
    exit(1);
}
void here_piping(t_execution *vars)
{
	close(vars->pipe_fd[1]);
	dup2(vars->origin_in, STDIN_FILENO);
	close(vars->pipe_fd[0]);
}

int check_if_ctrl_c(t_execution *vars)
{
	int exit_status = WEXITSTATUS(vars->child_stat);
		if (exit_status == 100)
		{
			ft_status(1, 1);
			return (write(1, "\n", 1), 100);
		}
		if (exit_status == 255)
		{
			vars->tmp = vars->tmp->next;
			return (1);
		}

	return (0);
}
void dup2cmd_here(t_execution *vars)
{
	if (dup2(vars->pipe_fd[0], STDIN_FILENO) == -1)
					(perror("dup2 doc"));
			close(vars->pipe_fd[0]);
}

void here_doc_child(t_execution *vars, t_env *env)
{
	signal(SIGINT, heredoc);
			signal(SIGQUIT, &ft_f);
			ft_here_doc(vars->tmp->her_doc[vars->n],vars->pipe_fd, vars->tmp, &env, vars->origin_in);
}
void exec_dups_here(t_execution *vars)
{
	if (vars->tmp->cmd)
				dup2cmd_here(vars);
			else
				here_piping(vars);
}
int here_doc_exec(t_execution *vars ,t_env *env)
{
	while (vars->tmp->her_doc[vars->n])
	{
		dup2(vars->origin_in, STDIN_FILENO);
			pipe(vars->pipe_fd);
		vars->pid = fork();
		if (!vars->pid)
			here_doc_child(vars, env);
		else
		{
			waitpid(vars->pid, &vars->child_stat, 0);
			if (WIFSIGNALED(vars->child_stat) && WTERMSIG(vars->child_stat) == SIGINT)
				break ;
			if (WIFEXITED(vars->child_stat))
			{
				if(check_if_ctrl_c(vars) == 100)
					return (500);
				if(check_if_ctrl_c(vars) == 1)
					return (1);
			}
			close(vars->pipe_fd[1]);
			exec_dups_here(vars);
			}
			vars->n++;
		}
		return (0);
}
void check_which_built_in(t_execution *vars, t_env *env)
{
	if (vars->tmp->next)
		dup2(vars->pipe_fd[1], STDOUT_FILENO);
	if (!ft_strcmp_asd(vars->tmp->args_built_in[0], "export"))
		exec_export(&vars->tmp, &env);
	else if (!ft_strcmp_asd(vars->tmp->args_built_in[0], "echo"))
		exec_echo(vars->tmp);
	else if (!ft_strcmp_asd(vars->tmp->args_built_in[0], "unset"))
		exec_unset(&env, vars->tmp);
	else if (!ft_strcmp_asd(vars->tmp->args_built_in[0], "env"))
		exec_env(&env);
	else if (!ft_strcmp_asd(vars->tmp->args_built_in[0], "exit"))
		ft_exit(vars->tmp);
	else if (!ft_strcmp_asd(vars->tmp->args_built_in[0], "pwd"))
		ft_pwd(env);
	else if (!ft_strcmp_asd(vars->tmp->args_built_in[0], "cd"))
	{
		if (vars->tmp->args_built_in[1])
			ft_cd(vars->tmp->args_built_in[1], &env);
	}
}
void built_in_exec(t_execution *vars, t_env *env)
{
	(vars->i = 0, vars->j = 0, vars->k = 0);
	if (vars->tmp->in[vars->i] != -42 && vars->tmp->in[vars->i] != -1)
		vars->i++;
	if (vars->tmp->out[vars->j] != -42 && vars->tmp->out[vars->j] != -1)
		vars->j++;
	if (vars->tmp->ap[vars->k] != -42 && vars->tmp->ap[vars->k] != -1)
		vars->k++;
	else if (vars->j != 0 && vars->tmp->out[vars->j-1] >= 0 
	&& vars->tmp->in[vars->j-1] < 1024 && vars->tmp->out[vars->j-1] != -42 
	&& vars->tmp->out[vars->j-1] != -1)
	{
		while (vars->tmp->out[vars->j-1] != -42)
			vars->j++;
		redirect_output(vars->tmp->out[vars->j-2]);
	}
	else if (vars->k != 0 && vars->tmp->ap[vars->k-1] >= 0 && 
	vars->tmp->in[vars->k-1] < 1024 && vars->tmp->ap[vars->k-1] != -42 
	&& vars->tmp->ap[vars->k-1] != -1)
	{
	while (vars->k != 0 && vars->tmp->ap[vars->k-1] != -42)
				vars->k++;
		redirect_append(vars->tmp->ap[vars->k-2]);
	}
	check_which_built_in(vars, env);
	dup2(vars->origin_out, STDOUT_FILENO);
}
void exec_cmd_vars_init(t_execution *vars)
{
	vars->j = 0;
	vars->i = 0;
	vars->k = 0;
}

void closing_files(t_execution *vars)
{
	while(vars->tmp->out[vars->j] && vars->tmp->out[vars->j] != -42 
	&& vars->tmp->out[vars->j] != -1)
	{
		close(vars->tmp->out[vars->j]);
		vars->j++;
	}
	while(vars->tmp->in[vars->i] && vars->tmp->in[vars->i] != -42 
	&& vars->tmp->in[vars->i] != -1)
	{
		close(vars->tmp->in[vars->i]);
		vars->i++;
	}
	while(vars->tmp->ap[vars->k] && vars->tmp->ap[vars->k] != -42 
	&& vars->tmp->ap[vars->k] != -1)
	{
		close(vars->tmp->ap[vars->k]);
		vars->k++;
	}
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
        return (0) ;
    if (!vars->pid)
        exec_cmd(vars->tmp, env, vars->pipe_fd,vars);
	exec_cmd_vars_init(vars);
	closing_files(vars);
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
	close(vars->pipe_fd[1]);
	ft_free_holder(holder);	
}

int command_first_exec(t_execution *vars, t_env *env, t_last *status)
{
	if (!execution_cmd(vars, env,status))
		{
			ft_putstr_fd("minishell: fork: Resource temporarily unavailable\n", 2);
			return (0);
		}
	return (1);
}

void after_exec(t_holder **holder , t_execution *vars, t_last *status)
{
	status->status = ft_status(0, 1);
	waitpid(vars->pid, &status->status, 0);
	if (WIFEXITED(status->status))
	{
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

	while (vars.tmp)
	{
		status->status = ft_status(0, 1);
		pipe(vars.pipe_fd);
		if (vars.tmp->her_doc[vars.n])
		{
			(close(vars.pipe_fd[0]), close(vars.pipe_fd[1]));
			if (here_doc_exec(&vars, env)== 500)
				break;
		}
		if ((vars.tmp->cmd_built_in && vars.tmp->file_out[vars.j]) || vars.tmp->cmd_built_in)
			built_in_exec(&vars, env);
		if ((vars.tmp && vars.tmp->cmd) || (vars.tmp->file_out && vars.tmp->file_out[vars.j]) 
		|| (vars.tmp->file_in && vars.tmp->file_in[vars.i]) || (vars.tmp->append && vars.tmp->append[vars.k])
		|| (vars.tmp->args && vars.tmp->args[0] && vars.tmp->args[0][0]))
		{
			if(!command_first_exec(&vars, env, status))
				break;
		}
		piping(&vars);
		vars.tmp = vars.tmp->next;
	}
	after_exec(holder, &vars, status);
}
