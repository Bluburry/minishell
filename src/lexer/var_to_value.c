#include "minishell.h"

static int	find_end(char *str)
{
	int	i;

	i = 0;
	while (!ft_iswhitespace(str[i]) && str[i] != '$'
		&& str[i] != '|' && str[i] != '"'
		&& str[i] != '?' && str[i] != ';'
		&& str[i] != '<' && str[i] != '>'
		&& str[i] != '\'' && str[i])
		i++;
	if (str[i] == '$' || ft_iswhitespace(str[i])
		|| str[i] != '|' || str[i] != '"'
		|| str[i] != '?' || str[i] != ';'
		|| str[i] != '<' || str[i] != '>'
		|| str[i] != '\'')
		i--;
	return (i);
}

static char	*store_word(char *str)
{
	int		i;
	int		j;
	char	*word;

	i = 0;
	i = find_end(str);
	word = ft_calloc(sizeof(char), i + 2);
	if (!word)
		return (NULL);
	j = 0;
	while (str[j] && j <= i)
	{
		word[j] = str[j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

static char	*process_var(int *i, char *str, char *temp, t_env *env)
{
	char	*word;
	char	*env_ptr;
	char	*ret_str;

	ret_str = ft_calloc(sizeof(char), 1);
	if (!ret_str)
		return (NULL);
	if (str[*i + 1] && str[*i + 1] == '?') 
	{
		ft_printf("exit status\n");
		(*i)++;
	}
	else if (str[*i + 1] && ft_isalpha(str[*i + 1]))
	{
		word = store_word(str + *i + 1);
		*i += ft_strlen(word);
		env_ptr = get_env_var(env, word);
		free(word);
		if (env_ptr)
		{
			ret_str = ft_strjoin(temp, env_ptr);
			free(temp);
			return (ret_str);
		}
		ret_str = ft_strjoin(temp, "");
	}
	else if (str[*i + 1] && ft_isdigit(str[*i + 1]))
		ft_printf("\n\nsyntax_error_number\n\n");
	else
	{
		ft_printf("syntax_error\n");
		return (temp);
	}
	if (ret_str)
		return (ret_str);
	return (ret_str);
}

char	*var_to_value(char *str, t_env *env)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_calloc(sizeof(char), 1);
	while (str[i])
	{
		if (str[i] && str[i] == '$')
		{
			if (ft_iswhitespace(str[i + 1]) || !str[i + 1])
				temp = ft_strjoin(temp, "$");
			else
				temp = process_var(&i, str, temp, env);
			i++;
		}
		else if (str[i] == '"' && str[i + 1] != '"')
		{
			if (str[i] && str[i] == '$')
			{
				i++;
				temp = process_var(&i, str, temp, env);
			}
			else
			{
				temp = ft_strjoin(temp, ft_substr(str, i, 1));
				i++;
			}

		}
		else if (str[i])
			temp = ft_strjoin(temp, ft_substr(str, i++, 1));
	}
	return (temp);
}
