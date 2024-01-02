#include "minishell.h"

// counts how many arguments there are in a phrase
// ignores the first word int the phrase since it's an executable
// ignores >, <, >>, << and the word following it
// returns the number of args for the program to be executed
// the list needs to be passed as the correct adress
// e.g. count_args(&list[5], 5) to count the arguments starting from the 6th idx
static uint32_t	count_args(char **l, uint32_t n)
{
	uint32_t	i;
	uint32_t	count;

	i = 0;
	count = 0;
	while (i < n)
	{
		if (ft_strncmp(">", l[i], 1) == 0 || ft_strncmp("<", l[i], 1) == 0
			|| ft_strncmp(">>", l[i], 2) == 0 || ft_strncmp("<<", l[i], 2) == 0)
			i++;
		else
			count++;
		i++;
	}
	return (count);
}

//checks if the string passed is a relative path, or an absolute path
//and if so, takes only the last part after the last /
static char	*check_if_path(char *str)
{
	char	*sub_str;

	sub_str = ft_strrchr(str, '/');
	if (sub_str == NULL)
		return (ft_strdup(str));
	sub_str++;
	if (sub_str[0] == '\0')
		return (NULL);
	return (ft_strdup(sub_str));
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
		return (str);
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
			c->tks[c->size].path = ft_strdup(path_or_builtin(env, remc(l[i])));
			if (c->tks[c->size].path == NULL)
				return (printf(ESTR, check_if_path((remc(l[i])))), false);
			c->tks[c->size].arglist[j++] = check_if_path((remc(l[i]))); 
		}
		else
			c->tks[c->size].arglist[j++] = ft_strdup(remc(l[i]));
	}
	return (c->tks[c->size].type = exec, c->tks[c->size++].arglist[j] = 0, 1);
}

//c->tks[c->size++].arglist[j] = NULL;
//return (c->tks[c->size - 1].type = exec, true);