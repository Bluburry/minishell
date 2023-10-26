#include "libft.h"
#include "macros.h"
#include "minishell.h"

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
	i = 0;
	while (prev != size && str_cmp(strs[index], strs[prev]) <= 0)
		index++;
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
	int	c;

	i = 0;
	j = 0;
	c = 0;
	while (i < n)
	{
		dest[j++] = src[i++];
		if (src[i - 1] == '=' && c == 0)
		{
			dest[j++] = '"';
			c++;
		}
	}
	if (c == 1)
	{
		dest[j] = '"';
		dest[++j] = '\0';
	}
	else
		dest[j] = '\0';
}

void	copy_char_matrix_ordered(char **mat, char **new_mat, int size)
{
	int		i;
	int		j;
	int		z;
	size_t	s;

	j = -1;
	i = size;
	while (++j < size)
	{
		i = ordered_index(mat, size, i);
		s = ft_strlen(mat[i]);
		z = EXTRA_SIZE_EXPORT + s + 1;
		if (ft_strrchr(mat[i], '='))
			z += 2;
		new_mat[j] = (char *) malloc(sizeof(char) * (z));
		ft_memcpy(new_mat[j], "declare -x ", EXTRA_SIZE_EXPORT);
		memcpy_export(new_mat[j]+EXTRA_SIZE_EXPORT, mat[i], s);
	}
}

char	**export_string(t_env *env)
{
	char	**ret;

	ret = (char **) malloc(sizeof(char *) * env->size);
	copy_char_matrix_ordered(env->vars, ret, env->size);
	return (ret);
}