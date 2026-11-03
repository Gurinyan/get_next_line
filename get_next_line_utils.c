#include "get_next_line.h"

char	*ft_free_candidates(char *buff, char *line, char *surplus)
{
	if (buff != NULL)
		free(buff);
	if (line != NULL)
		free(line);
	if (surplus != NULL)
		free(surplus);
	return (NULL);
}

void	lst_add_back(t_file **files, t_file *new)
{
	t_file	*current;

	current = *files;
	if (files == NULL)
		return ;
	while (current->next != NULL)
		current = current->next;
	if (*files == NULL)
		*files = new;
	else
		current->next = new;
}

t_file	*find_file_node(t_file *files, int fd)
{
	t_file	*file;

	while (files != NULL)
	{
		if (fd == files->fd)
			return (files);
		files = files->next;
	}
	file = malloc(sizeof(t_file));
	if (file == NULL)
		return (NULL);
	file->surplus = ft_make_surplus("", 0);
	if (file->surplus == NULL)
		return (NULL);
	file->fd = fd;
	file->next = NULL;
	return (file);
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