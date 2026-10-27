#include "get_next_line.h"

char *get_next_line(int fd)
{
	size_t		idx;
	static char	*next;
	char		*line;
	char		*buff;

	buff = malloc(sizeof(char) * BUFFER_SIZE);
	if (buff == NULL)
		return (NULL);
	if (!(ft_malloc_line(buff, BUFFER_SIZE)))
		return (NULL);
	if (!(ft_malloc_line(line, BUFFER_SIZE)))
		return (NULL);
	while (read(fd, buff, BUFFER_SIZE) > 0)
	{
		while (idx < BUFFER_SIZE)
		{
			//文字列のコピー

			// \nが来るか\0が来たらその文字列を返す
			idx++;

		}
		//*2の分をreallocする
	}
}