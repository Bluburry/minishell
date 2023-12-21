#include "minishell.h"

int	var_to_print(char *str)
{
	while (*str && *str != '=')
		str++;
	if (!*str || !*++str)
		return (0);
	return (1);
}

int	num_invalid_env_vars(t_env *env)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	while (++i < env->size)
		if (!var_to_print(env->vars[i]))
			n++;
	return (n);
}

static void	copy_char_to_env(char **mat, char **new_mat, int size)
{
	int		i;
	int		j;
	size_t	s;

	i = 0;
	j = 0;
	while (i < size)
	{
		if (!var_to_print(mat[i]))
		{
			i++;
			continue ;
		}
		s = ft_strlen(mat[i]) + 1;
		new_mat[j] = (char *) malloc(sizeof(char) * s);
		ft_memcpy(new_mat[j], mat[i], s);
		i++;
		j++;
	}
}

char	**env_string(t_env *env)
{
	int		n;
	char	**ret;

	n = num_invalid_env_vars(env);
	ret = (char **) malloc(sizeof(char *) * (env->size - n + 1));
	copy_char_to_env(env->vars, ret, env->size);
	ret[env->size - n] = NULL;
	return (ret);
}
