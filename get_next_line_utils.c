#include "get_num_line.h"

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