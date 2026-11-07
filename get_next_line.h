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

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdint.h>
# include <stddef.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_file
{
	char			*surplus;
	int				fd;
	struct s_file	*next;
}	t_file;

typedef struct s_buff
{
	char			*buff;
	struct s_buff	*next;
}	t_buff;

char	*get_next_line(int fd);
char	*ft_get_line(int fd, char *buff, t_file *file, size_t *idx);
char	*ft_make_surplus(char *src, size_t src_len);
int		ft_copy_source(char *src, char *line, char **surplus, size_t *idx);
ssize_t	read_buffer(int fd, char *buff);
int		ft_malloc_line(char **str, int len);
char	*ft_realloc(char *str, size_t *size);
size_t	read_buff(char *buff, int fd);
char	*ft_make_surplus(char *src, size_t len);
size_t	ft_strlen(char *str);
char	*ft_free_return_res(char *buff, char *line, t_file *file, bool is_line);
void	lst_add_back(t_file **files, t_file *new);
t_file	*find_file_node(t_file **files, t_file *file, int fd);
#endif
