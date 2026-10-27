#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE=42
#endif

int	ft_malloc_line(char **str, int len);

#endif