/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:34:08 by eduwer            #+#    #+#             */
/*   Updated: 2017/04/12 19:36:16 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

char		*balise(char *line, char *start, char *end)
{
	size_t	size;
	char	*ptr;

	size = ft_strlen(start);
	if (!(line = ft_strstr(line, start)))
		return (NULL);
	line += size;
	if (!(ptr = ft_strstr(line, end)))
		return (NULL);
	size = (size_t)((long)ptr - (long)line);
	line = strsub(line, 0, size);
	line[size] = '\0';
	return (line);
}

static bool	checktext(char *line, t_obj *new_obj)
{
	char	*str;

	if (ft_strstr(line, "<waves/>") != NULL)
		new_obj->is_waves = true;
	if ((str = balise(line, "<texture>", "</texture>")) != NULL)
	{
		if (init_surface(&(new_obj->texture), str) == true)
		{
			free(str);
			return (true);
		}
		else
			free(str);
	}
	if (ft_strstr(line, "<reflection>") != NULL && \
		init_ref(&(new_obj->reflection_id), line, "</reflection>") == true)
		return (true);
	if (ft_strstr(line, "<refraction>") != NULL && \
		init_ref(&(new_obj->refraction_id), line, "</refraction>") == true)
		return (true);
	if (ft_strstr(line, "<texture_size>") != NULL &&						\
		init_ref(&(new_obj->text_size), line, "</texture_size>") == true)
		return (true);
	return (false);
}

bool		check(char *line, t_obj *new_obj, int fd)
{
	if (ft_strstr(line, "<pos>") != NULL && new_obj->type != TYPE_PLANE && \
			init_3_values(new_obj->pos, line, "</pos>") == true)
		return (true);
	else if (ft_strstr(line, "<size>") != NULL && \
			init_one_value(&(new_obj->size), line, "</size>") == true)
		return (true);
	else if (ft_strstr(line, "<color>") != NULL && \
			init_colors(new_obj->color_rgb, line) == true)
		return (true);
	else if (ft_strstr(line, "<rotation>") != NULL && \
			init_3_values(new_obj->rotation, line, "</rotation>") == true)
		return (true);
	else if (ft_strstr(line, "<angle>") != NULL && \
			init_one_value(&(new_obj->angle), line, "</angle>") == true)
		return (true);
	else if (ft_strstr(line, "<high>") != NULL && \
			init_one_value(&(new_obj->high), line, "</high>") == true)
		return (true);
	else if (ft_strstr(line, "<procedural>") != NULL && \
			init_procedural_textures(new_obj, fd) == true)
		return (true);
	return (checktext(line, new_obj));
}

bool		check_procedural_texture(t_obj *obj, char *line)
{
	if (ft_strstr(line, "<type>") != NULL && \
			init_procedural_type(obj, line) == true)
		return (true);
	else if (ft_strstr(line, "<color1>") != NULL && \
			init_colors(obj->color1, line) == true)
		return (true);
	else if (ft_strstr(line, "<color2>") != NULL && \
			init_colors(obj->color2, line) == true)
		return (true);
	else if (ft_strstr(line, "<decal>") != NULL && \
			init_3_values(obj->decal_xyz, line, "</decal>") == true)
		return (true);
	return (false);
}

void		verif_plane_norm_vec(t_obj *plane)
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
