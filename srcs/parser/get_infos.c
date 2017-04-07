/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 16:59:02 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/29 17:40:38 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		free_spots(t_cam *cam)
{
	unsigned int i;

	i = 0;
	while (i < cam->nb_spot)
	{
		free(cam->spot[i]);
		++i;
	}
	free(cam->spot);
}

static bool	init_scene(int fd, t_obj *objs, int is_aa)
{
	int		ret_gnl;
	t_cam	cam;
	char	*line;

	while ((ret_gnl = get_next_line(fd, &line)) == 1 && \
			ft_strstr(line, "<cam_infos>") == NULL)
		free(line);
	free(line);
	if (get_cam_infos(fd, &cam, is_aa) == true)
		return (true);
	while ((ret_gnl = get_next_line(fd, &line) == 1) && \
			ft_strstr(line, "<objs>") == NULL)
		free(line);
	free(line);
	if (get_objs_infos(fd, objs, &cam) == true)
		return (true);
	while ((ret_gnl = get_next_line(fd, &line) == 1) && \
			ft_strstr(line, "</scene>") == NULL)
		free(line);
	free(line);
	init_recap_spots(objs, &cam);
	free_spots(&cam);
	if (ret_gnl == 1)
		return (false);
	return (true);
}

void		write_and_exit(void)
{
	write(2, "Error: file not well formated\n", 30);
	exit(-1);
}

void		get_infos(char *file_name, t_obj **objs, int is_aa)
{
	int		fd;
	char	*line;
	int		ret_gnl;

	if ((*objs = (t_obj *)malloc(sizeof(t_obj))) == NULL)
		ft_error("malloc", NULL);
	(*objs)->next = NULL;
	(*objs)->type = -1;
	if ((fd = open(file_name, O_RDONLY)) == -1)
		write_and_exit();
	while ((ret_gnl = get_next_line(fd, &line)) == 1 && \
			ft_strstr(line, "<scene>") == NULL)
		free(line);
	free(line);
	if (ret_gnl == 0 || (ret_gnl == 1 && init_scene(fd, *objs, is_aa) == true))
		write_and_exit();
	close(fd);
}
