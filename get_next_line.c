/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rutakano <rutakano@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 17:34:49 by rutakano          #+#    #+#             */
/*   Updated: 2026/10/27 17:34:51 by rutakano         ###   ########.fr       */
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

int	ft_copy_surplus(char *line, char **surplus, size_t *idx)
{
	size_t	i;
	char	*start;

	i = 0;
	start = *surplus;
	while ((*surplus)[i] != '\0')
	{
		line[*idx] = (*surplus)[i];
		*idx = *idx + 1;
		i++;
		if ((*surplus)[i - 1] == '\n')
			break ;
	}
	line[*idx] = '\0';
	*surplus = ft_make_surplus(&(*surplus)[i], ft_strlen(&(*surplus)[i]));
	if (start[i] != '\0')
	{
		free(start);
		return (1);
	}
	free(start);
	return (0);
}

int	ft_copy_read(char *buff, char *line, char **surplus, size_t *idx)
{
	size_t	i;
	bool	is_line;

	i = 0;
	is_line = false;
	while (buff[i] != '\0')
	{
		line[*idx] = buff[i];
		i++;
		*idx = *idx + 1;
		if (buff[i - 1] == '\n')
		{
			is_line = true;
			break ;
		}
	}
	line[*idx] = '\0';
	*surplus = ft_make_surplus(&buff[i], BUFFER_SIZE - i);
	if (is_line == true)
	{
		ft_free_candidates(buff, NULL, NULL);
		return (1);
	}
	return (0);
}

char	*ft_get_line(int fd, char *buff, char **surplus, size_t *idx)
{
	char		*line;
	size_t		size;
	ssize_t		read_byte;

	line = malloc(sizeof(int) * (BUFFER_SIZE + 1));
	if (line == NULL)
		return (ft_free_candidates(buff, NULL, *surplus));
	if (ft_copy_surplus(line, surplus, idx))
		return (line);
	size = ft_strlen(line);
	read_byte = read(fd, buff, BUFFER_SIZE);
	buff[read_byte] = '\0';
	while (read_byte > 0)
	{
		line = ft_realloc(line, &size);
		if (ft_copy_read(buff, line, surplus, idx))
			return (line);
		if (line == NULL || surplus == NULL)
			return (ft_free_candidates(buff, line, *surplus));
		read_byte = read(fd, buff, BUFFER_SIZE);
		buff[read_byte] = '\0';
	}
	if (read_byte != -1)
		return (line);
	return (NULL);
}

//char	*get_next_line(int fd)
//{
//	size_t		idx;
//	static char	*surplus;
//	char		*buff;

//	idx = 0;
//	if (surplus == NULL)
//		surplus = ft_make_surplus("", 0);
//	if (surplus == NULL)
//		return (NULL);
//	buff = malloc(sizeof(int) * (BUFFER_SIZE + 1));
//	if (buff == NULL)
//		return (NULL);
//	return (ft_get_line(fd, buff, &surplus, &idx));
//}

char	*get_next_line(int fd)
{
	size_t			idx;
	static t_file	**files;
	t_file			*file;
	char			*surplus;
	char			*buff;

	idx = 0;
	if (files == NULL)
	{
		files = malloc(sizeof(t_file *));
		*files = NULL;
	}
	if (files == NULL)
		return (NULL);
	file = find_file_node(*files, fd);
	if (file == NULL)
		return (NULL);
	lst_add_back(files, file);
	surplus = file->surplus;
	buff = malloc(sizeof(int) * (BUFFER_SIZE + 1));
	if (buff == NULL)
		return (NULL);
	return (ft_get_line(fd, buff, &surplus, &idx));
}

#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int fd = open("rui.txt", O_RDONLY);
	char	*line;
	for (int i = 0; i < 8; i++)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	//printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));
}
