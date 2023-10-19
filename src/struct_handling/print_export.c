#include "../../include/minishell.h"

int	str_cmp(const char *str1, const char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return ((int) (*str1 - *str2));
		str1++;
		str2++;
	}
	if (!*str1 && !*str2)
		return (0);
	else if (!*str1)
		return ((int) (*str2) * -1);
	else
		return ((int) (*str1));
}

int	ordered_index(char **strs, int size, int prev)
{
	int		index;
	int		i;

	index = 0;
	i = -1;
	while (++i < size)
	{
		if (i == index || i == prev)
			continue ;
		else if (str_cmp(strs[index], strs[i]) > 0 && \
			(prev == size || str_cmp(strs[i], strs[prev]) > 0))
			index = i;
	}
	return (index);
}

void	memcpy_export(char *dest, char *src, int n)
{
	int	i;
	int	j;

	if (dest == src || n == 0)
		return ;
	i = 0;
	j = 0;
	while (i < n)
	{
		if (i == n - 1)
		{
			dest[j++] = '"';
			dest[j++] = src[i++];
			break ;
		}
		dest[j++] = src[i++];
		if (src[i - 1] == '=')
			dest[j++] = '"';
	}

}

void	copy_char_matrix_ordered(char **mat, char **new_mat, int size)
{
	int		i;
	int		j;
	size_t	s;
	size_t	z;

	j = -1;
	i = size;
	z = ft_strlen("declare -x ");
	while (++j < size)
	{
		i = ordered_index(mat, size, i);
		s = ft_strlen(mat[i]) + 1;
		new_mat[j] = (char *) malloc(sizeof(char) * (s + z + 2));
		ft_memcpy(new_mat[j], "declare -x ", z);
		memcpy_export(new_mat[j]+z, mat[i], s);
	}
}

char	**export_string(t_env *env)
{
	char	**ret;

	ret = (char **) malloc(sizeof(char *) * env->size);
	copy_char_matrix_ordered(env->vars, ret, env->size);
	return (ret);
}