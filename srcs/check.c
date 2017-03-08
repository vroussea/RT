/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:34:08 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/02 14:59:32 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

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
	return(0);
}
