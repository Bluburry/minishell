#include "libft.h"
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

#define PTH "/tmp/MS_HEREDOC"
#define ERR_STR "Warning: heredoc delimited by end of file instead of %s\n"

int	redir_heredoc(char *stop, t_data *d)
{
	auto int fl = open(PTH, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	auto char *str = NULL;
	if (fl == -1)
		return (printf("Error opening temp file.\n"), 0);
	dup2(d->stdin, STDIN_FILENO);
	while (g_sig != SIGINT)
	{
		//printf("∙ ");
		//str = ft_gnl_reset(fl, false);
		//auto char *temp = ft_strrchr(str, '\n');
		//if (temp != NULL)
		//	*temp = '\0';
		str = readline("∙ ");
		if (str == NULL)
		{
			printf(ERR_STR, stop);
			break ;
		}
		else if (!ft_strcmp(str, stop))
			break ;
		ft_putstr_fd(str, fl);
		ft_putstr_fd("\n", fl);
		free(str);
	}
	free(str);
	//ft_gnl_reset(fl, true);
	close(fl);
	fl = open(PTH, O_RDONLY, 0);
	if (fl == -1)
		return (printf("Error opening temp file.\n"), 0);
	return (unlink(PTH), dup2(fl, STDIN_FILENO), close(fl), 1);
}
