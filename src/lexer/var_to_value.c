/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_to_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-barr <ade-barr@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:14:01 by ade-barr          #+#    #+#             */
/*   Updated: 2023/10/31 12:58:31 by ade-barr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	ft_printf("i is %d after count \n", i);
	return (i);
}

static char	*store_word(char *str)
{
	int	i;
	int	j;
	char	*word;

	i = 0;
	i = find_end(str);
	word = malloc(sizeof(char) * i + 2);
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
		char	*ret_str;

		ret_str = ft_calloc(sizeof(char), 1);
		if (str[*i + 1] && str[*i + 1] == '?') 
		{
			ft_printf("exit status\n");
			(*i)++;
		}
		else if (str[*i + 1] && ft_isalpha(str[*i + 1]))
		{
			word = store_word(str + *i + 1); //saves into 'word' whatever comes after '$'
			*i += ft_strlen(word);
			word = get_env_var(env, word); //searches for a env called 'word' and then replaces it with its value
			if (word)
			{
				ret_str = ft_strjoin(temp, word);
				return (ret_str);
			}
			ret_str = ft_strjoin(temp, "");
		}
		else if (str[*i + 1] && ft_isdigit(str[*i + 1]))
			ft_printf("\n\nsyntax_error_number\n\n"); //syntax_error('$');
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
	int	i;
	char	*temp;

	i = 0;
	//ft_printf("\n........................\nvar_to_value input str is = '%s'\n", str);
	temp = ft_calloc(sizeof(char), 1);
	while (str[i])
	{
		if (str[i] && str[i] == '$')
		{
			if (ft_iswhitespace(str[i + 1]) || !str[i + 1])
				temp = ft_strjoin(temp, "$");
			else
				temp = process_var(&i, str, temp, env);
		}
		else if (str[i] == '"' && str[i + 1] != '"')
		{
			i++;
			if (str[i] && str[i] == '$')
				temp = process_var(&i, str, temp, env);
			else
				temp = ft_strjoin(temp, ft_substr(str, i, 1));
		}
		else if (str[i])
			temp = ft_strjoin(temp, ft_substr(str, i, 1));
		i++;
	}
	//ft_printf("string after var_to_value = '%s'\n", temp);
	return (temp);
}
