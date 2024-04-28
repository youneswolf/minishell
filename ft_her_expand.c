#include "minishell.h"

char	*ft_str_join(char *static_str, char *buff)
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
	str = malloc(sizeof(char) * (len + ft_strlen(buff)) + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (static_str && static_str[i] != '\0')
	{
		str[i] = static_str[i];
		i++;
	}
	while (buff && buff[j] != '\0')
		str[i++] = buff[j++];
	str[i] = '\0';
	return (str);
}
int	ft_isalpha(int c)
{
	if (((unsigned char )c >= 65 && (unsigned char )c <= 90)
		|| ((unsigned char )c >= 97 && (unsigned char )c <= 122))
	{
		return (1);
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if ((char )c >= 48 && (char )c <= 57)
	{
		return (1);
	}
	return (0);
}
int     ft_isalnum(int c)
{
        if (ft_isalpha(c) || ft_isdigit(c))
        {
                return (1);
        }
        return (0);
}
int count_dollar(char *str)
{
	int i = 0;
	int count = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}
int count_sgl_quote(char *str)
{
	int i = 0;
	int count = 0;
	while (str && str[i])
	{
		if (str[i] == 39)
			count++;
		i++;
	}
	return (count);
}
char *handle_expand_here(char *line_str, t_env **env)
{
	t_line *split = NULL;
	t_line *node;
	char *dollar_str_space;
	char *spaces;
	char *join = NULL;
	char **str = NULL;
	char **dollar_str = NULL;
	int i = 0;
	int j = 0;
		while (line_str && line_str[i])
		{
			if (line_str[i] == '$')
			{
				str = ft_split(line_str, 32);
				while (str[j])
				{
					if (!split)
						split = ft_lst_new(ft_strdup(str[j]));
					else
					{
						node = get_last_l(&split);
						node->next = ft_lst_new(ft_strdup(str[j]));
					}
					j++;
				}
				ft_free_2d(str);
			}
			i++;
		}
	j = 0;
	free(line_str);
	node = split;
	while (split)
	{
		if (count_dollar(split->str) > 1)
		{
			i = 0;
			dollar_str = ft_split(split->str, '$');
			while(dollar_str[i])
			{
				j = 0;
				// spaces = ft_substr(dollar_str[i], 0, ft_strlen(dollar_str[i] - j));
				dollar_str_space = ft_strtrim(dollar_str[i], " ", 1);
				dollar_str_space = ft_strjoin("$",dollar_str_space,3);
				join = ft_strjoin(join, expand_here(dollar_str_space, env),2);
				while (dollar_str[j] && dollar_str[i][j] == ' ')
				{
					join = ft_strjoin(join, " ",1);
					j++;
				}
				i++;
				free(dollar_str_space);
			}
			// printf("%s\n",join);
		}
		else 
		{
			j = 0;
			// printf("else\n");
			join = ft_strjoin(join, expand_here(split->str, env),2);
			if (split->next)
				join = ft_strjoin(join," ",1);
		}
		split = split->next;
	}
	ft_free_list2(&node);
	if (!join)
		return ("");
	return (join);
}
char *expand_here(char *str, t_env **env)
{
	t_env *tmp;
	t_line *line_tmp;
	char *special = NULL;
	char *pre_special = NULL;
	int i;
	char *var;
	char *sub;
	char *pre_var = NULL;
	tmp = *env;
	i = 0;
	int j = 0;
	// if ( str && (str[0] == 34 || str[ft_strlen(str) - 1] == 34))
	// {
	// 	// sub = ft_strtrim(str, "\"", 1);
	// 	while (sub && sub[i] != '$')
	// 		i++;
	// 	if (i && i != ft_strlen(str))
	// 	{
	// 		pre_special = ft_substr(sub, 0, i);
	// 	}
	// 	if (str && str[0] == 34)
	// 		sub = ft_substr(str, i+2, (ft_strlen(str) - i - 1));
	// 	else 
	// 		sub = ft_substr(str, i+1, (ft_strlen(str) - i - 1));
	// 	sub = ft_strtrim(sub, "\"", 1);
	// }
	// else
	// {
		while (str && str[i] != '$')
			i++;
		if (i && i != ft_strlen(str))
		{
			pre_special = ft_substr(str, 0, i);
		}
		sub = ft_sub_str(str, i+1, (ft_strlen(str) - i -1),0);
	// }
	i = 0;
	// if (count_sgl_quote(pre_special) % 2 != 0)
	// {
	// 	return (str);
	// }
	while (sub && sub[i])
	{
		if (sub[i] == '.' || sub[i] == ',' || sub[i] == '/' || sub[i] == '-' || sub[i] == ':' || sub[i] == '_' || sub[i] == 34 || sub[i] == 39)
		{
			j = i;
			while (sub [j] && sub[j] != '$')
				j++;
			special = ft_sub_str(sub, i, j - i,0);
			pre_var = ft_sub_str(sub, 0, i,0);
			break;
		}
		i++;
	}
	if (pre_var)
	{
		var = ft_strjoin(pre_var, "=",1);
		free(sub);
	}
	else
		var = ft_strjoin(sub, "=",1);
	while ((tmp && pre_var) || (tmp && var))
	{
		if (!ft_strncmp(var, tmp->env, ft_strlen(var)))
		{
			i = 0;
			free(var);
			var = ft_strjoin(tmp->env,special,0);
			while (var && var[i] != '=')
				i++;
			var = ft_sub_str(var, i + 1, ft_strlen(var) - i - 1,1);
			var = ft_strjoin(pre_special,var,3);
			return (var);
		}
		tmp = tmp->next;
	}
	i = 0;
	j = 42;
	if (if_dollar(str))
	{
		while (str[i] && str[i] != '$')
		{
			i++;
		}
		while (str[i])
		{
			if (ft_isalnum(str[i]) == 1)
			{
				return (pre_special);
			}
			else
				return (str);
		}
		return ("");
	}
	if (str && str[0] == '$')
	{
		pre_var = ft_strjoin(pre_special, special,2);
		return (ft_strjoin("$", pre_var,3));
	}
	return (ft_strjoin(pre_special, special,2));
}
