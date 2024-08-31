#include "../minishell.h"

int x = 0;

int ft_check_exp(char *str)
{
    if (str[0] == '$' && x == 1)
    {
        x = 0;
        return (1);
    }
    else
        return (0);
}

char *ft_environment_variables(char *arguments, t_env *env_var)
{
    int i;
    int j;
    char *result;
    char tmp[BUFSIZ];
    char *env;
    char str[2];

    i = 0;
    j = 0;
    result = NULL;
    while (arguments[i] != '\0')
    {
        if (arguments[i] == '$' && ft_is_digits(arguments[i + 1]) == 1)
            i = i + 2;
        else if (arguments[i] == '$' && arguments[i + 1] != '$' && (x == 0 || x == 2) && arguments[i + 1] != '\0')
        {
            i++;
            j = 0;
            while (arguments[i] != '\0' && arguments[i] != ' ' && ft_is_valid(arguments[i]) == 1 && arguments[i] != '$' && j < sizeof(tmp) - 1)
            {
                tmp[j] = arguments[i];
                j++;
                i++;
            }
            tmp[j] = '\0';
            env = ft_getenv(env_var, tmp);
            if (env != NULL)
                result = ft_strjoinee(result, env);
            else if (env == NULL && x != 2)
                result = ft_strjoinee(result, "");
        }
        else
        {

            str[0] = arguments[i];
            str[1] = '\0';
            result = ft_strjoinee(result, str);
            i++;
        }
    }
    if (result == NULL)
    {
        arguments = NULL;
        return (arguments);
    }
    else
    {
        if (result != NULL)
            arguments = result;
    }
    return arguments;
}

int ft_check(char *input)
{
    int i;

    i = 0;
    if (input[i])
    {
        while (input[i] == ' ')
            i++;
        if ((input[i] == '\'' || input[i] == '\"') && (input[i + 1] == '\'' || input[i + 1] == '\"'))
        {
            if (input[i + 2] == '\0' || input[i + 2] == ' ')
                return (0);
        }
    }
    return (1);
}

char *replace_env_variable(const char *str, int *skip)
{
    char var_name[1024];
    int var_index;
    char *env;
    char *result;

    var_index = 0;

    if (str[*skip] == '$')
    {
        var_name[var_index++] = str[*skip];
        (*skip)++;
    }
    while (str[*skip] && isalnum(str[*skip]) || str[*skip] == '_')
    {
        var_name[var_index++] = str[*skip];
        (*skip)++;
    }
    var_name[var_index] = '\0';
    return (var_name);
}

char **split_line_to_args(char *input, t_env *env_var)
{
    char **args;
    char *env;
    char *env_val;
    char *env_tmp;
    char *env_tmp2;
    int i;
    int j;
    char quote;
    char buffer[1024];
    int buf_index;
    int check;

    i = 0;
    j = 0;
    quote = 0;
    buf_index = 0;
    args = malloc(sizeof(char *) * (ft_count_args(input) + 1));
    if (!args)
        return (NULL);
    check = ft_check(input);
    env_tmp = NULL;
    env_tmp2 = NULL;
    while (input[i] != '\0')
    {
        if ((input[i] == '\"' && input[i + 1] == '\"') &&
            (input[i + 2] != '\"' || input[i + 2] == '\0') &&
            (input[i + 2] == ' ' || input[i + 2] == '\0') &&
            quote == 0 && buf_index == 0)
        {
            args[j++] = ft_strdup("");
            i += 2;
            continue;
        }
        if ((input[i] != '\'' && input[i] != '"') && quote == 0 && buf_index == 0)
            x = 2;
        if ((input[i] == '\'' || input[i] == '"') && (input[i] == quote || quote == 0) && check == 1)
        {
            if (input[i] == '\"')
                x = 0;
            else
                x = 1;

            if (quote == 0)
                quote = input[i];
            else if (quote == input[i])
                quote = 0;
        }
        else if (input[i] == '$' && (quote == 0 || quote != '\''))
        {
            int temp_i = i + 1;
            while (input[temp_i] == '"' || input[temp_i] == '\'')
                temp_i++;

            if (input[temp_i] == ' ' || input[temp_i] == '\0')
            {
                i = temp_i - 1;
            }
            else
            {
                buffer[buf_index] = '\0';
                env_val = replace_env_variable(input, &i);
                env = ft_environment_variables(env_val, env_var);

                if (env != NULL)
                {
                    ft_strcpy(buffer + buf_index, env);
                    buf_index += ft_strlen(env);
                    free(env);
                }

                while (input[i] != '\0' && input[i] != ' ' && input[i] != '\'' && input[i] != '"' && input[i] != '$')
                {
                    buffer[buf_index++] = input[i++];
                }
                i--;
            }
        }
        else if (input[i] == ' ' && quote == 0)
        {
            if (buf_index > 0)
            {
                buffer[buf_index] = '\0';
                args[j++] = ft_strdup(buffer);
                buf_index = 0;
            }
        }
        else
        {
            buffer[buf_index++] = input[i];
        }
        i++;
    }
    if (buf_index > 0)
    {
        buffer[buf_index] = '\0';
        args[j++] = ft_strdup(buffer);
    }
    if (buf_index == 0)
    {
        args[1] = NULL;
    }
    args[j] = NULL;
    return (args);
}

int parse_line(t_data **data, char *input, t_env *env_var)
{
    char *command;
    char **arguments;
    char *token;
    char *remaining_input;
    int i;

    i = 0;
    if (check_qout(input) == 1)
    {
        printf("minishell: syntax error\n");
        free(input);
        return (1);
    }
    remaining_input = input;
    while ((token = strsplit_by_pipe(&input)) != NULL)
    {
        arguments = split_line_to_args(token, env_var);
        if (arguments[0] != NULL)
            ft_add_node(data, arguments);
        else
        {
            free(input);
            return (1);
        }
    }
    free(input);
    return (0);
}
