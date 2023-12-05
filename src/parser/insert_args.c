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
	if (count == 0)
		return (count);
	else
		return (count - 1);
}

// insert_name_args(cmds, &list[i], n)
bool	insert_name_args(t_cmda *c, char **l, uint32_t n)
{
	int32_t		i;
	uint32_t	j;
	bool		path_added;

	i = -1;
	j = 0;
	path_added = false;
	c->tks[c->size].arglist = malloc(sizeof(char *) * count_args(l, n) + 1);
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
			c->tks[c->size].path = l[i];
		}
		else
			c->tks[c->size].arglist[j++] = l[i];
	}
	c->tks[c->size++].arglist[j] = NULL;
	return (true);
}