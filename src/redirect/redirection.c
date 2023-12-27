#include "minishell.h"

int	redir_appd(char *path)
{
	int	file;

	file = open(path, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (file == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
	return (0);
}

int	redir_trunc(char *path)
{
	int	file;

	file = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (file == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
	return (0);
}

int	redir_in(char *path)
{
	int		file;
	char	c;

	file = open(path, O_RDONLY, 0666);
	if (file == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	dup2(file, STDIN_FILENO);
	while (read(STDIN_FILENO, &c, 1) > 0)
		write(STDOUT_FILENO, &c, 1);
	close(file);
	return (0);
}
