#include "../minishell.h"

void ft_print_env(t_env *envp)
{
    while (envp)
    {
        printf("%s", envp->var);
        if (envp->val)
            printf("\"%s\"\n", envp->val);
        else
            printf("\n");
        envp = envp->next;
    }
}

void exec_env(char **commande, t_env *envp)
{
    if (commande[1] == NULL)
    {
        ft_print_env(envp);
    }
    else
        printf("env: ‘%s’: No such file or directory\n", commande[1]);
}