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

int	ft_copy_read(char *buff, char *line, char *surplus, size_t *idx)
{
	size_t	i;

	i = 0;
	while (*surplus != '\0')
	{
		line[*idx] = *surplus;
		surplus++;
	}
	while (i < BUFFER_SIZE && buff[i] != '\n')
	{
		line[*idx] = buff[i];
		i++;
		*idx = *idx + 1;
	}
	if (i < BUFFER_SIZE)
		*surplus = ft_make_surplus(&buff[i], BUFFER_SIZE - i);
	if (buff[i] == '\n')
		return (1);
	return (0);
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
	surplus = "";
	if (!(ft_malloc_line(buff, BUFFER_SIZE)) 
	|| (!(ft_malloc_line(line, BUFFER_SIZE))))
		return (ft_free_candidates(buff, line, NULL));
	while (read(fd, buff, BUFFER_SIZE) > 0)
	{
		if (ft_copy_read(buff, line, surplus, &idx))
		{
			return (line);
		}
		if (surplus == NULL)
			return (NULL);
		if (!(ft_realloc(line, size)))
			return (NULL);
		size *= 2;
	}
}
