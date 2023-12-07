#include "minishell.h"

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

bool	create_comm_list(t_data *data)
{
	int32_t		n;
	uint32_t	st;

	data->cmds = create_cmda(list_len(data->strlist));
	if (data->cmds == NULL || data->strlist == NULL)
		return (free(data->cmds), data->cmds = NULL, dcp_cleaner(data->strlist),
			data->strlist = NULL, false);
	data->pipe_n = count_pipes(data->strlist);
	n = find_strn_to_pipe(&data->strlist[0]);
	st = 0;
	while (n != -1)
	{
		if (insert_redirs(data->cmds, &data->strlist[st], n) == false)
			return (free(data->cmds), data->cmds = NULL,
				dcp_cleaner(data->strlist), data->strlist = NULL, false);
		data->cmds->tks[data->cmds->size++] = (t_tok){r_pipe, NULL, NULL};
		if (insert_name_args(data->cmds, &data->strlist[st], n) == false)
			return (free(data->cmds), data->cmds = NULL,
				dcp_cleaner(data->strlist), data->strlist = NULL, false);
		st += n + 1;
		n = find_strn_to_pipe(&data->strlist[st]);
	}
	n = list_len(data->strlist) - st;
	if (insert_redirs(data->cmds, &data->strlist[st], n) == false)
		return (free(data->cmds), data->cmds = NULL,
			dcp_cleaner(data->strlist), data->strlist = NULL, false);
	if (insert_name_args(data->cmds, &data->strlist[st], n) == false)
		return (free(data->cmds), data->cmds = NULL,
			dcp_cleaner(data->strlist), data->strlist = NULL, false);
	return (true);
}
