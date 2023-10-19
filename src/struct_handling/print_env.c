#include "../../include/minishell.h"

// TODO: NEEDS TO BE 
char	**env_string(t_env *env)
{
	char	**ret;

	ret = (char **) malloc(sizeof(char*) * env->size);
	copy_char_matrix(env->vars, ret, env->size, -1);
	return (ret);
}