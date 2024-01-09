#include "minishell.h"

static void	alter_paths(t_env *env, char *new_path, char *old_path)
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
static void	change_pwd(t_env *env, const char *path)
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
static int	home_dir(t_env *env, char **path)
{
	char	*str;
	char	*str2;
	size_t	s;

	if (!path[1][1])
	{
		str2 = get_env_var(env, "HOME");
		s = ft_strlen(str2) + 1;
		str = (char *) malloc(sizeof(char) * s);
		ft_memcpy(str, str2, s);
	}
	else
		str = relative_path(env, path[1]);
	if (chdir(str) != 0)
		return (perror("cd error"), 0);
	change_pwd(env, str);
	return (free(str), 1);
}

/**
 * @brief changes the current working directory using chdir
 * @param env environmental variable structure
 * @param path path string to cd into
 * @return returns 1 on success, 0 on error, automatically 
 * prints an error message
*/
int	cd(t_env *env, char **path)
{
	char	*str;
	int		i;

	i = 0;
	while (path[i])
		i++;
	if (i < 2)
		printf("minishell: cd: too few arguments\n");
	else if (i >= 3)
		printf("minishell: cd: too many arguments\n");
	if (i != 2)
		return (0);
	if (*path[1] == '~')
		return (home_dir(env, path));
	else if (chdir(path[1]) != 0)
		return (perror("cd error"), 0);
	str = pwd();
	change_pwd(env, str);
	return (free(str), 1);
}
