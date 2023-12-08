#include "minishell.h"

/**
 * @brief creates a temporary path by concatenating the path at start and end, 
 * and appending cmd
 * @param path environmental variable of PATH
 * @param cmd executable to find
 * @param start index to start copying path
 * @param send index to stop copying path
 * @return path string created
*/
char	*create_exec_string(const char *path, const char *cmd, int start, int end)
{
	char	*str;
	size_t	s;
	int		dif;

	dif = end - start;
	s = ft_strlen(cmd) + 1;
	str = (char *) malloc(sizeof(char) * (dif + s + 1));
	ft_memcpy(str, path + start, dif);
	str[dif] = '/';
	ft_memcpy(str + dif + 1, cmd, s);
	return (str);
}

/**
 * @brief simple function that checks if a file exists and, if so, 
 * it it's an executable. Differs from check_path by requiring that 
 * struct stat has already been created and is passed as a parameter
 * @param bs struct stat to use in stat function
 * @param exec path to executable
 * @return 0 if it doesn't exist of is not an executable, 0 if executable
*/
int	check_file_executable(struct stat *bs, char *exec)
{
	if (stat(exec, bs) == -1 || !S_ISREG(bs->st_mode) || !(bs->st_mode & S_IXUSR))
		return (0);
	return (1);
}

/**
 * @brief checks the various paths in the PATH env var, appends cmd to the various paths, 
 * and uses the stat function to determine if it's a viable path, and then if it's an
 * executable file
 * @param path environmental variable of PATH
 * @param cmd executable to find
 * @param bs struct stat to use in the stat function
 * @return executable path, or NULL if it no path was found
*/
char	*handle_exe_stats(const char *path, const char *cmd, struct stat *bs)
{
	int		i;
	int		j;
	char	*exec;

	i = 0;
	while (path[i] != 0)
	{
		j = i;
		while (path[j] != 0 && path[j] != ':')
			j++;
		exec = create_exec_string(path, cmd, i, j);
		if (!check_file_executable(bs, exec))
		{
			i = j;
			if (path[j] != 0)
				i++;
			free(exec);
			continue;
		}
		return (free(bs), exec);
	}
	return (free(bs), NULL);
}

/**
 * @brief finds and return the path to the executable passed as parameter
 * @param path environmental variable of PATH
 * @param cmd executable to find
 * @return executable path string that needs to be freed or NULL if not found
*/
char	*find_exe_path(t_env *env, const char *cmd)
{
	struct stat	*bs;
	char		*str;

	if (cmd == NULL || path == NULL)
		return (NULL);
	str = NULL;
	bs = (struct stat *) malloc(sizeof(struct stat));
	if (*cmd == '/')
	{
		s = ft_strlen(cmd) + 1;
		str = (char *) malloc (sizeof(char) * s);
		ft_memcpy(str, cmd, s);
	}
	else if (*cmd == '.' || *cmd == '~')
		str = relative_path(env, cmd);
	if (!str)
		return (handle_exe_stats(get_env_var(env, "PATH"), cmd, bs));
	else if (!check_file_executable(bs, str))
	{
		free(str);
		return (free(bs), NULL);
	}
	return (free(bs), str);
}
