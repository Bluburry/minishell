#include "minishell.h"

/**
 * @brief changes the current pwd and old pwd in the
 * environmental structure
 * @param env environmental variable structure
 * @param path path string to cd into
*/
void	change_pwd(t_env *env, const char *path)
{
	char	*new_path;
	char	*old_path;
	char	*path_old;
	size_t	s;

	s = ft_strlen(path);
	if (path[s - 2] == '/')
		s--;
	new_path = (char *) malloc(sizeof(char) * (s + 5));
	ft_memcpy(new_path, "PWD=", 4);
	ft_memcpy(new_path + 4, path, s);
	new_path[s + 4] = 0;
	path_old = get_env_var(env, "PWD");
	s = ft_strlen(path_old) + 1;
	old_path = (char *) malloc(sizeof(char) * (s + 7));
	ft_memcpy(old_path, "OLDPWD=", 7);
	ft_memcpy(old_path + 7, path_old, s);
	add_new_env_var(env, new_path);
	add_new_env_var(env, old_path);
	free(old_path);
	free(new_path);
}
