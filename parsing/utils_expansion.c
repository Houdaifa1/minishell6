
#include "../minishell.h"

int ft_is_digits(char c)
{
    if (c > 47 && c < 58)
        return (1);
    else
        return (0);
}

int ft_is_valid(char c)
{
    if (c > 64 && c < 91)
        return (1);
    else if (c > 96 && c < 123)
        return (1);
    else if (c > 47 && c < 58)
        return (1);
    else if (c == '_')
        return (1);
    else
        return (0);
}

char    *ft_strcpy(char *dest, const char *src)
{
    size_t  i;

    i = 0;
    while (src[i] != NULL)
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

char *ft_strjoinee(char *s1, const char *s2)
{
    size_t  len1;
    size_t  len2;

    len1 = 0;
    len2 = 0;
    if (s1 != NULL)
        len1 = strlen(s1);
    if (s2 != NULL)
        len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 1);
    if (!result)
        return NULL;
    if (s1 != NULL)
        strcpy(result, s1);
    if (s2 != NULL)
        strcpy(result + len1, s2);
    free(s1);
    return (result);
}
