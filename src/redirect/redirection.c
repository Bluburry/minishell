#include "minishell.h"

int	redir_appd(char *path)
{
	int	file;

	file = open(path, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (file == -1)
	{
		printf("Error opening file\n");
		return (0);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
	return (1);
}

int	redir_trunc(char *path)
{
	int	file;

	file = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (file == -1)
	{
		printf("Error opening file\n");
		return (0);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
	return (1);
}

int	redir_in(char *path)
{
	int		file;

	file = open(path, O_RDONLY, 0);
	if (file == -1)
	{
		printf("Error opening file\n");
		return (0);
	}
	dup2(file, STDIN_FILENO);
	close(file);
	return (1);
}
