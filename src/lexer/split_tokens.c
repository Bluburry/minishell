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
	unsigned int	i;

	token = malloc((len + 1) * sizeof(char));
	if (token == 0)
		return (0);
	i = 0;
	while (i < len && str[i])
	{
		token[i] = str[i];
		i++;
	}
	token[i] = '\0';
	return (token);
}

void	remove_quotes_from_tokens(char **input)
{
	char	c;
	char	*tmp;

	while (*input)
	{
		if (**input == '\'' || **input == '\"')
		{
			tmp = ft_strdup(*input);
			c = **input;
			*tmp = 31;
			free(*input);
			*input = ft_strtrim(tmp, &c);
			free(tmp);
		}
		input++;
	}
}

char	**tokens_init(char *input, t_env *env)
{
	char	**ptr;
	char	*tmp;
	char	**ptr2;

	tmp = ft_strtrim(input, " \a\b\t\n\v\f\r");
	//free(input);
	ptr = split_quotes_tokens(tmp);
	free(tmp);
	if (ptr == NULL)
		return (NULL);
	ptr2 = expand_var_tokens(ptr, env);
	dcp_cleaner(ptr);
	ptr = split_char_tokens(ptr2, ' ');
	dcp_cleaner(ptr2);
	ptr2 = split_inout_tokens(ptr);
	dcp_cleaner(ptr);
	if (ptr2 == NULL)
		return (NULL);
	ptr = split_char_tokens(ptr2, '|');
	dcp_cleaner(ptr2);
	remove_quotes_from_tokens(ptr);
	ptr2 = merge_tokens_cleanup(ptr);
	dcp_cleaner(ptr);
	return (ptr2);
}
