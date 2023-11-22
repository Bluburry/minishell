#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "libft.h"

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

#endif