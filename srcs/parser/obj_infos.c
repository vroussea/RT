/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 16:59:02 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/17 14:57:08 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

bool	get_objs_infos(int fd, t_obj *objs, t_cam *cam)
{
	int		ret_gnl;
	char	*line;

	while ((ret_gnl = get_next_line(fd, &line)) == 1 && ft_strstr(line, \
		"</objs>") == NULL)
	{
		if (ft_strstr(line, "<sphere>") != NULL && \
			init_sphere(fd, objs, cam) == true)
			return (true);
		else if (ft_strstr(line, "<plane>") != NULL && \
			init_plane(fd, objs, cam) == true)
			return (true);
		else if (ft_strstr(line, "<cylinder>") != NULL && \
			init_cylinder(fd, objs, cam) == true)
			return (true);
		else if (ft_strstr(line, "<cone>") != NULL && \
			init_cone(fd, objs, cam) == true)
			return (true);
		free(line);
	}
	free(line);
	return (false);
}

bool	init_sphere(int fd, t_obj *objs, t_cam *cam)
{
	int		ret_gnl;
	char	*line;
	t_obj	*new_obj;

	if ((new_obj = make_new_obj(objs, TYPE_SPHERE)) == NULL)
		return (-1);
	init_default_sphere_values(cam, new_obj);
	while ((ret_gnl = get_next_line(fd, &line)) == 1 && ft_strstr(line, \
		"</sphere>") == NULL)
	{
		if (check(line, new_obj, fd) == true)
			return (true);
		free(line);
	}
	free(line);
	finish_init_obj(new_obj, cam);
	return (false);
}

bool	init_plane(int fd, t_obj *objs, t_cam *cam)
{
	int		ret_gnl;
	char	*line;
	t_obj	*new_obj;

	if ((new_obj = make_new_obj(objs, TYPE_PLANE)) == NULL)
		return (-1);
	init_default_plane_values(cam, new_obj);
	while ((ret_gnl = get_next_line(fd, &line)) == 1 && ft_strstr(line, \
		"</plane>") == NULL)
	{
		if (check(line, new_obj, fd) == true)
			return (true);
		free(line);
	}
	free(line);
	finish_init_obj(new_obj, cam);
	return (false);
}

bool	init_cylinder(int fd, t_obj *objs, t_cam *cam)
{
	int		ret_gnl;
	char	*line;
	t_obj	*new_obj;

	if ((new_obj = make_new_obj(objs, TYPE_CYLINDER)) == NULL)
		return (-1);
	init_default_cylinder_values(cam, new_obj);
	while ((ret_gnl = get_next_line(fd, &line)) == 1 && ft_strstr(line, \
		"</cylinder>") == NULL)
	{
		if (check(line, new_obj, fd) == true)
			return (true);
		free(line);
	}
	free(line);
	finish_init_obj(new_obj, cam);
	return (false);
}

bool	init_cone(int fd, t_obj *objs, t_cam *cam)
{
	int		ret_gnl;
	char	*line;
	t_obj	*new_obj;

	if ((new_obj = make_new_obj(objs, TYPE_CONE)) == NULL)
		return (true);
	init_default_cone_values(cam, new_obj);
	while ((ret_gnl = get_next_line(fd, &line)) == 1 && ft_strstr(line, \
		"</cone>") == NULL)
	{
		if (check(line, new_obj, fd) == true)
			return (true);
		free(line);
	}
	free(line);
	new_obj->rad = radians(new_obj->angle);
	finish_init_obj(new_obj, cam);
	return (0);
}
