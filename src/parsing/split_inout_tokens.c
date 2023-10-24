#include "minishell.h"

int	count_inouts(char *str, char c)
{
	int	len;

	len = 0;
	while (*str)
	{
		str += move_in_str(str, c);
		if (*str == c && *(str + 1) == c)
			syntax_error(1, &c);
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
	i = -1;
	while (input[++i])
	{
		tmp = input[i];
		if (*tmp == '\'' || *tmp == '\"')
			len++;
		else
		{
			if (*tmp != '<' && *tmp != '>')
				len++;
			rtn = count_inouts(tmp, '<') + count_inouts(tmp, '>');
			if (rtn)
				if (tmp[ft_strlen(tmp) - 1] != '<'
					&& tmp[ft_strlen(tmp) - 1] != '>')
					len++;
			len += rtn;
		}
	}
	return (len);
}

char	**test(char *input, char **ptr)
{
	int		end;
	char	*str;

	str = input;
	while (*str)
	{
		end = 0;
		if ((*str == '<' && *(str + 1) == '<')
			|| (*str == '>' && *(str + 1) == '>'))
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
	return (ptr);
}

char	**split_inout_tokens(char **input)
{
	char	**tokens;
	char	**ptr;
	int		flag;

	tokens = malloc((count_inout_tokens(input) + 1) * sizeof(char *));
	if (!tokens)
		return (0);
	ptr = tokens;
	while (*input)
	{
		flag = 0;
		ptr = check_for_quotes(*input, ptr, &flag);
		if (flag == 0)
			ptr = test(*input, ptr);
		input++;
	}
	*ptr = NULL;
	return (tokens);
}
