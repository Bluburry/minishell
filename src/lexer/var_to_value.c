/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_to_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-barr <ade-barr@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:14:01 by ade-barr          #+#    #+#             */
/*   Updated: 2023/10/30 01:29:14 by ade-barr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//mallocs and stores any valid input after '$' [QUESTION]: where do i free this? To be continued... 
//int i ---------- index counter to malloc correct size
//int j ---------- index that starts from 0 again, to copy 'str' into 'word' up to 'i' size
//char *word ----- string that stores anything after the '$' untill it finds a space (doesnt copy the space)
static char	*store_word(char *str)
{
	int	i;
	int	j;
	char	*word;

	i = 0;
	while (!ft_iswhitespace(str[i]) && str[i] != '$' && str[i])
	{
		ft_printf("str[i] = %c\n", str[i]);
		i++;
	}
	i--;
	word = malloc(sizeof(char) * i);
	j = 0;
	while (str[j] && j <= i)
	{
		word[j] = str[j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

static char	*store_special(char *str)
{
	int	i;
	int	j;
	char	*word;

	i = 0;
	while (str[i] != '"')
		i++;
	i--;
	word = malloc(sizeof(char) * i);
	j = -1;
	while (str[++j] && j <= i)
		word[j] = str[j];
	word[j] = '\0';
	return (word);
}


static char	*process_var(int *i, char *str, char *temp, t_env *env)
{
		char	*word;

		ft_printf("process temp = %s\n", temp);
		if (str[*i + 1] == '?') 
		{
			ft_printf("exit status\n");
			(*i)++;
		}
		else if (ft_isalpha(str[*i + 1]))
		{
			word = store_word(str + *i + 1); //saves into 'word' whatever comes after '$'
			*i += ft_strlen(word);
			word = get_env_var(env, word); //searches for a env called 'word' and then replaces it with its value
			if (ft_strlen(word) > 0)
				temp = ft_strjoin(temp, word);
				
		}
		else if (ft_isdigit(str[*i + 1]))
			ft_printf("\n\nsyntax_error_number\n\n"); //syntax_error('$');
		else
			ft_printf("\n\nsyntax_error\n\n");
		return (temp);
}

char	*var_to_value(char *str, t_env *env)
{
	int	i;
	char	*word;
	char	*temp;

	i = -1;
	temp = ft_calloc(sizeof(char), 1);
	while (str[++i])
	{
		
		if (str[i] == '$')
			temp = process_var(&i, str, temp, env);
		else if (str[i] == '"' && str[i + 1] != '"')
		{
			//check end quote
			word = store_special(str + i + 1); //saves into 'word' whatever comes after '$'
			i += ft_strlen(word);
			temp = ft_strjoin(temp, word);
			ft_printf("word is = %s\n", word);
		}
		else
			temp = ft_strjoin(temp, ft_substr(str, i, 1));
	}
	return (temp);
}
