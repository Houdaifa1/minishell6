#include "../minishell.h"

int	ft_atoi(char *str)
{
	int	i;
	int	symbol;
	int	outcome;

	i = 0;
	symbol = 1;
	outcome = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			symbol = symbol * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		outcome = outcome * 10 + (str[i] - 48);
		i++;
	}
	return (outcome * symbol);
}
int ft_isalnum(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[0] == '+' || str[0] == '-')
            i++;
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (1);
        else
            i++;
    }
    
    if (i == 20)
        return (1);
    
    return(0);
}
void exec_exit(char **commande, t_env **envp, t_data **data, t_hold **hold_vars)
{
    int i;

    
    if (commande[1] != NULL && ft_isalnum(commande[1]) == 1)
    {
        printf("exit: %s: numeric argument required\n", commande[1]);
        free((*hold_vars)->input);
        free((*hold_vars)->temp);
        free(*hold_vars);
        ft_free_list(*data);
        ft_free_list2(*envp);
        exit(2);
    }
    else if (commande[1] != NULL && commande[2] != NULL)
        printf("exit: too many arguments\n");
    else if (commande[1] != NULL)
    {
        i = ft_atoi(commande[1]);
        free((*hold_vars)->input);
        free((*hold_vars)->temp);
        free(*hold_vars);
        ft_free_list(*data);
        ft_free_list2(*envp);
        exit(i);
    }
    else
    {
        free((*hold_vars)->input);
        free((*hold_vars)->temp);
        free(*hold_vars);
        ft_free_list(*data);
        ft_free_list2(*envp);
        exit (0);
    }
}
