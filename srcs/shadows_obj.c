/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 15:50:27 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/09 22:57:36 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	get_new_pos(double point[3], double pos_obj[3], double rotation[3])
{
	int i;

	i = 0;
	while (i < 3 && pos_obj != NULL)
	{
		point[i] -= pos_obj[i];
		i++;
	}
	make_rotation(point, rotation);
}

int		shadow_sphere(t_obj *sphere, double point[3], int nb)
{
	double	point_sphere[3];
	double	vec[3];
	double	abc[3];
	double	delta;
	double	ans;

	memcpy(point_sphere, point, sizeof(double) * 3);
	get_new_pos(point_sphere, sphere->pos, NULL);
	vec[0] = (sphere->spot)[nb][0] - point_sphere[0];
	vec[1] = (sphere->spot)[nb][1] - point_sphere[1];
	vec[2] = (sphere->spot)[nb][2] - point_sphere[2];
	abc_sphere(abc, vec, point_sphere, sphere->size);
	if ((delta = pow(abc[1], 2) - 4 * abc[0] * abc[2]) < 0)
		return (1);
	ans = (-abc[1] - sqrt(delta)) / (2 * abc[0]);
	if (ans > 0.0001 && ans < 0.9999)
		return (0);
	ans = (-abc[1] + sqrt(delta)) / (2 * abc[0]);
	if (ans > 0.0001 && ans < 0.9999)
		return (0);
	return (1);
}

int		shadow_plane(t_obj *plane, double point[3], int nb)
{
	double vec[3];
	double ab[2];
	double result;
	double obj_point[3];

	memcpy(obj_point, point, sizeof(double) * 3);
	get_new_pos(obj_point, NULL, plane->rotation);
	vec[0] = (plane->spot)[nb][0] - obj_point[0];
	vec[1] = (plane->spot)[nb][1] - obj_point[1];
	vec[2] = (plane->spot)[nb][2] - obj_point[2];
	ab[0] = plane->norm_vec[0] * vec[0] + plane->norm_vec[1] * vec[1] + \
			plane->norm_vec[2] * vec[2];
	if (ab[0] == 0)
		return (1);
	ab[1] = plane->norm_vec[0] * obj_point[0] + \
				plane->norm_vec[1] * obj_point[1] + \
					plane->norm_vec[2] * obj_point[2] - plane->high;
	result = (-ab[1]) / (ab[0]);
	if (result > 0.0001 && result < 0.9999)
		return (0);
	return (1);
}

int		shadow_cylinder(t_obj *cylinder, double point[3], int nb)
{
	double	vec[3];
	double	abc[3];
	double	obj_point[3];
	double	delta;

	memcpy(obj_point, point, sizeof(double) * 3);
	get_new_pos(obj_point, cylinder->pos, cylinder->rotation);
	vec[0] = (cylinder->spot)[nb][0] - obj_point[0];
	vec[1] = (cylinder->spot)[nb][1] - obj_point[1];
	vec[2] = (cylinder->spot)[nb][2] - obj_point[2];
	abc_cylinder(abc, vec, obj_point, cylinder->size);
	if ((delta = pow(abc[1], 2) - 4 * abc[0] * abc[2]) < 0)
		return (1);
	vec[0] = (-abc[1] - sqrt(delta)) / (2 * abc[0]);
	if (vec[0] > 0.0001 && vec[0] < 0.9999)
		return (0);
	vec[0] = (-abc[1] + sqrt(delta)) / (2 * abc[0]);
	if (vec[0] > 0.0001 && vec[0] < 0.9999)
		return (0);
	return (1);
}

int		shadow_cone(t_obj *cone, double point[3], int nb)
{
	double	vec[3];
	double	abc[3];
	double	obj_point[3];
	double	delta;

	memcpy(obj_point, point, sizeof(double) * 3);
	get_new_pos(obj_point, cone->pos, cone->rotation);
	vec[0] = (cone->spot)[nb][0] - obj_point[0];
	vec[1] = (cone->spot)[nb][1] - obj_point[1];
	vec[2] = (cone->spot)[nb][2] - obj_point[2];
	abc_cone(abc, vec, obj_point, cone->rad);
	if ((delta = pow(abc[1], 2) - 4 * abc[0] * abc[2]) < 0)
		return (1);
	vec[0] = (-abc[1] - sqrt(delta)) / (2 * abc[0]);
	if (vec[0] > 0.0001 && vec[0] < 0.9999)
		return (0);
	vec[0] = (-abc[1] + sqrt(delta)) / (2 * abc[0]);
	if (vec[0] > 0.0001 && vec[0] < 0.9999)
		return (0);
	return (1);
}
