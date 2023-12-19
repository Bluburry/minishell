#include "minishell.h"

void	alter_paths(t_env *env, char *new_path, char *old_path)
{
	int	i;

	i = index_of_str(env, "PWD");
	replace_env_var(env, new_path, i);
	i = index_of_str(env, "OLDPWD");
	replace_env_var(env, old_path, i);
	free(old_path);
	free(new_path);
}

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
	alter_paths(env, new_path, old_path);
}

/**
 * @brief handles receiving a ~ or empty string, 
 * and sets it to the home directory and appends 
 * the extra string, then recursively calls cd again
 * @param env environmental variable structure
 * @param path path string to cd into
 * @return returns 0 on error, else it returns 
 * whatever the return from the recursive cd call was
*/
int	home_dir(t_env *env, const char *path)
{
	char	*str;
	int		ret;

	if (!path || !*path || (*path == '~' && (!*(path + 1) || \
		(*(path + 1) == '/' && !*(path + 2)))))
		return (cd(env, get_env_var(env, "HOME")));
	else if (*path == '~' && *(path + 1) == '/' && *(path + 2))
	{
		str = relative_path(env, path);
		ret = cd(env, str);
		return (free(str), ret);
	}
	return (0);
}

/**
 * @brief changes the current working directory using chdir
 * @param env environmental variable structure
 * @param path path string to cd into
 * @return returns 1 on success, 0 on error, automatically 
 * prints an error message
*/
int	cd(t_env *env, const char *path)
{
	char	*str;

	if (!path || !*path || *path == '~')
		return (home_dir(env, path));
	else if (chdir(path) != 0)
		return (perror("cd error"), 0);
	str = pwd();
	change_pwd(env, str);
	return (free (str), 1);
}
