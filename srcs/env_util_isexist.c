#include "minishell.h"
#include "env.h"

bool is_env_var_exist(char *var)
{
    char **env;
    size_t i;

    env = env_store(NULL, GET_ENV);
    while (env && env[i])
    {
        while (env && env[i] && ft_strncmp(env[i], var, ft_strlen(env[i])) == '=')
            return (true);
        i++;
    }
    return (false);
}