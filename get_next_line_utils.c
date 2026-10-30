#include "get_next_line.h"

int	ft_strdup(char *src, char **str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (src[count] != '\0')
		count++;
	*str = malloc(sizeof(char) * (count + 1));
	if (*str == NULL)
		return (0);
	while (i < count)
	{
		(*str)[i] = src[i];
		i++;
	}
	(*str)[i] = '\0';
	return (1);
}

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

char	*ft_realloc(char *str, size_t size)
{
	size_t	i;
	char	*buff;

	if ((size_t)-1 / size < 2)
		return (NULL);
	buff = malloc(sizeof(char) * (size * 2));
	if (buff == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		buff[i] = str[i];
		i++;
	}
	free(str);
	return (buff);
}