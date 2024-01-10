#include "minishell.h"

//checks if the string passed is a relative path, or an absolute path
//and if so, takes only the last part after the last /
static char	*chk_path(char *str)
{
	char	*sub_str;

	sub_str = ft_strrchr(str, '/');
	if (sub_str == NULL)
		return (str);
	sub_str++;
	if (sub_str[0] == '\0')
		return (NULL);
	return (sub_str);
}

static char	*path_or_builtin(t_env *env, char *str)
{
	if (ft_strncmp(str, "echo", 5) == 0
		|| ft_strncmp(str, "pwd", 4) == 0
		|| ft_strncmp(str, "env", 4) == 0
		|| ft_strncmp(str, "unset", 6) == 0
		|| ft_strncmp(str, "export", 8) == 0
		|| ft_strncmp(str, "exit", 5) == 0
		|| ft_strncmp(str, "cd", 3) == 0)
		return (ft_strdup(str));
	return (find_exe_path(env, str));
}

static inline bool	check_redir(char *str)
{
	if (ft_strncmp(">", str, 1) == 0 || ft_strncmp("<", str, 1) == 0
		|| ft_strncmp(">>", str, 2) == 0 || ft_strncmp("<<", str, 2) == 0)
		return (true);
	return (false);
}

#define ESTR "%s is not a valid executable\n"

static inline bool	ret_stuff(t_cmda *c, uint32_t j, char *str)
{
	c->tks[c->size].arglist[j] = NULL;
	printf(ESTR, chk_path((remc(str))));
	return (false);
}

// insert_name_args(cmds, &list[i], n)
// needs to check when check_if_path returns NULL
//true if no errors   c->tks[c->size - 1].path != NULL
bool	insert_name_args(t_cmda *c, char **l, uint32_t n, t_env *env)
{
	auto int32_t i = -1;
	auto uint32_t j = count_args(l, n);
	auto bool path_added = false;
	if (j == 0)
		return (true);
	c->tks[c->size].arglist = malloc(sizeof(char *) * (j + 1));
	j = 0;
	if (c->tks[c->size].arglist == NULL)
		return (false);
	while (++i < (int32_t)n)
	{
		if (check_redir(l[i]))
			i++;
		else if (path_added == false)
		{
			path_added = true;
			c->tks[c->size].path = path_or_builtin(env, remc(l[i]));
			if (c->tks[c->size].path == NULL)
				return (ret_stuff(c, j, l[i]));
			c->tks[c->size].arglist[j++] = ft_strdup(chk_path((remc(l[i]))));
		}
		else
			c->tks[c->size].arglist[j++] = ft_strdup(remc(l[i]));
	}
	return (c->tks[c->size].type = exec, c->tks[c->size++].arglist[j] = 0, 1);
}

//c->tks[c->size++].arglist[j] = NULL;
//return (c->tks[c->size - 1].type = exec, true);
//return (c->tks[c->size].arglist[j] = NULL,
//	printf(ESTR, chk_path((remc(l[i])))), false);