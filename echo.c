#include "minishell.h"

char *expand(t_line **line, t_env **env)
{
	t_env *tmp;
	t_line *line_tmp;
	char special[1024];
	special[0] = '\0';
	int i;
	char *var;
	char *sub;
	int j = 0;
	tmp = *env;
	line_tmp = *line;
	i = 0;
	if (line_tmp->str[0] == 34)
	{
		sub = ft_strtrim(line_tmp->str, "\"", 1);
	}
	else
		sub = ft_substr(line_tmp->str, 1, ft_strlen(line_tmp->str));
	while (sub[i])
	{
		if (sub[i] == '.')
		{
			special[j] = '.';
			sub = ft_strtrim(sub, ".", 0);
			j++;
		}
		else if (sub[i] == ',')
		{
			special[j] = ',';
			sub = ft_strtrim(sub, ",", 0);
			j++;
		}
		else if (sub[i] == '/')
		{
			special[j] = '/';
			sub = ft_strtrim(sub, "/", 0);
			j++;
		}
		else if (sub[i] == '-')
		{
			special[j] = '-';
			sub = ft_strtrim(sub, "-", 0);
			j++;
		}
		i++;
	}
	var = ft_strjoin(sub, "=");
	while (tmp)
	{
		if (!ft_strncmp(var, tmp->env, ft_strlen(var)))
		{
			i = 0;
			var = ft_strjoin(tmp->env,special);
			while (var[i] != '=')
				i++;
			var = ft_substr(var, i + 1, ft_strlen(var) - i - 1);
			return (var);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void sub_echo(char *str)
{
	t_line *tmp;
	char to_skip;
	int sglquote;
	int dblquote;
	int i;

	i = 0;
	while (str[i])
	{
		if (to_skip == str[i])
		{
			i++;
			continue ;
		}
		if (str[i] == 39)
		{
			sglquote++;
			if (!dblquote)
			{
				to_skip = str[i];
				continue ;
			}
		}
		else if (str[i] == 34)
		{
			dblquote++;
			if (!sglquote)
			{
				to_skip =str[i];
				continue ;
			}
		}
		write(1, &str[i], 1);
		i++;
		}
}
void exec_echo(t_line **line, t_env **env)
{
	char *sub;
	int sglquote;
	int dblquote;
	int i;
	char to_skip;
	t_line *tmp;

	tmp = *line;
	i = 0;
	sglquote = 0;
	dblquote = 0;
	if (!ft_strcmp(tmp->str, "-n"))
	{
			if (tmp->next->str)
			{
				tmp = tmp->next;
				if (tmp->str[0] == '$')
					sub_echo(expand(&tmp, env));
				else
				{
					sub_echo(tmp->str);
				}
			}
	}
	else if (tmp->str[0] == '$')
	{
		sub_echo(expand(line, env));
		write(1, "\n", 1);
	}
	else
	{
		sub_echo(tmp->str);
		write(1, "\n", 1);
	}
}
