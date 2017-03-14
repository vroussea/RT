/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:34:08 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/14 16:45:13 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		check(char *line, t_obj *new_obj, int fd)
{
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
	else if (strstr(line, "<procedural>") != NULL && \
			init_procedural_textures(new_obj, fd) == -1)
		return (-1);
	return (0);
}

int		check_procedural_texture(t_obj *obj, char *line)
{
	if (strstr(line, "<type>") != NULL && \
			init_procedural_type(obj, line) == -1)
		return (-1);
	else if (strstr(line, "<color1>") != NULL  && \
			init_colors(obj->proc_texture->color1, line) == -1)
		return (-1);
	else if (strstr(line, "<color2>") != NULL && \
			init_colors(obj->proc_texture->color2, line) == -1)
		return (-1);
	else if (strstr(line, "<size>") != NULL && \
			init_3_values(obj->proc_texture->size_xyz, line, "</size>") == -1)
		return (-1);
	else if (strstr(line, "<decal>") != NULL && \
			init_3_values(obj->proc_texture->decal_xyz, line, "</decal>") == -1)
		return (-1);
	return (0);
}

void	verif_plane_norm_vec(t_obj *plane)
{
	double	vec[3];
	int		i;

	i = 0;
	while (plane->norm_vec[i] == 0.0)
		i++;
	vec[0] = plane->pos_cam[0];
	vec[1] = plane->pos_cam[1];
	vec[2] = plane->pos_cam[2];
	vec[i] = plane->pos_cam[i] - \
			 (plane->high / plane->norm_vec[i]);
	normalize_vec(vec);
	if (dot_product(vec, plane->norm_vec) <= 0)
	{
		plane->norm_vec[2] = -1;
		plane->high = -plane->high;
	}
}

