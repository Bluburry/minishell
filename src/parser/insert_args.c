#include "libft.h"
#include "minishell.h"
#include <stdbool.h>

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
/* 
// checks to see if the first value passed is a relative or absolute path
// returns true if it is
static bool	check_if_pathname(char *str);

// if the first value of a phrase is a relative or absolute path, returns
// only the filename
// otherwise does nothing and returns the argument
static char	*return_filename(char *str)
{
	if (check_if_pathname(str) == true)
	{
		(void)str;
	}
	return (str);
} */

//checks if the string passed is a relative path, or an absolute path
//and if so, takes only the last part after the last /
char	*check_if_path(char *str)
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

// insert_name_args(cmds, &list[i], n)
bool	insert_name_args(t_cmda *c, char **l, uint32_t n) // needs to add the name of the application as the first item in arglist
{
	int32_t		i;
	uint32_t	j;
	bool		path_added;

	i = -1;
	j = 0;
	path_added = false;
	c->tks[c->size].arglist = malloc(sizeof(char *) * (count_args(l, n) + 1)); // need to see if it`s allocating the right size
	if (c->tks[c->size].arglist == NULL)
		return (false);
	while (++i < (int32_t)n)
	{
		if (ft_strncmp(">", l[i], 1) == 0 || ft_strncmp("<", l[i], 1) == 0
			|| ft_strncmp(">>", l[i], 2) == 0 || ft_strncmp("<<", l[i], 2) == 0)
			i++;
		else if (path_added == false)
		{
			path_added = true;
			c->tks[c->size].path = ft_strdup(l[i]);
			c->tks[c->size].arglist[j++] = check_if_path(l[i]); // needs to check when check_if_path returns NULL
		}
		else
			c->tks[c->size].arglist[j++] = ft_strdup(l[i]);
	}
	c->tks[c->size++].arglist[j] = NULL;
	return (c->tks[c->size - 1].type = exec, true);
}
