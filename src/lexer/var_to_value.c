#include "minishell.h"
#include <ctype.h>
#include <stdlib.h>

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
			free(ret_str);
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
		free(ret_str);
		return (temp);
	}
	return (ret_str);
}
 
/* int	scan_for_vars(char *str)
{
	int	counter;

	counter = 0;
	while (*str)
	{
		if (*str == '$' && (isalpha(*(str + 1)) || *(str + 1) == '?'))
			counter++;
		str++;
	}
	return (counter);
} */

/*
void	calc_og_strlen(char *str, int *len)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (!(str[i] == '$' && (isalpha(str[i + 1]) || str[i + 1] == '?'))
			&& str[i])
		{
			i++;
			*len += 1;
		}
		if (str[i] == '\0')
			break ;
		if (str[i] == '$' && str[i + 1] == '?')
		{
			i += 2;
			*len += 3;
			continue ;
		}
		i++;
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
	}
}

void	calc_var_len(char *var, t_env *env, int *len)
{
	char	*value;

	value = get_env_var(env, var);
	*len += ft_strlen(value);
}

int	calc_new_strlen(char *str, t_env *env, int num_of_vars)
{
	int		len;
	int		i;
	int		j;
	int		counter;
	char	*var;

	len = 0;
	calc_og_strlen(str, &len);
	var = malloc(sizeof(str) + 1);
	counter = -1;
	i = 0;
	while (++counter < num_of_vars)
	{
		while (!(str[i] == '$' && isalpha(str[i + 1]))
			&& str[i])
			i++;
		j = 0;
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			var[j++] = str[i++];
		var[j] = '\0';
		calc_var_len(var, env, &len);
	}
	free(var);
	return (len);
}

char	*var_to_value(char *str, t_env *env)
{
	int		i;
	char	*new;
	int		num_of_vars;
	int		new_strlen;

	i = 0;
	num_of_vars = scan_for_vars(str);
	if (num_of_vars == 0)
		return (str);
	new = malloc((calc_new_strlen(str, env, num_of_vars) + 1) * sizeof(char));
	while (str[i])
	{
		
	}
	return (new);
} */

/* char	*var_to_value(char *str, t_env *env)
{
	int		i;
	int		end;
	int		start;
	char	*new;
	char	*temp;
	int		num_of_vars;

	num_of_vars = scan_for_vars(str);
	printf("num of vars %d\n", num_of_vars);
	if (num_of_vars == 0)
		return (str);
	printf("yo!\n");
	i = -1;
	end = 0;
	start = 0;
	while (++i < num_of_vars && str[end])
	{
		while (str[end] && str[end] != '$' && str[end + 1] != '?' && !ft_isalpha(str[end + 1]))
			end++;
		if (i == 0)
			temp = ft_substr(str, start, end);
		else
		{
			temp = ft_strjoin(new, ft_substr(str, start, end));
			free(new);
		}
		if (str[end] == '\0')
			return (temp);
		end++;
		start = end;
		while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
			end++;
		new = ft_strjoin(temp, get_env_var(env, ft_substr(str, start, end - start)));
		free(temp);
	}
	return (new);
} */

char	*var_to_value(char *str, t_env *env)
{
	int		i;
	char	*temp;
	char	*new;

	i = 0;
	temp = ft_calloc(sizeof(char), 1);
	while (str[i])
	{
		if (str[i] && str[i] == '$')
		{
			if (ft_iswhitespace(str[i + 1]) || !str[i + 1])
				new = ft_strjoin(temp, "$");
			else
				new = process_var(&i, str, temp, env);
			i++;
		}
		else if (str[i] == '"' && str[i + 1] != '"')
		{
			if (str[i] && str[i] == '$')
			{
				i++;
				new = process_var(&i, str, temp, env);
			}
			else
			{
				new = ft_strjoin(temp, ft_substr(str, i, 1));
				i++;
			}
		}
		else if (str[i])
			new = ft_strjoin(temp, ft_substr(str, i++, 1));
	}
	return (new);
}
