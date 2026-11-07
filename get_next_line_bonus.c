/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rutakano <rutakano@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 17:34:49 by rutakano          #+#    #+#             */
/*   Updated: 2026/11/07 15:58:28 by rutakano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_make_surplus(char *src, size_t src_len)
{
	size_t	i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (src_len + 1));
	if (str == NULL)
		return (NULL);
	while (i < src_len)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_copy_source(char *src, char *line, char **surplus, size_t *idx)
{
	size_t	i;
	char	*start;
	bool	is_line;

	if (src == NULL)
		return (0);
	i = 0;
	is_line = false;
	while (src[i] != '\0')
	{
		line[*idx] = src[i];
		i++;
		*idx = *idx + 1;
		if (src[i - 1] == '\n')
		{
			is_line = true;
			break ;
		}
	}
	line[*idx] = '\0';
	start = *surplus;
	*surplus = ft_make_surplus(&src[i], ft_strlen(src) - i);
	free(start);
	return (is_line);
}

ssize_t	read_buffer(int fd, char *buff)
{
	ssize_t	read_byte;

	read_byte = read(fd, buff, BUFFER_SIZE);
	if (read_byte < 0)
		return (-1);
	buff[read_byte] = '\0';
	return (read_byte);
}

char	*ft_get_line(int fd, char *buff, t_file *file, size_t *idx)
{
	char		*line;
	size_t		size;
	ssize_t		read_byte;

	line = malloc(sizeof(int) * (BUFFER_SIZE + 1));
	if (line == NULL)
		return (ft_free_return_res(buff, NULL, NULL, false));
	if (ft_copy_source(file->surplus, line, &(file->surplus), idx))
		return (ft_free_return_res(buff, line, NULL, true));
	size = ft_strlen(line);
	read_byte = read_buffer(fd, buff);
	while (read_byte > 0)
	{
		line = ft_realloc(line, &size);
		if (ft_copy_source(buff, line, &(file->surplus), idx))
			return (ft_free_return_res(buff, line, NULL, true));
		if (line == NULL || file->surplus == NULL)
			return (ft_free_return_res(buff, line, NULL, false));
		read_byte = read_buffer(fd, buff);
	}
	if (read_byte != -1 && line[0] != '\0')
		return (ft_free_return_res(buff, line, NULL, true));
	else
		return (ft_free_return_res(buff, line, file, false));
}

char	*get_next_line(int fd)
{
	size_t			idx;
	static t_file	**files;
	t_file			*file;
	char			*buff;

	idx = 0;
	if (fd < 0)
		return (NULL);
	if (BUFFER_SIZE < 0 || BUFFER_SIZE >= SSIZE_MAX)
		return (NULL);
	if (files == NULL)
	{
		files = malloc(sizeof(t_file *));
		*files = NULL;
	}
	if (files == NULL)
		return (NULL);
	file = find_file_node(files, *files, fd);
	if (file == NULL)
		return (NULL);
	buff = malloc(sizeof(int) * (BUFFER_SIZE + 1));
	if (buff == NULL)
		return (NULL);
	return (ft_get_line(fd, buff, file, &idx));
}

#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int fd_1 = open("rui.txt", O_RDONLY);
	int fd_2 = open("takano.txt", O_RDONLY);
	int fd_3 = open("pawmot.txt", O_RDONLY);
	int fd_null = open("this_file_is_not_exist", O_RDONLY);
	char	*line;
	for (int i = 0; i < 10; i++)
	{
		line = get_next_line(fd_1);
		printf("%s", line);
		free(line);
		line = get_next_line(fd_2);
		printf("%s", line);
		free(line);
		line = get_next_line(fd_3);
		printf("%s", line);
		free(line);
		line = get_next_line(fd_null);
		printf("%s", line);
		free(line);
		printf("\n\n");
	}
}
