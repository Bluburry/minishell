#include "libft.h"
#include "minishell.h"
#include "structures.h"
#include <stdint.h>

// counts the number of items in the string list
static uint32_t	list_len(char **list)
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
int32_t	find_strn_to_pipe(char **list, uint32_t start); //maybe instead of receiving a list and a start, it just receives the address at that specific point

// counts how many arguments there are in a phrase
// ignores the first word int the phrase since it's an executable
// ignores >, <, >>, << and the word following it
// returns the number of args for the program to be executed
uint32_t	count_args(char **list, uint32_t n);

// counts the number of pipes that exists in the entire list of strings
// returns the number of pipes
// this should probably be saved in data
uint32_t	count_pipes(char **list);

#define ERR_REDIR "Syntax Error: No file for redirection\n"

static inline bool redirs_helper(t_etok type, t_cmda *cmds, char **list, uint32_t *i)
{
	if (list[*i + 1] != NULL)
		cmds->tks[cmds->size++] = (t_tok){type, list[++(*i)], NULL};
	else
		return (printf(ERR_REDIR), false);
	return (true);
}

// returns false if there's an error
bool	insert_redirs(t_cmda *cmds, char **list, uint32_t n)
{
	uint32_t	i;

	i = 0;
	while (i < n)
	{
		if (ft_strncmp(">", list[i], 1) == 0)
			if (redirs_helper(r_out, cmds, list, &i) != true)
				return (false);
		else if (ft_strncmp("<", list[i], 1) == 0)
			if (redirs_helper(r_in, cmds, list, &i) != true)
				return (false);
		else if (ft_strncmp(">>", list[i], 2) == 0)
			if (redirs_helper(r_append, cmds, list, &i) != true)
				return (false);
		else if (ft_strncmp("<<", list[i], 2) == 0)
			if (redirs_helper(r_heredoc, cmds, list, &i) != true)
				return (false);
		i++;
	}
	return (true);
}


/* bool	insert_redirs(t_cmda *cmds, char **list, uint32_t n)
{
	uint32_t	i;

	i = 0;
	while (i < n)
	{
		if (ft_strncmp(">", list[i], 1) == 0)
		{
			if (list[i + 1] != NULL)
				cmds->tks[cmds->size++] = (t_tok){r_out, list[++i], NULL};
			else
				return (printf(ERR_REDIR), false);
		}
		else if (ft_strncmp("<", list[i], 1) == 0)
		{
			if (list[i + 1] != NULL)
				cmds->tks[cmds->size++] = (t_tok){r_in, list[++i], NULL};
			else
				return (printf(ERR_REDIR), false);
		}
		else if (ft_strncmp(">>", list[i], 2) == 0)
		{
			if (list[i + 1] != NULL)
				cmds->tks[cmds->size++] = (t_tok){r_append, list[++i], NULL};
			else
				return (printf(ERR_REDIR), false);
		}
		else if (ft_strncmp("<<", list[i], 2) == 0)
		{
			if (list[i + 1] != NULL)
				cmds->tks[cmds->size++] = (t_tok){r_heredoc, list[++i], NULL};
			else
				return (printf(ERR_REDIR), false);
		}
		i++;
	}
	return (true);
} */

void	insert_name_args(t_cmda *cmds, char **list, uint32_t n);

bool	create_comm_list(t_data *data)
{
	int32_t		n;

	data->cmds = create_cmda(list_len(data->strlist));
	if (data->cmds == NULL || data->strlist == NULL)
		return (free(data->cmds), free(data->strlist), false); // needs to be set to 0
	// go through phrases
	n = find_strn_to_pipe(data->strlist, 0);
	while (n != -1)	
	{
		insert_redirs(data->cmds, data->strlist, n); // data->cmds->size is used like an i and should be modified internally
		data->cmds->tks[data->cmds->size++] = (t_tok){r_pipe, NULL, NULL};
		insert_name_args(data->cmds, data->strlist, n); // data->cmds->size is used like an i and should be modified internally
		n = find_strn_to_pipe(data->strlist, n + 1);
	}
	insert_redirs(data->cmds, data->strlist, n); // data->cmds->size is used like an i and should be modified internally
	insert_name_args(data->cmds, data->strlist, n);
	return (true);
}
