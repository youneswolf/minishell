#include "minishell.h"
char *handle_expand_here(char *line_str, t_env **env)
{
	t_line *split = NULL;
	t_line *node;
	char *join = NULL;
	char **str = NULL;
	char **dollar_str;
	int i = 0;
	int j = 0;
		while (line_str && line_str[i])
		{
			if (line_str[i] == '$')
			{
				str = ft_split(line_str, 42);
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
	while (split)
	{
		join = ft_strjoin(join, expand(&split, env));
		if (split->next)
			join = ft_strjoin(join," ");
		split = split->next;
	}

	if (!join)
		return ("");
	return (join);
}
// char *expand_here(t_line **line, t_env **env)
// {
// 	t_env *tmp;
// 	t_line *line_tmp;
// 	char *special = NULL;
// 	char *pre_special = NULL;
// 	int i;
// 	char *var;
// 	char *sub;
// 	char *pre_var = NULL;
// 	tmp = *env;
// 	line_tmp = *line;
// 	i = 0;
// 	int j = 0;
// 	if ( line_tmp && (line_tmp->str[0] == 34 || line_tmp->str[ft_strlen(line_tmp->str) - 1] == 34))
// 	{
// 		sub = ft_strtrim(line_tmp->str, "\"", 1);
// 		while (sub && sub[i] != '$')
// 			i++;
// 		if (i && i != ft_strlen(line_tmp->str))
// 		{
// 			pre_special = ft_substr(sub, 0, i);
// 		}
// 		if (line_tmp && line_tmp->str[0] == 34)
// 			sub = ft_substr(line_tmp->str, i+2, (ft_strlen(line_tmp->str) - i - 1));
// 		else 
// 			sub = ft_substr(line_tmp->str, i+1, (ft_strlen(line_tmp->str) - i - 1));
// 		sub = ft_strtrim(sub, "\"", 1);
// 	}
// 	else
// 	{
// 		while (line_tmp && line_tmp->str[i] != '$')
// 			i++;
// 		if (i && i != ft_strlen(line_tmp->str))
// 		{
// 			pre_special = ft_substr(line_tmp->str, 0, i);
// 		}
// 		sub = ft_substr(line_tmp->str, i+1, (ft_strlen(line_tmp->str) - i -1));
// 	}
// 	i = 0;
// 	while (sub && sub[i])
// 	{
// 		if (sub[i] == '.' || sub[i] == ',' || sub[i] == '/' || sub[i] == '-' || sub[i] == ':' || sub[i] == '_')
// 		{
// 			j = i;
// 			while (sub [j] && sub[j] != '$')
// 				j++;
// 			special = ft_substr(sub, i, j - i);
// 			pre_var = ft_substr(sub, 0, i);
// 			break;
// 		}
// 		i++;
// 	}
// 	if (pre_var)
// 		var = ft_strjoin(pre_var, "=");
// 	else
// 		var = ft_strjoin(sub, "=");
// 	// printf("%s\n",var);
// 	while ((tmp && pre_var) || (tmp && var))
// 	{
// 		if (!ft_strncmp(var, tmp->env, ft_strlen(var)))
// 		{
// 			i = 0;
// 			var = ft_strjoin(tmp->env,special);
// 			while (var && var[i] != '=')
// 				i++;
// 			var = ft_substr(var, i + 1, ft_strlen(var) - i - 1);
// 			var = ft_strjoin(pre_special,var);
// 			return (var);
// 		}
// 		tmp = tmp->next;
// 	}
// 	if (!if_dollar(line_tmp->str))
// 	{
// 		pre_var = ft_strtrim(line_tmp->str, "\"", 1);
// 		pre_var = ft_strtrim(pre_var, "\'", 1);
// 		return (pre_var);
// 	}
// 	return (pre_special);
// }
