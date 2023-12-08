#include "minishell.h"

/**
 * @brief checks if passed string is a valid parameter
 * @param path string path to check
 * @return -1 if not a path, 0 if path, 1 if file
 */
int	check_path(char *path)
{
	struct stat	*bs;
	int			ret;

	bs = (struct stat *) malloc(sizeof(struct stat));
	if (stat(path, bs) == -1)
	{
		printf("Invalid directory.\n");
		ret = -1;
	} 
	else
		ret = 0;
	if (ret != -1 && S_ISREG(bs->st_mode))
		ret = 1;
	return (free(bs), ret);
}
