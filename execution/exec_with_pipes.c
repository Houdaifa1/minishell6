#include "../minishell.h"

// void exec_with_pipes(char **commande, char **next_commande, t_env **envp, t_data **data, t_hold **hold_vars)
// {
//     int pid;
//     int pid2;
//     int fd[2];

//     if ((pid = fork()) == -1)
//     {
//         perror("fork failed");
//         exit(1);
//     }
//     if (pid == 0)
//     {
//         if (pipe(fd) == -1)
//         {
//             perror("pipe failed");
//             exit(1);
//         }
//         close(fd[0]);
//         dup2(fd[1], STDOUT_FILENO);
//         close(fd[1]);
//         exec_simple_commande(commande, envp, data, hold_vars);
//         if ((pid2 = fork()) == -1)
//         {
//             perror("fork failed");
//             exit(1);
//         }
//         if (pid2 == 0)
//         {
//             close(fd[1]);
//             dup2(fd[0], STDIN_FILENO);
//             close(fd[0]);
//             exec_simple_commande(next_commande, envp, data, hold_vars);
//             exit(0);
//         }

//         waitpid(pid2, NULL, 0);
//         exit(0);
//     }
//      waitpid(pid, NULL, 0);

// }

void exec_with_pipes(char **commande, char **next_commande, t_env **envp, t_data **data, t_hold **hold_vars)
{
    int pid;
    int pid2;
    int fd[2];

    if (pipe(fd) == -1)
    {
        perror("pipe failed");
        exit(1);
    }
    if ((pid = fork()) == -1)
    {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        exec_simple_commande(commande, envp, data, hold_vars);
        exit(0);
    }
    if ((pid2 = fork()) == -1)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    
    if (pid2 == 0)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        exec_simple_commande(next_commande, envp, data, hold_vars);
        exit(0);
    }
    close (fd[1]);
    close(fd[0]);
    waitpid(pid, NULL, 0);
    waitpid(pid2, NULL, 0);
}

// void exec_with_pipes(char **commande, char **next_commande, t_env **envp, t_data **data, t_hold **hold_vars)
// {
//     int pid;
//     int fd[2];

//     if (pipe(fd) == -1)
//     {
//         perror("pipe failed");
//         exit(EXIT_FAILURE);
//     }
//     if ((pid = fork()) == -1)
//     {
//         perror("fork failed");
//         exit(EXIT_FAILURE);
//     }
//     if (pid == 0)
//     {
//         if ((pid = fork()) == -1)
//         {
//             perror("fork failed");
//             exit(EXIT_FAILURE);
//         }
//         if (pid == 0)
//         {
//             close(fd[1]);
//             dup2(fd[0], STDIN_FILENO);
//             close(fd[0]);
//             exec_simple_commande(next_commande, envp, data, hold_vars);
//             exit(EXIT_SUCCESS);
//         }
//         else
//         {
//             close(fd[0]);
//             dup2(fd[1], STDOUT_FILENO);
//             close(fd[1]);
//             exec_simple_commande(commande, envp, data, hold_vars);
//             waitpid(pid, NULL, 0);
//             exit(EXIT_SUCCESS);
//         }
//     }
//     else
//     {
//         close(fd[0]);
//         close(fd[1]);
//         waitpid(pid, NULL, 0);
//     }
// }
