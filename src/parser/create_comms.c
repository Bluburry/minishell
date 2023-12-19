#include "minishell.h"
#include <stdbool.h>

// A prhase is everything between pipes
// phrase0 | phrase1 | phrase3

// counts the number of items in the string list
uint32_t	list_len(char **list)
{
	uint32_t	i;

	if (list == NULL)
		return (0);
	i = 0;
	while (list[i] != NULL)
		i++;
	return (i);
}

// returns the size n of items in the substring until the pipe
// e.g. $> ex arg > out arg2 | arg
// if you send that with a start of 0, it'll return 5, as there are
// 5 items starting and including index 0 before the pipe
// which also means the next pipe after index 0 is found at index 5
// if you send that with start 6, you'll get -1, since there are no more pipes
// returns negative if no pipe is found
// find_strn_to_pipe(&list[i])
static int32_t	find_strn_to_pipe(char **list)
{
	uint32_t	i;

	i = 0;
	while (list[i] != NULL)
	{
		if (ft_strncmp("|", list[i], 1) == 0)
			return (i);
		i++;
	}
	return (-1);
}

// counts the number of pipes that exists in the entire list of strings
// returns the number of pipes
// this should probably be saved in data
static uint32_t	count_pipes(char **list)
{
	uint32_t	i;
	uint32_t	count;

	i = 0;
	count = 0;
	while (list[i] != NULL)
	{
		if (ft_strncmp("|", list[i++], 1) == 0)
			count++;
	}
	return (count);
}

static bool	comm_list_helper(t_data *d, int32_t n, uint32_t st, bool ins_pipe) //I need to properly clean cmds
{
	if (insert_redirs(d->cmds, &d->strlist[st], n) == false)
		return (free(d->cmds), d->cmds = NULL,
			dcp_cleaner(d->strlist), d->strlist = NULL, false);
	if (ins_pipe == true)
		d->cmds->tks[d->cmds->size++] = (t_tok){r_pipe, NULL, NULL};
	if (insert_name_args(d->cmds, &d->strlist[st], n) == false)
		return (free(d->cmds), d->cmds = NULL,
			dcp_cleaner(d->strlist), d->strlist = NULL, false);
	return (true);
}

bool	create_comm_list(t_data *d)
{
	int32_t		n;
	uint32_t	st;

	d->cmds = create_cmda(list_len(d->strlist));
	if (d->cmds == NULL || d->strlist == NULL)
		return (free(d->cmds), d->cmds = NULL, dcp_cleaner(d->strlist),
			d->strlist = NULL, false);
	d->pipe_n = count_pipes(d->strlist);
	n = find_strn_to_pipe(&d->strlist[0]);
	st = 0;
	while (n != -1)
	{
		if (comm_list_helper(d, n, st, true) == false)
			return (false);
		st += n + 1;
		n = find_strn_to_pipe(&d->strlist[st]);
	}
	n = list_len(d->strlist) - st;
	if (comm_list_helper(d, n, st, false) == false)
		return (false);
	return (true);
}

/* bool	create_comm_list(t_data *d)
{
	int32_t		n;
	uint32_t	st;

	d->cmds = create_cmda(list_len(d->strlist));
	if (d->cmds == NULL || d->strlist == NULL)
		return (free(d->cmds), d->cmds = NULL, dcp_cleaner(d->strlist),
			d->strlist = NULL, false);
	d->pipe_n = count_pipes(d->strlist);
	n = find_strn_to_pipe(&d->strlist[0]);
	st = 0;
	while (n != -1)
	{
		if (insert_redirs(d->cmds, &d->strlist[st], n) == false)
			return (free(d->cmds), d->cmds = NULL,
				dcp_cleaner(d->strlist), d->strlist = NULL, false);
		d->cmds->tks[d->cmds->size++] = (t_tok){r_pipe, NULL, NULL};
		if (insert_name_args(d->cmds, &d->strlist[st], n) == false)
			return (free(d->cmds), d->cmds = NULL,
				dcp_cleaner(d->strlist), d->strlist = NULL, false);
		st += n + 1;
		n = find_strn_to_pipe(&d->strlist[st]);
	}
	n = list_len(d->strlist) - st;
	if (insert_redirs(d->cmds, &d->strlist[st], n) == false)
		return (free(d->cmds), d->cmds = NULL,
			dcp_cleaner(d->strlist), d->strlist = NULL, false);
	if (insert_name_args(d->cmds, &d->strlist[st], n) == false)
		return (free(d->cmds), d->cmds = NULL,
			dcp_cleaner(d->strlist), d->strlist = NULL, false);
	return (true);
} */
