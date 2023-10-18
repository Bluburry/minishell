#include "minishell.h"

int	is_token_end(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
/* 	else if (c == '|')
		return (-1); */
	return (0);
}

void	syntax_error(char c)
{
	printf("syntax error near unexpected token `%c'\n", c);
	waiting_for_input();
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
	//free(tmp); //!!causing double free
	return (token);
}

void	print_tokens(char **tokens)
{
	while (*tokens)
	{
		printf("%s\n", *tokens);
		tokens++;
	}
}

char	**tokens_init(char *input)
{
	char	**tokens;
	char	**ptr;
	char	*tmp;
	char	**ptr2;
	char	**ptr3;

	tmp = ft_strtrim(input, " \a\b\t\n\v\f\r");
	free(input);
	ptr = split_quotes_tokens(tmp);
	printf("\n\n--quotes--\n");
	print_tokens(ptr);
	ptr2 = split_space_tokens(ptr);
	printf("\n\n--spaces--\n");
	print_tokens(ptr2);
	ptr3 = split_inout_tokens(ptr2);
	printf("\n\n--inout--\n");
	print_tokens(ptr3);
	tokens = split_char_tokens(ptr3, '|');
	printf("\n\n--char--\n");
	print_tokens(tokens);
	printf("\n\n--returned--\n");
	//free(ptr);
	//ptr =
	return (tokens);
}

void	parser(char *input)
{
	char	**tokens;

	if (!input || !(*input))
		return ;
	tokens = tokens_init(input);
	while (*tokens)
	{
		printf("%s\n", *tokens);
		tokens++;
	}
	//!!! call funtion that executes instructions HERE
	//free(input); //!! causing double free
}


//   hsdfg kfg ikdf|fdsf | 648"dfhgkdjgdf'g"                  dfgdrgdh>>dg <gdf << |> ''      
