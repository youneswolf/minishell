#include "minishell.h"
void fill_null_env(t_env **mini_env)
{
	t_env *node;
	char *line;
	int len;
	int i;

	i = 0;
	char first[1024] = "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.";
	node = malloc(sizeof(t_env));
	if (!node)
		(ft_free_nodes(mini_env), exit(1));
	line = malloc(sizeof(char) * ft_strlen(first) + 1);
	if (!line)
		exit(1);
	while (first[i])
	{
		line[i] = first[i];
		i++;
	}
	line[i] = '\0';
	node->env = line;
	node->next = NULL;
	*mini_env = node;
	fill_second_null_env(mini_env);
}

void fill_second_null_env(t_env **mini_env)
{
	char	buf[1024];
	char	var[5] = "PWD=";
	t_env *node;
	char *line;
	int i;

	i = 0;
	if (getcwd(buf, sizeof(buf)) == NULL)
        (perror("getcwd"), exit(EXIT_FAILURE));
	node = malloc(sizeof(t_env));
	if (!node)
		(ft_free_nodes(mini_env), exit(1));
	line = malloc(sizeof(char) * ft_strlen(buf) + 5);
	if (!line)
		exit(0);
	while (var[i])
	{
		line[i] = var[i];
		i++;
	}
	i = 0;
	while (buf[i])
	{
		line[i + 4] = buf[i];
		i++;
	}
	line[i+4] = '\0';
	node->env = line;
	node->next = NULL;
	(*mini_env)->next = node;
}

void exec_env(t_env **mini_env, char *str)
{
	int i;
	t_env *tmp;

	tmp = *mini_env;
    // if (getcwd(buf, sizeof(buf)) == NULL)
    //     (perror("getcwd"), exit(EXIT_FAILURE));
	if (!ft_strcmp(str, "env"))
	{
		while (tmp)
		{
			printf("%s\n",tmp->env);
			tmp = tmp->next;
		}
		// else
		// {
		// 	printf("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.\n");
		// 	printf("PWD=%s\n", buf);
		// }
	}
	else
		return ;
}

// char **cpy_in_2d(t_env **mini_env, char **str)
// {
// 	int i;
// 	int j;
// 	char **new_str;
// 	i = 0;
// 	while (str[i])
// 	{
// 		i++;
// 	}
// 	new_str = malloc(sizeof(char *) * (i + 1));
// 	if (!new_str)
// 		exit(0);
// 	i = 0;
// 	while (str[i])
// 	{
// 		j = 0;
// 		new_str[i] = malloc(sizeof(char) * (ft_strlen(str[i]) + 1));
// 		if (!new_str[i])
// 			(free2darray(new_str, i), exit(0));
// 		while (str[j])
// 		{
// 			new_str[i][j] = str[i][j];
// 			j++;
// 		}
// 		i++;
// 	}
// 	new_str[i] = NULL;
// 	return (new_str);
// }
void	ft_free_nodes(t_env **a)
{
	t_env	*head;
	t_env	*tobefreed;

	head = *a;
	while (head != NULL)
	{
		tobefreed = head;
		head = head->next;
		free(tobefreed);
	}
	*a = NULL;
}

t_env	*get_last(t_env **a)
{
	t_env	*tmp;

	tmp = *a;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void fiLL_env(t_env **mini_env, char **env)
{
	char *line;
	int	i;
	int j;

	i = 0;
	while (env[i])
	{
		j = 0;
		line = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		if (!line)
			exit(0);
		while (env[i][j])
		{
			line[j] = env[i][j];
			j++;
		}
		env_list(mini_env, line);
		i++;

	}
}

void	env_list(t_env **mini_env, char *line)
{
	t_env	*node;
	t_env	*last_node;

	node = malloc(sizeof(t_env));
	if (!node)
		(ft_free_nodes(mini_env), exit(1));
	node->env = line;
	node->next = NULL;
	if (!(*mini_env))
	{
		*mini_env = node;
	}
	else
	{
		last_node = get_last(mini_env);
		last_node->next = node;
	}
}