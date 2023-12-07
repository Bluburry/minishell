#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "libft.h"
# include <stdbool.h>
# include <stdint.h>

typedef enum type_of_path
{
	ABSOLUTE,
	RELATIVE,
	NO_PATH,
	INVALID
}	t_path;

typedef struct s_env
{
	char	**vars;
	int		size;
	int		capacity;
}	t_env;

// an enum that decides wether the token is a name or an operator
typedef enum e_etok
{
	none, // *
	exec, // !
	r_pipe,
	r_out,
	r_in,
	r_append,
	r_heredoc,
}	t_etok;
/* 	echo_b, // *
	cd_b, // *
	pwd_b, //*
	export_b, //!
	unset_b, // !
	env_b, //*
	exit_b, // ! */

// a token read by the parser, with the optional path and list of arguments
// used by exec
typedef struct s_tok
{
	t_etok		type;
	char		*path;
	char		**arglist;
}	t_tok;

// the command array, a dynamically allocated array of tokens in the order
// they should be executed
typedef struct s_cmda
{
	t_tok		*tks;
	uint32_t	size;
	uint32_t	cap;
}	t_cmda;

// a struct containing temporary information used when dealing with
// sequential pipes
typedef struct s_pipe
{
	int		prevfd;
	int		ret_status;
}	t_pipe;

// a singleton struct meant to carry global state data across many
// functions
typedef struct s_data
{
	int			fd_in;
	int			ret_status;
	bool		is_first_pipe;
	bool		is_final_pipe;
	bool		is_exiting;
	t_cmda		*cmds;
	char		**strlist;
	char		*path;
	char		**envp;
	t_env		*env;
	uint32_t	pipe_n;
}	t_data;

#endif