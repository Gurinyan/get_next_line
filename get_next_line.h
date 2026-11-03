/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rutakano <rutakano@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 19:11:54 by rutakano          #+#    #+#             */
/*   Updated: 2026/10/27 19:11:56 by rutakano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

typedef struct s_file
{
	char	*surplus;
	int		fd;
	struct s_file	*next;
}	t_file;

int		ft_malloc_line(char **str, int len);
char	*ft_realloc(char *str, size_t *size);
//char	*ft_realloc(char *str);
//int		ft_strdup(char *src, char **str);
size_t	read_buff(char *buff, int fd);
char	*ft_make_surplus(char *src, size_t len);
size_t	ft_strlen(char *str);
char	*ft_free_candidates(char *buff, char *line, char *surplus);
void	lst_add_back(t_file **files, t_file *new);
t_file	*find_file_node(t_file *files, int fd);
#endif
