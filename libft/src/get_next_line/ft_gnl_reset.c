/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_reset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque < remarque@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:15:57 by remarque          #+#    #+#             */
/*   Updated: 2023/09/28 04:30:24 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*buff_joiner(char *buff, char *temp)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!buff)
		buff = ft_calloc(1, 1);
	if (!buff || !temp)
		return (NULL);
	result = malloc(sizeof(char) *(ft_strlen(buff) + ft_strlen(temp) + 1));
	if (!result)
		return (NULL);
	i = -1;
	while (buff[++i])
		result[i] = buff[i];
	j = 0;
	while (temp[j])
		result[i++] = temp[j++];
	result[i] = '\0';
	free(buff);
	return (result);
}

char	*read_into_buff(int fd, char *st_buff)
{
	long			read_bytes;
	char			*temp_buff;

	temp_buff = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!temp_buff)
		return (NULL);
	read_bytes = 1;
	while (read_bytes)
	{
		read_bytes = read(fd, temp_buff, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			free(temp_buff);
			free(st_buff);
			return (NULL);
		}
		temp_buff[read_bytes] = '\0';
		st_buff = buff_joiner(st_buff, temp_buff);
		if (ft_searcher(temp_buff, '\n') || read_bytes < BUFFER_SIZE)
			break ;
	}
	free(temp_buff);
	return (st_buff);
}

char	*get_line_from(char *st_buff)
{
	size_t	i;
	size_t	len;
	char	*line;

	i = -1;
	len = ft_searcher(st_buff, '\n');
	if (len == 0)
		len = ft_strlen(st_buff);
	if (len == 0)
		return (NULL);
	line = malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (++i < len)
		line[i] = st_buff[i];
	line[i] = '\0';
	return (line);
}

char	*remove_line_from(char *buff)
{
	char	*result;
	size_t	buff_i;
	size_t	i;

	if (!buff)
		return (NULL);
	i = 0;
	buff_i = ft_searcher(buff, '\n');
	if (!buff_i)
	{
		free(buff);
		return (NULL);
	}
	result = malloc(sizeof(char) * (ft_strlen(buff) - buff_i + 1));
	if (!result)
		return (NULL);
	while (buff[buff_i])
		result[i++] = buff[buff_i++];
	result[i] = '\0';
	free(buff);
	return (result);
}

char	*ft_gnl_reset(int fd, bool reset)
{
	static char	*buff[MAX_N_BUFFERS];
	char		*line;

	if (reset)
	{
		free(buff[fd]);
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff[fd] = read_into_buff(fd, buff[fd]);
	line = get_line_from(buff[fd]);
	buff[fd] = remove_line_from(buff[fd]);
	return (line);
}

/*
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("test.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("String is: %s", str);
	free(str);
	str = get_next_line(fd);
	printf("String is: %s", str);
	free(str);
	str = get_next_line(fd);
	printf("String is: %s", str);
	free(str);
	str = get_next_line(fd);
	printf("String is: %s", str);
	free(str);
}
*/