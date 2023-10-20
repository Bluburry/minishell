#include "minishell.h"

int	is_token_end(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

int	move_in_str(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		i++;
	return (i);
}

char	*create_token(const char *str, size_t len)
{
	char			*token;
	char			*tmp;
	unsigned int	i;

	tmp = malloc((len + 1) * sizeof(char));
	if (tmp == 0)
		return (0);
	i = 0;
	while (i < len && str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	token = ft_strtrim(tmp, " \a\b\t\n\v\f\r");
	free(tmp);
	return (token);
}

char	**tokens_init(char *input)
{
	char	**tokens;
	char	**ptr;
	char	*tmp;
	char	**ptr2;
	int		flag;

	tmp = ft_strtrim(input, " \a\b\t\n\v\f\r");
	free(input);
	flag = 0;
	ptr = split_quotes_tokens(tmp, &flag);
	free(tmp);
	if (flag)
		waiting_for_input(); // !! change for error message
	ptr2 = split_space_tokens(ptr);
	dcp_cleaner(ptr);
	ptr = split_inout_tokens(ptr2);
	dcp_cleaner(ptr2);
	tokens = split_char_tokens(ptr, '|');
	dcp_cleaner(ptr);
	return (tokens);
}
