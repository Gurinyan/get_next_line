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

int	ft_malloc_line(char **str, int len)
{
	*str = malloc(sizeof(char) * len);
	if (*str == NULL)
		return (0);
	return (1);
}

void	ft_strcat(char **surplus, char *buff, size_t len)
{

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