#include "minishell.h"

void exec_echo(char *str)
{
	char *sub;
	int sglquote;
	int dblquote;
	int i;
	char to_skip;

	i = 0;
	sglquote = 0;
	dblquote = 0;
	if (!ft_strncmp("echo ", str, 5))
	{
		if (str[5] == '-' && str[6] == 'n')
		{
			sub = ft_substr(str, 8, ft_strlen(str) - 7);
			ft_putstr_fd(sub, 1);
			free(sub);
		}
		else
		{
			sub = ft_substr(str, 5, ft_strlen(str) - 5);
			while(sub[i])
			{
				if (sub[i] == to_skip && sub[i + 1] == ' ')
				{
						while (sub[i + 1] == 32)
							i++;
						i++;
						sglquote = 0;
						dblquote = 0;
						to_skip = '\0';
						write(1, " ", 1);
						continue ;
				}
				if (to_skip == sub[i])
				{
					i++;
					if (sub[i + 1] != 32)
						continue ;
				}
				if (sub[i] == 39)
				{
					sglquote++;
					if (!dblquote)
					{
						to_skip = sub[i];
						continue ;
					}
				}
				else if (sub[i] == 34)
				{
					dblquote++;
					if (!sglquote)
					{
						to_skip = sub[i];
						continue ;
					}
				}
					write(1, &sub[i], 1);
				i++;
			}
			write(1, "\n", 1);
			free(sub);
		}
	}
	else
		return ;
}
