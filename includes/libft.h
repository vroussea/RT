/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 13:47:08 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/03 18:36:05 by eduwer           ###   ########.fr       */
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

#endif
