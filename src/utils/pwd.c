#include "minishell.h"

/**
 * @brief gets the current working directory by using 
 * getcwd, the returning string must be freed
 * @return current working directory, needs to be freed 
 * can be NULL if there was an error
*/
char	*pwd()
{
	char	*cwd;
	
	cwd = NULL;
	cwd = getcwd(cwd, PATH_MAX);
	return (cwd);
}
