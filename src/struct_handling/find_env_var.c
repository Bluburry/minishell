#include "minishell.h"

/**
 * @brief return what is left of the string after fiding the char passed as parameter
 * @param str string to search
 * @param c char to find
 * @return string after char c
*/
char	*str_after_char(char *str, char c)
{
	while (*str && *str != c)
		str++;
	if (!*str)
		return (NULL);
	return (++str);
}

/**
 * @brief matches 2 strings until it finds a specific char in the first one
 * @param str string to search
 * @param c char to stop search
 * @param str_find string that it will try to find in str
 * @return 1 if found, 0 otherwise
*/
int	ft_strchrstr(const char *str, char c, const char *str_find)
{
	if (!*str_find)
		return (0);
	while (*str && *str != c && *str == *str_find)
	{
		str++;
		str_find++;
	}
	if (!*str_find && *str == c)
		return (1);
	return (0);
}

/**
 * @brief iterates throught the strucutre to try and find an environmental 
 * variable matching the str passed as parameter
 * @param env structure
 * @param str string to find
 * @return pointer to string after '=', NULL str was not found
*/
char	*get_env_var(t_env *env, const char *str)
{
	int		i;
	char	*ret;

	ret = NULL;
	i = -1;
	while (++i < env->size)
	{
		if (ft_strchrstr(env->vars[i], '=', str))
			break ;
	}
	if (i >= env->size)
		return (NULL);
	ret = str_after_char(env->vars[i], '=');
	return (ret);
}
