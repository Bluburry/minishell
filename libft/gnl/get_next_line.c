/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:41:46 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/01/04 16:29:57 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*append_static(char *static_string, char *append_str)
{
	char	*str;

	if (!static_string)
	{
		str = (char *) malloc((ft_strlen_gnl(append_str) + 1) * sizeof(char));
		ft_memcpy_gnl(str, append_str, ft_strlen_gnl(append_str));
	}
	else
	{
		str = ft_strjoin_gnl(static_string, append_str);
		free(static_string);
	}
	return (str);
}

char	*search_newline(int fd, char *static_string, int buffer_size)
{
	char	*buffer_str;
	ssize_t	size_read;

	if (static_string && ft_strrchr_gnl(static_string, '\n'))
		return (static_string);
	buffer_str = (char *) malloc((buffer_size + 1) * sizeof(char));
	if (!buffer_str)
		return (NULL);
	size_read = buffer_size;
	while (!ft_strrchr_gnl(static_string, '\n') && size_read == buffer_size)
	{
		size_read = read(fd, buffer_str, buffer_size);
		if (size_read < 0 || (!static_string && size_read == 0))
		{
			free(buffer_str);
			free(static_string);
			return (NULL);
		}
		buffer_str[size_read] = 0;
		static_string = append_static(static_string, buffer_str);
		if (!*static_string)
			break ;
	}
	free(buffer_str);
	return (static_string);
}

char	*get_string(char *static_string)
{
	char	*str;
	int		i;

	if (!ft_strrchr_gnl(static_string, '\n'))
		i = ft_strlen_gnl(static_string);
	else
	{
		i = 0;
		while (static_string[i] && static_string[i] != '\n')
			i++;
		i++;
	}
	str = (char *) malloc ((i + 1) * sizeof(char));
	ft_memcpy_gnl(str, static_string, i);
	return (str);
}

char	*alter_static(char *static_string)
{
	char	*str;
	int		i;
	int		size;

	size = ft_strlen_gnl(static_string);
	i = 0;
	while (static_string[i] && static_string[i] != '\n')
		i++;
	if (!static_string[i] || !static_string[i + 1])
	{
		free(static_string);
		return (NULL);
	}
	i++;
	str = (char *) malloc ((size - i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy_gnl(str, static_string + i, size - i);
	free(static_string);
	return (str);
}

char	*get_next_line(int fd, int buffer_size)
{
	static char		*static_string;
	char			*str;

	if (fd < 0 || buffer_size < 1)
		return (NULL);
	static_string = search_newline(fd, static_string, buffer_size);
	if (!static_string)
		return (NULL);
	str = get_string(static_string);
	static_string = alter_static(static_string);
	return (str);
}
