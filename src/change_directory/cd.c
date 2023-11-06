#include "minishell.h"

void	cd_error(void)
{

}

// missing home directory check "~/something"
// and check if path ends with "/" (need to remove)
// ^ trying a fix in change_path
void	cd(t_env *env, const char *path)
{
	t_path	p;
	char	*str;

	if (!path || !*path || (*path == '~' && !*(path + 1)))
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
		str = relative_path(env, path);
		change_pwd(env, str);
		free (str);
	}
}
