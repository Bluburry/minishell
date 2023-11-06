#include "minishell.h"

static int	bit_store(char *str)
{
	int	nbr;
	int	ret_nbr;

	nbr = atoi(str);
	if (ft_strncmp(str, ft_itoa(nbr), ft_strlen(str)))
	{
		ft_printf("\nsyntax_error_bitstore()\n");
		return (-1);
	}
	ret_nbr = 0;
	ret_nbr = nbr & 0xFF;
	return (ret_nbr);
}

int	ft_exit(char *argv)
{
	ft_printf("post binary %i\n", bit_store(argv));
	return (0);
}
