#include "minishell.h"

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
		str = calc_pwd(get_env_var(env, "HOME"), path + 2);
		ret = cd(env, str);
		free(str);
		return (ret);
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
	t_path	p;
	char	*str;

	p = RELATIVE;
	if (!path || !*path || *path == '~')
		return (home_dir(env, path));
	else if (chdir(path) != 0)
		return (perror("cd error"), 0);
	else if (*path == '/')
		p = ABSOLUTE;
	if (p != 1)
		return (change_pwd(env, path), 1);
	else
	{
		str = relative_path(env, path);
		change_pwd(env, str);
		return (free (str), 1);
	}
}
