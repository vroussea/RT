/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 16:59:02 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/08 15:46:03 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	init_functs_obj(t_obj *obj)
{
	if (obj->type == TYPE_SPHERE)
	{
		obj->intersect = intersec_sphere;
		obj->vector = get_vector_sphere;
		obj->shadow = shadow_sphere;
		obj->texturing = texture_sphere;
	}
	else if (obj->type == TYPE_PLANE)
	{
		obj->intersect = intersec_plane;
		obj->vector = get_vector_plane;
		obj->shadow = shadow_plane;
		obj->texturing = texture_plane;
	}
	else if (obj->type == TYPE_CYLINDER)
	{
		obj->intersect = intersec_cylinder;
		obj->vector = get_vector_cylinder;
		obj->shadow = shadow_cylinder;
		obj->texturing = texture_cylinder;
	}
	else if (obj->type == TYPE_CONE)
	{
		obj->intersect = intersec_cone;
		obj->vector = get_vector_cone;
		obj->shadow = shadow_cone;
		obj->texturing = texture_cylinder;
	}
}

int		init_scene(int fd, t_obj *objs, int is_aa)
{
	int		ret_gnl;
	t_cam	cam;
	char	*line;

	while ((ret_gnl = get_next_line(fd, &line)) == 1 && \
			strstr(line, "<cam_infos>") == NULL)
		free(line);
	free(line);
	if (get_cam_infos(fd, &cam, is_aa) == -1)
		return (-1);
	while ((ret_gnl = get_next_line(fd, &line) == 1) && \
			strstr(line, "<objs>") == NULL)
		free(line);
	free(line);
	if (get_objs_infos(fd, objs, &cam) == -1)
		return (-1);
	while ((ret_gnl = get_next_line(fd, &line) == 1) && \
			strstr(line, "</scene>") == NULL)
		free(line);
	free(line);
	if (ret_gnl == 1)
		return (0);
	return (-1);
}

void	write_and_exit(void)
{
	write(2, "Error: file not well formated\n", 30);
	exit(-1);
}

void	get_infos(char *file_name, t_obj **objs, int is_aa)
{
	int		fd;
	char	*line;
	int		ret_gnl;

	del_all_list(*objs);
	if ((*objs = (t_obj *)malloc(sizeof(t_obj))) == NULL)
		ft_error("malloc", NULL);
	(*objs)->next = NULL;
	(*objs)->type = -1;
	if ((fd = open(file_name, O_RDONLY)) == -1)
		write_and_exit();
	while ((ret_gnl = get_next_line(fd, &line)) == 1 && \
			strstr(line, "<scene>") == NULL)
		free(line);
	free(line);
	if (ret_gnl == 0 || (ret_gnl == 1 && init_scene(fd, *objs, is_aa) == -1))
		write_and_exit();
	close (fd);
}
