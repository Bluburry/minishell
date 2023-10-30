#include "minishell.h"

// unused, but could be useful
/**
 * @brief returns the total size of a matrix, null terminating 
 * byte included
 * @param mat matrix to count
 * @param size size of matrix
 * @return size of matrix (double, because it could cause overflow)
*/
double	total_size(char **mat, int size)
{
	size_t	ret;
	int		i;

	if (size <= 0)
		return (0);
	i = -1;
	ret = (double) ft_strlen(mat[++i]) + 1;
	while (++i < size)
		ret += (double) ft_strlen(mat[++i]) + 1;
	return (ret);
}

// unused
/**
 * @brief concatenates a matrix into a singles string, 
 * separated by new lines
 * @param str string with memory already allocated
 * @param mat matrix to concatenate
 * @param size size of matrix
*/
void	concatenate_matrix(char *str, char **mat, int size)
{
	int		k;
	int		j;
	int		i;

	i = -1;
	k = 0;
	while (++i < size)
	{
		j = -1;
		while(mat[i][++j])
			str[k++] = mat[i][j];
		str[k++] = '\n';
	}
	str[--k] = 0;
}
