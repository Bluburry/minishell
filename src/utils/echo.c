#include "minishell.h"

int	ft_echo(char **argv)
{
	int	i;
	int	n;

	if (!argv[1])
	{
		printf("\n");
		return (0);
	}
	n = ft_strncmp(argv[1], "-n", 2);
	if (n == 0)
		i = 2;
	else
		i = 1;
	while (argv[i])
	{
		printf("%s", argv[i++]);
		if (argv[i])
			printf(" ");
	}
	if (n != 0)
		printf("\n");
	return (0);
}

/* int	main(int argc, char **argv)
{
	ft_echo(argv);
	(void)argc;
	return (0);
} */
