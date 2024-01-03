#include "minishell.h"

int	redir_appd(char *path)
{
	int	file;

	file = open(path, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (file == -1)
	{
		perror("Error opening file");
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
		perror("Error opening file");
		return (0);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
	return (1);
}

int	redir_in(char *path)
{
	int		file;

	file = open(path, O_RDONLY, 0666);
	if (file == -1)
	{
		perror("Error opening file");
		return (0);
	}
	dup2(file, STDIN_FILENO);
	close(file);
	return (1);
}

int	redir_heredoc(char *stop)
{
	int		fl;
	char	*str;

	str = pwd();
	fl = open(str, O_TMPFILE | O_RDWR, 0666);
	free(str);
	if (fl == -1)
	{
		perror("Error opening temp file.");
		return (0);
	}
	str = NULL;
	while (g_sig != SIGINT)
	{
		str = readline("> ");
		if (!strcmp(str, stop))
			break ;
		ft_putstr_fd(str, fl);
	}
	if (g_sig != SIGINT)
		dup2(fl, STDIN_FILENO);
	close(fl);
	return (1);
}
