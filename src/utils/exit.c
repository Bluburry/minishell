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

void	ft_exit(char **argv)
{
	int	exit_code;
	int	check_nbr;

	exit_code = bit_store(argv[1]);
	if (exit_code < 0)
	{
		ft_printf("Error\n");
		exit(1);
	}
	if (exit_code > -1)
	{
		if (argv[2])
			check_nbr = atoi(argv[2]);
		//check if is digit is looking weird...
		if (argv[2] && ft_strncmp(argv[2], ft_itoa(check_nbr), ft_strlen(argv[2])))
			ft_printf("it should wait here");
		else
			exit(exit_code);
	}
	if (argv[2] && !ft_strncmp(argv[2], "|", ft_strlen(argv[2])))
		ft_printf("it should wait here");
	else if (argv[2] && (!ft_strncmp(argv[2], "<", ft_strlen(argv[2]))
		|| !ft_strncmp(argv[2], ">", ft_strlen(argv[2]))
		|| !ft_strncmp(argv[2], ">>", ft_strlen(argv[2]))
		|| !ft_strncmp(argv[2], "<<", ft_strlen(argv[2]))))
	{
		ft_printf("redirect here, then exit");
		//exit();
	}
}
