#include "libft.h"
#include "minishell.h"
#include "structures.h"
#include <stddef.h>

void	cd_error(void)
{

}

void	change_pwd(t_env *env, const char *path)
{
	char	*new_path;
	char	*old_path;
	char	*path_old;
	size_t	s;

	s = ft_strlen(path) + 1;
	new_path = (char *) malloc(sizeof(char) * (s + 4));
	ft_memcpy(new_path, "PWD=", 4);
	ft_memcpy(new_path+3, path, s);
	path_old = get_env_var(env, "PWD");
	s = ft_strlen(path_old) + 1;
	old_path = (char *) malloc(sizeof(char) * (s + 7));
	ft_memcpy(old_path, "OLDPWD=", 7);
	ft_memcpy(old_path+7, path_old, s);
	add_new_env_var(env, new_path);
	add_new_env_var(env, old_path);
	free(old_path);
	free(new_path);
}

char	*calc_pwd(t_env *env, const char *path)
{
	char	*str;
	char	*path_old;
	size_t	s;

	//if(*path == '.' && *(path + 1) == '.')
	s = ft_strlen(path_old) + ft_strlen(path) + 2;
}

void	cd(t_env *env, const char *path)
{
	t_path	p;
	char	*str;

	if (!path || !*path)
	{
		p = NO_PATH;
		path = get_env_var(env, "HOME");
	}
	else if (*path == '/')
		p = ABSOLUTE;
	else
	 	p = RELATIVE;
	if (chdir(path) != 0)
		p = INVALID;
	if (p == 3)
		cd_error();
	else if (p != 1)
		change_pwd(env, path);
	else
	{
	 	str = calc_pwd(env, path);
		change_pwd(env, str);
		free (str);
	}
}
