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
	char	*path_new;
	char	*path_old;
	size_t	s;

	if (*path == '.' && *(path + 1) == '.')
	{
		// work out how to go back the pwd and then append
		// probably alter old path to represent only what i need
	}
	s = ft_strlen(path_old) + ft_strlen(path) + 2;
	if (*path == '.' && *(path + 1) == '/')
	str = ft_strjoin

	return (str);
}

char	*rollback(char *pwd, char *path)
{
	int	i;
	int	j;

	i = ft_strlen(pwd) - 1;
	j = 0;
	while (*(pwd + i) && *(path + j) && *(path + j) == '.')
	{
		j += 3;
		while (i >= 0 && *(pwd + i) != '/')
			i--;
		i--;
	}
	// this should give me both the index of where 
	// to stop copying pwd, and to start copying path
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
