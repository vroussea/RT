/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Updated: 2017/03/22 15:02:21 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

char	*balise(char *line, char *start, char *end)
{
	size_t	size;
	char	*ptr;

	size = strlen(start);
	if (!(line = strstr(line, start)))
		return (NULL);
	line += size;
	if (!(ptr = strstr(line, end)))
		return (NULL);
	size = (size_t)((long)ptr - (long)line);
	line = strsub(line, 0, size);
	line[size] = '\0';
	return (line);
}

int		check(char *line, t_obj *new_obj)
{
	char	*str;

	if (strstr(line, "<pos>") != NULL && new_obj->type != TYPE_PLANE && \
			init_3_values(new_obj->pos, line, "</pos>") == -1)
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
	else if ((str = balise(line, "<texture>", "</texture>")) != NULL)
	{
		if (init_surface(&(new_obj->texture), str) == -1)
		{
			free(&str);
			return (-1);
		}
		else
			free(&str);
	}
	return (0);
}
