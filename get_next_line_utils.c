#include "get_next_line.h"

char	*ft_free_candidates(char *buff, char *str, char *surplus)
{
	if (buff != NULL)
		free(buff);
	if (str != NULL)
		free(str);
	if (buff != NULL)
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