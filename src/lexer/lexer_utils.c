#include "minishell.h"

int	is_space(char c)
{
	if (c == ' ' || (c > 6 && c < 14))
		return (1);
	return (0);
}

char	**check_for_quotes(char *input, char **ptr, int *flag)
{
	if (*input == '\'' || *input == '\"')
	{
		*ptr = ft_strdup(input);
		ptr++;
		*flag = 1;
	}
	return (ptr);
}

void	dcp_cleaner(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}
// type == 1 -> unexpected token
// type == 2 -> no matching closing quotes
// type == 3 -> unexpected end of file
void	syntax_error(int type, char c, t_env *env)
{
	if (type == 1)
	{
		printf("syntax error near unexpected token ");
		if (c == '\n')
			printf("`newline'\n");
		else
			printf("`%c'\n", c);
	}
	if (type == 2)
		printf("unexpected EOF while looking for matching `%c'\n", c);
	if (type == 3)
		printf("syntax error: unexpected end of file\n");
	waiting_for_input(env);
}
