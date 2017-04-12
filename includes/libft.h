/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 13:47:08 by eduwer            #+#    #+#             */
/*   Updated: 2017/04/12 18:24:00 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# if !WIN32
#  include <unistd.h>
# endif
# include <stdbool.h>
# define BUFF_SIZE 1000

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

char			**ft_strsplit(char const *s, char c);
int				get_next_line(const int fd, char **line);
bool			ft_isdigit(int c);
char			*ft_strcpy(char *dst, const char *src);
void			*ft_memcpy(void *dest, const void *src, size_t n);
int				ft_strlen(char *str);
void			*ft_memset(void *b, int c, size_t len);
char			*ft_strncpy(char *s1, const char *s2, size_t n);
char			*ft_strstr(const char *str, const char *to_find);
int				ft_atoi(const char *str);

#endif
