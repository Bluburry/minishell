#include "minishell.h"

/**
 * @brief takes the indexes for where to stop copying the old pwd
 * and start copying the new path to create the string that will 
 * be the new pwd
 * @param pwd old path
 * @param path new string to append to old
 * @param i index to stop copying old path
 * @param j index to start copying new path
 * @return new path
*/
char	*complex_path(char *pwd, const char *path, int i, int j)
{
	int		s;
	char	*str;

	s = i + (int) ft_strlen(path) - j;
	if (s <= 1)
	{
		str = (char *) malloc(sizeof(char) * 2);
		str[0] = '/';
		str[1] = 0;
		return (str);
	}
	str = (char *) malloc(sizeof(char) * (s + 2));
	ft_memcpy(str, pwd, i);
	if (*(path + j))
	{
		str[i] = '/';
		ft_memcpy(str + i + 1, path + j, ft_strlen(path) - j + 1);
	}
	else
		str[s] = 0;
	return (str);
}

/**
 * @brief manipulates the previous pwd path to append the new 
 * path where necessary (for ../something and ~/something)
 * @param pwd old path
 * @param path new string to append to old
 * @return new path string
*/
char	*calc_pwd(char *pwd, const char *path)
{
	int	i;
	int	j;
	int	c;

	i = ft_strlen(pwd) - 1;
	j = 0;
	c = 0;
	while (*(pwd + i) && *(path + j) && \
		(*(path + j) == '.' || *(path + j) == '/'))
	{
		if (*(path + j) == '.')
			c++;
		if (c == 2)
		{
			c = 0;
			while (i > 0 && *(pwd + i) != '/')
				i--;
			i--;
		}
		j++;
	}
	return (complex_path(pwd, path, i + 1, j));
}

/**
 * @brief creates a path string from the relative path given
 * @param env environmental variable structure
 * @param path path string to cd into
 * @return new path string
*/
char	*relative_path(t_env *env, const char *path)
{
	char	*str;
	char	*new_path;
	char	*path_old;
	size_t	s;

	path_old = get_env_var(env, "PWD");
	if (*path == '.' && *(path + 1) && *(path + 1) == '.')
		return (calc_pwd(path_old, path));
	else if (*path == '~')
		return (calc_pwd(get_env_var(env, "HOME"), path + 2));
	s = ft_strlen(path_old);
	str = (char *) malloc(sizeof(char) * (s + 2));
	ft_memcpy(str, path_old, s);
	str[s] = '/';
	str[s + 1] = 0;
	if (*path == '.' && *(path + 1) == '/')
		new_path = ft_strjoin(str, path + 2);
	else
		new_path = ft_strjoin(str, path);
	free(str);
	return (new_path);
}
