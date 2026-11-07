/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rutakano <rutakano@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 16:02:32 by rutakano          #+#    #+#             */
/*   Updated: 2026/11/07 16:02:33 by rutakano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free_return_res(char *buff, char *line, t_file *file, bool is_line)
{
	if (buff != NULL)
		free(buff);
	if (line != NULL && is_line == false)
	{
		free(line);
		return (NULL);
	}
	if (file != NULL)
	{
		free(file->surplus);
	}
	return (line);
}

void	lst_add_back(t_file **files, t_file *new)
{
	t_file	*current;

	current = *files;
	if (files == NULL)
		return ;
	if (current == NULL)
		*files = new;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

t_file	*find_file_node(t_file **files, t_file *file, int fd)
{
	t_file	*new;

	while (file != NULL)
	{
		if (fd == file->fd)
			return (file);
		file = file->next;
	}
	new = malloc(sizeof(t_file));
	if (new == NULL)
		return (NULL);
	new->surplus = ft_make_surplus("", 0);
	if (new->surplus == NULL)
		return (NULL);
	new->fd = fd;
	new->next = NULL;
	lst_add_back(files, new);
	return (new);
}

char	*ft_realloc(char *str, size_t *size)
{
	size_t	i;
	char	*line;

	*size = ft_strlen(str);
	if ((size_t)-1 - *size < BUFFER_SIZE)
		return (NULL);
	line = malloc(sizeof(char) * (*size + BUFFER_SIZE + 1));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (i < *size)
	{
		line[i] = str[i];
		i++;
	}
	*size = *size + BUFFER_SIZE;
	free(str);
	return (line);
}

size_t	ft_strlen(char *str)
{
	size_t	count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}
