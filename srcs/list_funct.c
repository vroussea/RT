/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 17:21:14 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/29 16:47:02 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void		free_recap_spot(t_obj *list)
{
	unsigned int i;

	i = 0;
	while (i < list->nb_spots_on_screen)
		free(list->recap_spots[i++]);
	free(list->recap_spots);
}

void		del_all_list(t_obj *list)
{
	t_obj			*mem;
	int				nb_spot;

	mem = list;
	free_recap_spot(list);
	while (list != NULL)
	{
		mem = list->next;
		nb_spot = (int)(list->nb_spot);
		while (--nb_spot >= 0)
			free(list->spot[nb_spot]);
		free(list->spot);
		free(list);
		list = mem;
	}
}

t_obj		*copy_the_list(t_obj *list, t_obj *obj, double ray[3])
{
	t_obj	*new_list;
	t_obj	*new_elem;
	t_obj	*mem;
	double	new_ray[3];

	new_list = NULL;
	mem = NULL;
	while (list != NULL)
	{
		if (mem != NULL)
			mem = new_elem;
		if ((new_elem = (t_obj *)malloc(sizeof(t_obj))) == NULL)
			ft_error("malloc", NULL);
		if (new_list == NULL)
			new_list = new_elem;
		if (mem != NULL)
			mem->next = new_elem;
		mem = new_elem;
		new_elem->next = NULL;
		memcpy(new_elem, list, sizeof(t_obj));
		new_elem->pos_cam[0] = obj->base_intersec_point[0] - list->pos[0];
		new_elem->pos_cam[1] = obj->base_intersec_point[1] - list->pos[1];
		new_elem->pos_cam[2] = obj->base_intersec_point[2] - list->pos[2];
		make_rotation(new_elem->pos_cam, list->rotation);
		memcpy(new_ray, ray, sizeof(double[3]));
		make_rotation(new_ray, list->rotation);
		new_elem->pos_pixel_base[0] = new_elem->pos_cam[0] + new_ray[0];
		new_elem->pos_pixel_base[1] = new_elem->pos_cam[1] + new_ray[1];
		new_elem->pos_pixel_base[2] = new_elem->pos_cam[2] + new_ray[2];
		list = list->next;
	}
	return (new_list);
}

void		free_copied_list(t_obj *list)
{
	t_obj *mem;

	while (list != NULL)
	{
		mem = list->next;
		free(list);
		list = mem;
	}
}
