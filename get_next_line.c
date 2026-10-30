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

char	*ft_make_surplus(char *start, size_t len)
{
	size_t	i;
	char	*surplus;

	surplus = malloc(sizeof(char) * (len + 1));
	if (surplus == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		surplus[i] = start[i];
		i++;
	}
	surplus[i] = '\0';
	return (surplus);
}

int	ft_copy_surplus(char *line, char **surplus, size_t *idx)
{
	size_t	i;

	i = 0;
	if (surplus == NULL)
		return (false);
	while ((*surplus)[i] != '\0')
	{
		line[*idx] = (*surplus)[i];
		*idx = *idx + 1;
		i++;
		if ((*surplus)[i - 1] == '\n')
			break ;
	}
	if ((*surplus)[i] != '\0')
	{
		line[*idx] = '\0';
		ft_strdup((&(*surplus)[i]), surplus);
		return (1);
	}
	free(*surplus);
	ft_strdup("", surplus);
	return (0);
}

int	ft_copy_read(char *buff, char *line, char **surplus, size_t *idx)
{
	size_t	i;

	i = 0;
	if (ft_copy_surplus(line, surplus, idx))
		return (1);
	while (i < BUFFER_SIZE)
	{
		line[*idx] = buff[i];
		i++;
		*idx = *idx + 1;
		if (buff[i - 1] == '\n')
			break ;
	}
	if (i < BUFFER_SIZE)
	{
		line[*idx] = '\0';
		*surplus = ft_make_surplus(&buff[i], BUFFER_SIZE - i);
		ft_free_candidates(buff, NULL, NULL);
		return (1);
	}
	ft_strdup("", surplus);
	return (0);
}

char	*ft_read_buff(int fd, size_t buffer_size)
{
	char	*buff;
	size_t	read_byte;

	if (!(ft_malloc_line(&buff, BUFFER_SIZE)))
		return (NULL);
	read_byte = read(fd, buff, BUFFER_SIZE);
}

char	*get_next_line(int fd)
{
	size_t		idx;
	size_t		size;
	static char	*surplus;
	char		*line;
	char		*buff;

	idx = 0;
	size = BUFFER_SIZE;
	if (surplus == NULL)
		ft_strdup("", &surplus);
	if (!(ft_malloc_line(&buff, BUFFER_SIZE) || surplus == NULL)
		|| (!(ft_malloc_line(&line, BUFFER_SIZE))))
		return (ft_free_candidates(buff, line, surplus));
	while (read(fd, buff, BUFFER_SIZE) > 0)
	{
		if (ft_copy_read(buff, line, &surplus, &idx))
			return (line);
		line = ft_realloc(line, size);
		if (line == NULL || surplus == NULL)
			return (ft_free_candidates(buff, line, surplus));
		size *= 2;
	}
	
	return (NULL);
}

#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char	*line;
	for (int i = 0; i < 4; i++)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	//printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));
}
