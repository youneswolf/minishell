#include <unistd.h>
#include <stdio.h>
#include "minishell.h"

char    *ft_alloc_string(char *str, int i)
{
    int     j, k, flag = 0;
    char    *new = NULL;

    j = i;
    k = 0;
	if (!str || str[i] == '\0')
		return (NULL);

    while (str[i] != '\0' && str[i] != ' ')
    {
		if (str[i] == '\'' || str[i] == '\"')
		{
			flag = str[i];
			i++;
			k++;
			break;
		}
        i++;
        k++;
    }
	if (flag != 0)
	{
		while (str[i] && str[i] != flag)
		{
			i++;
			k++;
		}
		if (str[i])
		{
			i++;
			k++;
		}
		if (str[i] == '\'' || str[i] == '\"')
		{
			flag = str[i];
			while (str[i] && str[i] != ' ')
			{
				i++;
				k++;
			}
		}
	} 
	if (str[i] == flag)
		k++;
	printf("{%d}\n", k);
	new = malloc((k + 1) * sizeof(char));
	if (!new)
		return (NULL);
    i = 0;
	while (str[j] != '\0' && str[j] != ' ')
	{
		if (str[j] == '\"' || str[j] == '\'')
		{
			flag = str[j];
			new[i] = flag;
			if (str[j])
				(j++, i++);
			break;
		}
		new[i] = str[j];
		i++;
		j++;
	}
	if (flag)
	{
		while (str[j] != '\0' && str[j] != flag)
		{
			new[i] = str[j];
			i++;
			j++;
		}
		if (str[j] == flag && str[j + 1] != ' ')
		{
			while (str[j] != '\0' && str[j] != ' ')
			{
				new[i] = str[j];
				i++;
				j++;
			}
		}
		
	}
	if (new == NULL)
		return (NULL);
	new[i] = '\0';
    return (new);
}

int	ft_strlen1(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putnode(char *str)
{
    int i = 0, l;
	char *str1 = NULL;
	int flag;

	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		str1 = ft_alloc_string(str, i);
		printf("===%s===and size = {%d}\n", str1, ft_strlen1(str1));
		i += ft_strlen1(str1);
		if (str[i])
			i++;
	}
}
int main()
{
    ft_putnode("ls -al | grep \"\"\'\'\"\' test");
}