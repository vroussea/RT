/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_procedural_textures.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 13:32:27 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/14 16:45:50 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		init_default_procedural(t_obj *obj)
{
	t_proc_text		*texture;
	int				i;

	if ((texture = (t_proc_text *)malloc(sizeof(t_proc_text))) == NULL)
		ft_error("malloc", NULL);
	texture->type = PROC_TEXT_CUBE;
	i = 0;
	while (i < 3)
	{
		texture->size_xyz[i] = 1;
		texture->decal_xyz[i] = 0;
		texture->color1[i] = 0x00;
		texture->color2[i] = 0xFF;
		++i;
	}
	texture->color2[1] = 0x00;
	obj->proc_texture = texture;
	return (0);
}

int		init_procedural_type(t_obj *obj, char *line)
{
	if (strstr(line, "cubes") != NULL)
		obj->proc_texture->type = PROC_TEXT_CUBE;
	else if (strstr(line, "circles_x") != NULL)
		obj->proc_texture->type = PROC_TEXT_CIRCLE_X;
	else if (strstr(line, "circles_y") != NULL)
		obj->proc_texture->type = PROC_TEXT_CIRCLE_Y;
	else if (strstr(line, "circles_z") != NULL)
		obj->proc_texture->type = PROC_TEXT_CIRCLE_Z;
	else if (strstr(line, "straight stripes") != NULL)
		obj->proc_texture->type = PROC_TEXT_STRAIGHT_STRIPES;
	else if (strstr(line, "diagonal stripes") != NULL)
		obj->proc_texture->type = PROC_TEXT_DIAGONAL_STRIPES;
	return (0);
}

int		init_procedural_textures(t_obj *obj, int fd)
{
	char	*line;
	int		ret_gnl;

	if (init_default_procedural(obj) == -1)
		return (-1);
	while ((ret_gnl = get_next_line(fd, &line)) == 1 && \
			strstr(line, "</procedural>") == NULL)
	{
		if (check_procedural_texture(obj, line) == -1)
			return (-1);
		free(line);
	}
	free(line);
	if (ret_gnl != 1)
		return (-1);
	return (0);
}