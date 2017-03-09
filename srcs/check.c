/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:34:08 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/09 19:43:00 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

char	*balise(char *line, t_obj *new_obj, char *start, char *end)
{
	size_t	size;
	char	*ptr;

	size = strlen(start);
	if (!(line = strstr(line, start)))
		return (NULL);
	line += size;
	if (!(ptr = strstr(line, end)))
		return (NULL);
	size = ptr - line;
	line = strsub(line, 0, size);
	return (line);
}

int		check(char *line, t_obj *new_obj)
{
	if (strstr(line, "<pos>") != NULL && \
			init_3_values(new_obj->pos/*_cam*/, line, "</pos>") == -1)
		return (-1);
	else if (strstr(line, "<size>") != NULL && \
			init_one_value(&(new_obj->size), line, "</size>") == -1)
		return (-1);
	else if (strstr(line, "<color>") != NULL && \
			init_colors(new_obj->color_rgb, line) == -1)
		return (-1);
	else if (strstr(line, "<rotation>") != NULL && \
			init_3_values(new_obj->rotation, line, "</rotation>") == -1)
		return (-1);
	else if (strstr(line, "<angle>") != NULL && \
			init_one_value(&(new_obj->angle), line, "</angle>") == -1)
		return (-1);
	else if (strstr(line, "<high>") != NULL && \
			init_one_value(&(new_obj->high), line, "</high>") == -1)
		return (-1);
	else if (strstr(line, "<texture>") != NULL && \
			init_surface(&(new_obj->texture), line, "</texture>") == -1)
		return (-1);
	return(0);
	// need to free the new small lines and use balise funct
}
