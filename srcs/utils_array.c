#include "minishell.h"

//縦をカウント
int str_arr_len(char **arr)
{
    int i;

    i = 0;
    //要素がある限りカウント
    while (arr && arr[i])
        i++;
    return (i);
}

char **str_arr_dup(char **arr)
{
    char **cpy;
    int i;

    if (!arr)
        return (NULL);
    //外側
    cpy = ft_calloc(str_arr_len(arr) + 1, sizeof(*cpy));
    if (!cpy)
        return (NULL);
    i = 0;
    //中
    while (arr[i])
    {
        cpy[i] = ft_strdup(arr[i]);
        i++;
    }
    return (cpy);
}

void free_str_array(char ***arr)
{
    int i;

    i = 0;
    while (*arr && (*arr)[i])
    {
        free((*arr)[i]);
        (*arr)[i] = NULL;
        i++;
    }
    free(*arr);
    *arr = NULL;
}