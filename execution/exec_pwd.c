#include "../minishell.h"

void exec_pwd(char **commande)
{
    char path[PATH_MAX];

    if (commande[1] != NULL && commande[1][0] == '-' &&  commande[1][1] != '\0')
    {
        if (commande[1][1] != '-' || commande[1][2] != '\0')
        {
            printf("pwd takes no option\n");
            return ;
        }
    }
    getcwd(path, PATH_MAX);
    printf("%s\n", path);
}
