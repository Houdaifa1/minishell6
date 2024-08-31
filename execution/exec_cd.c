#include "../minishell.h"

char *grep_env_value(char *envp, int i)
{
    int j;
    char *value;

    j = 0;

    while (envp[j])
        j++;
    value = malloc(j - i + 1);
    j = 0;
    while (envp[i])
    {
        value[j] = envp[i];
        j++;
        i++;
    }
    value[j] = '\0';
    return (value);
}

char *ft_getenv(t_env *envp, char *var)
{
    int j;
    int i;

    j = 0;
    while (envp != NULL)
    {
        i = 0;
        while (envp->var[i] && var[i])
        {
            if (envp->var[i] != var[i])
                break;
            i++;
        }
        if (var[i] == '\0' && envp->var[i] == '=')
            return (envp->val);
        envp = envp->next;
    }
    return (NULL);
}
char *go_home(char **commande, t_env *envp, char *home, char *join)
{
    home = ft_getenv(envp, "HOME");
    if (commande[1] == NULL || (commande[1][0] == '-' && commande[1][1] == '-' && commande[1][2] == '\0'))
    {
        if (home == NULL)
            return (NULL);
        if (chdir(home) != 0)
            printf("cd: %s: No such file or directory\n", home);
        else
            return (home);
    }
    else if (commande[1][0] == '~')
    {
        if (home == NULL)
            return (NULL);
        join = ft_strjoin(home, &commande[1][1], 1, 1);
        if (chdir(join) != 0)
            printf("cd: %s: No such file or directory\n", commande[1]);
        return (join);
    }
    return (NULL);
}

void exec_cd(char **commande, t_env *envp)
{
    char *path;

    if (commande[1] != NULL && commande[2] != NULL)
    {
        printf("too many arguments\n");
        return;
    }
    else if ((path = go_home(commande, envp, NULL, NULL)) == NULL)
    {
        if (commande[1] != NULL && commande[1][0] != '~' && chdir(commande[1]) != 0)
            printf("cd: %s: No such file or directory\n", commande[1]);
    }
    if (commande[1] != NULL && commande[1][0] == '~' && path != NULL)
        free(path);
}



