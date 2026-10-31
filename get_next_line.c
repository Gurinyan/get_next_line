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

//char	*ft_make_surplus(char *start, size_t len)
//{
//	size_t	i;
//	char	*surplus;

//	surplus = malloc(sizeof(char) * (len + 1));
//	if (surplus == NULL)
//		return (NULL);
//	i = 0;
//	while (i < len)
//	{
//		surplus[i] = start[i];
//		i++;
//	}
//	surplus[i] = '\0';
//	return (surplus);
//}
char	*ft_make_surplus(char *surplus, char *src, size_t src_len)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(surplus) + src_len + 1));
	if (str == NULL)
		return (NULL);
	while (surplus[i] != '\0')
	{
		str[i] = surplus[i];
		i++;
	}
	while (j < src_len)
	{
		str[i] = src[j];
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
	*surplus = ft_make_surplus(*surplus, &(*surplus)[i], ft_strlen(&(*surplus)[i]));
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
	size_t	surplus_byte;

	i = 0;
	if (ft_copy_surplus(line, surplus, idx))
	{
		*surplus = ft_make_surplus(surplus, &(*surplus)[i], ft_strlen(&(*surplus)[i]));
		return (1);
	}
	surplus_byte = ft_strlen(line);
	while (i < BUFFER_SIZE - surplus_byte)
	{
		line[*idx] = buff[i];
		i++;
		*idx = *idx + 1;
		if (buff[i - 1] == '\n')
			break ;
	}
	line[*idx] = '\0';
	*surplus = ft_make_surplus(*surplus, &buff[i], BUFFER_SIZE - i);
	if (i < BUFFER_SIZE - surplus_byte)
	{
		ft_free_candidates(buff, NULL, NULL);
		return (1);
	}
	return (0);
}

char	*ft_read_buff(int fd, char *buff, char **surplus, size_t *idx)
{
	char		*line;
	size_t		size;
	ssize_t		read_byte;

	if (!(ft_malloc_line(&line, BUFFER_SIZE)))
		return (ft_free_candidates(buff, NULL, *surplus));
	size = BUFFER_SIZE;
	read_byte = read(fd, buff, BUFFER_SIZE);
	while (read_byte > 0)
	{
		if (ft_copy_read(buff, line, surplus, idx))
			return (line);
		line = ft_realloc(line, &size);
		if (line == NULL || surplus == NULL)
			return (ft_free_candidates(buff, line, *surplus));
		read_byte = read(fd, buff, BUFFER_SIZE);
	}
	if (read_byte != -1)
	{
		//if (ft_copy_surplus(line, surplus, idx))
		//	return (line);
		ft_copy_read(buff, line, surplus, idx);
		return (line);
	}
	return (NULL);
}

//char	*get_next_line(int fd)
//{
//	size_t		idx;
//	size_t		size;
//	static char	*surplus;
//	char		*line;
//	char		*buff;

//	idx = 0;
//	size = BUFFER_SIZE;
//	if (surplus == NULL)
//		surplus = ft_make_surplus("", 0);
//	if (!(ft_malloc_line(&buff, BUFFER_SIZE) || surplus == NULL)
//		|| (!(ft_malloc_line(&line, BUFFER_SIZE))))
//		return (ft_free_candidates(buff, line, surplus));
//	if (surplus == NULL || )
//	//if ((ft_copy_surplus(line, &surplus, &idx)))
//	//	return (line);
//	//while (read(fd, buff, BUFFER_SIZE) > 0)
//	//{
//	//	if (ft_copy_read(buff, line, &surplus, &idx))
//	//		return (line);
//	//	line = ft_realloc(line, size);
//	//	if (line == NULL || surplus == NULL)
//	//		return (ft_free_candidates(buff, line, surplus));
//	//	size *= 2;
//	//}
	
//	return (NULL);
//}

char	*get_next_line(int fd)
{
	size_t		idx;
	static char	*surplus;
	char		*buff;

	idx = 0;
	if (surplus == NULL)
		surplus = ft_make_surplus("", 0);
	if (surplus == NULL)
		return (NULL);
	if (!(ft_malloc_line(&buff, BUFFER_SIZE)))
		return (NULL);
	return (ft_read_buff(fd, buff, &surplus, &idx));
}

#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char	*line;
	for (int i = 0; i < 6; i++)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	//printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));
}
