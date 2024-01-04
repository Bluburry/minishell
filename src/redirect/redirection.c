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

int	redir_heredoc(char *stop, t_data *d)
{
	int		fl;
	char	*str;

	fl = open("/tmp/MS_HEREDOC", O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fl == -1)
		return (printf("Error opening temp file.\n"), 0);
	dup2(d->stdin, STDIN_FILENO);
	while (g_sig != SIGINT)
	{
		str = readline("∙ ");
		if (str == NULL || !ft_strcmp(str, stop))
			break ;
		ft_putstr_fd(str, fl);
		ft_putstr_fd("\n", fl);
		free(str);
	}
	free(str);
	close(fl);
	fl = open("/tmp/MS_HEREDOC", O_RDONLY, 0);
	if (fl == -1)
		return (printf("Error opening temp file.\n"), 0);
	unlink("/tmp/MS_HEREDOC");
	dup2(fl, STDIN_FILENO);
	close(fl);
	return (1);
}
