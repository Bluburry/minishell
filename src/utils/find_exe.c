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
		if (stat(exec, bs) == -1 || !S_ISREG(bs->st_mode) || !(bs->st_mode & S_IXUSR))
		{
			i = j;
			if (path[j] != 0)
				i++;
			free(exec);
			continue;
		}
		free(bs);
		return (exec);
	}
	free(bs);
	return (NULL);
}

/**
 * @brief finds and return the path to the executable passed as parameter
 * @param path environmental variable of PATH
 * @param cmd executable to find
 * @return executable path or NULL if not found
*/
char	*find_exe_path(const char *path, const char *cmd)
{
	struct stat	*bs;

	if (cmd == NULL || path == NULL)
		return (NULL);
	bs = (struct stat *) malloc(sizeof(struct stat));
	return (handle_exe_stats(path, cmd, bs));
}
