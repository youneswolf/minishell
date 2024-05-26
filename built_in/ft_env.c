#include "../minishell.h"

int is_equal(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}
void exec_env(t_env **mini_env)
{
    int i;
    t_env *tmp;

    tmp = *mini_env;
    while (tmp)
    {
        if (is_equal(tmp->env))
            printf("%s\n",tmp->env);
        tmp = tmp->next;
    }
}