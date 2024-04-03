#include "minishell.h"
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
						split = ft_lst_new(str[j]);
					else
					{
						node = get_last_l(&split);
						node->next = ft_lst_new(str[j]);
					}
					j++;
				}
			}
			i++;
		}
	j = 0;
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
				dollar_str_space = ft_strjoin("$",dollar_str_space);
				join = ft_strjoin(join, expand_here(dollar_str_space, env));
				while (dollar_str[j] && dollar_str[i][j] == ' ')
				{
					join = ft_strjoin(join, " ");
					j++;
				}
				i++;
			}
			// printf("%s\n",join);
		}
		else 
		{
			j = 0;
			// printf("else\n");
			join = ft_strjoin(join, expand_here(split->str, env));
			if (split->next)
				join = ft_strjoin(join," ");
		}
		split = split->next;
	}

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
		sub = ft_substr(str, i+1, (ft_strlen(str) - i -1));
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
			special = ft_substr(sub, i, j - i);
			pre_var = ft_substr(sub, 0, i);
			break;
		}
		i++;
	}
	if (pre_var)
		var = ft_strjoin(pre_var, "=");
	else
		var = ft_strjoin(sub, "=");
	while ((tmp && pre_var) || (tmp && var))
	{
		if (!ft_strncmp(var, tmp->env, ft_strlen(var)))
		{
			i = 0;
			var = ft_strjoin(tmp->env,special);
			while (var && var[i] != '=')
				i++;
			var = ft_substr(var, i + 1, ft_strlen(var) - i - 1);
			var = ft_strjoin(pre_special,var);
			return (var);
		}
		tmp = tmp->next;
	}
	if (str && str[0] == '$')
	{
		pre_var = ft_strjoin(pre_special, special);
		return (ft_strjoin("$", pre_var));
	}
	return (ft_strjoin(pre_special, special));
}
