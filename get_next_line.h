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

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

int		ft_malloc_line(char **str, int len);
char	*ft_realloc(char *str, size_t size);
int		ft_strdup(char *src, char **str);
char	*ft_free_candidates(char *buff, char *line, char *surplus);
#endif
