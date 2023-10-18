#include "minishell.h"

int	count_inouts(char *str, char c)
{
	int	len;

	len = 0;
	while (*str)
	{
		str += move_in_str(str, c);
		if (*str == c && *(str + 1) == c)
			syntax_error(c);
		if (*(str - 1) == c)
			len++;
		if (*(str - 1) == c && *str == c)
			str++;	
	}
	return (len);
}

int	count_inout_tokens(char **input)
{
	int		len;
	int		i;
	char	*tmp;
	int		rtn;

	len = 0;
	i = 0;
	while (input[i])
	{
		tmp = input[i++];
		if (*tmp == '\'' || *tmp == '\"')
			len++;
		else
		{
			if (*tmp != '<' && *tmp != '>')
				len++;
			if((rtn = count_inouts(tmp, '<') + count_inouts(tmp, '>')))
			{

				if(tmp[ft_strlen(input[i]) - 1] != '<' && tmp[ft_strlen(input[i]) - 1] != '>')
					len++;
				len += rtn;
			}
		}
	}
	return (len);
}

char	**split_inout_tokens(char **input)
{
	int		end;
	char	**tokens;
	char	**ptr;
	char	*str;

	tokens = malloc((count_inout_tokens(input) + 1) * sizeof(char *));
	if (!tokens)
		return (0);
	ptr = tokens;
	while (*input)
	{
		if (**input == '\'' || **input == '\"')
		{
			*ptr = *input;
			ptr++;
		}
		else
		{
			str = *input;
			while (*str)
			{
				end = 0;
				if ((*str == '<' && *(str + 1) == '<') || (*str == '>' && *(str + 1) == '>'))
					end = 2;
				else if (*str == '<' || *str == '>')
					end = 1;
				else
				{
					while (str[end] && str[end] != '<' && str[end] != '>')
						end++;
				}
				*ptr = create_token(str, end);
				if (**ptr)
					ptr++;
				else
					free(*ptr);
				str += end;
			}
		}
		input++;
	}
	*ptr = NULL;
	return (tokens);
}
