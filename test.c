void create_pipes(char **commande, t_env **env, t_data **data, t_hold **hold_vars, int fd_in, int fd_out)
{
    int pid;

    if ((pid = fork()) == -1)
    {
        perror("Error creating new process");
        exit(1);
    }
    if (pid == 0)
    {
        if (fd_in != 0)
        {
            dup2(fd_in, 0);
            close(fd_in);
        }
        if (fd_out != 1)
        {
            dup2(fd_out, 1);
            close(fd_out);
        }
        exec_simple_commande(commande, env, data, hold_vars);
        exit(0);
    }
}

void exec_with_pipes(t_env **envp, t_data **data, t_hold **hold_vars)
{
    t_data *temp;
    int fd[2];
    int fd_in = 0;
    int status;

    temp = *data;
    int i = 0;
    while (temp)
    {
        if (temp->next != NULL)
        {
            if (pipe(fd) == -1)
            {
                perror("Error creating pipe");
                exit(1);
            }
        }
        else
            fd[1] = 1;
        create_pipes(temp->argumment, envp, data, hold_vars, fd_in, fd[1]);
        if (fd_in != 0)
            close(fd_in);
        if (fd[1] != 1)
            close(fd[1]);
        fd_in = fd[0];
        temp = temp->next;
    }
    while (wait(&status) > 0);
}
