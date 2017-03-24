/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quad_collide.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 18:10:29 by vroussea          #+#    #+#             */
/*   Updated: 2017/02/11 18:12:28 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_v1.h"
#include <math.h>
#include <stdio.h> ////

static t_obj	mod_cam(t_obj ray, t_obj quad, t_scene scene)
{
	double		ang;
	t_vect3d	dir_z;

	dir_z = vect3d_fill(0.0, 0.0, 1.0);
//	printf("ray pos avant rot : \nx : %f\ny : %f\nz : %f\n", ray.PX, ray.PY, ray.PZ);
//	printf("ray dir avant rot : \nx : %f\ny : %f\nz : %f\n", ray.DX, ray.DY, ray.DZ);
//	ray.pos = vect3d_sub(ray.pos, quad.pos);
	ang = vect3d_ang(quad.dir, dir_z);
	ray.dir = vect3d_rot(vect3d_unit(CAM.dir), ray.dir, ang);
	ray.pos = vect3d_rot(vect3d_unit(CAM.dir), ray.pos, ang);
//	printf("ray pos apres rot : \nx : %f\ny : %f\nz : %f\n", ray.PX, ray.PY, ray.PZ);
//	printf("ray dir apres rot : \nx : %f\ny : %f\nz : %f\n", ray.DX, ray.DY, ray.DZ);
	return (ray);
}

double	collide_sphere(t_obj ray, t_obj quad, t_scene scene)
{
	double		a;
	double		b;
	double		c;
	double		d;

	a = ray.DX * ray.DX + ray.DY * ray.DY + ray.DZ * ray.DZ;
	b = 2 * ray.DX * (ray.PX - quad.PX) +
		2 * ray.DY * (ray.PY - quad.PY) +
		2 * ray.DZ * (ray.PZ - quad.PZ);
	c = quad.PX * quad.PX + quad.PY * quad.PY + quad.PZ * quad.PZ +
		ray.PX * ray.PX + ray.PY * ray.PY + ray.PZ * ray.PZ -
		2 * (quad.PX * ray.PX + quad.PY * ray.PY + quad.PZ * ray.PZ )
		- quad.size * quad.size;
	d = b * b - 4 * a * c;
	if (d < 0)
		return (-1);
	c = (-b - sqrt(d)) / (2 * a);
	d = (-b + sqrt(d)) / (2 * a);
//	printf("c : %f\nd : %f\n", c, d);
	return (c > 0.00001 ? c : d);
	CAM.DX++;
}

double	collide_plan(t_obj ray, t_obj quad, t_scene scene)
{
	double	d;

	d = vect3d_scal_prod(ray.dir, quad.dir);
	if (d)
		return (vect3d_scal_prod(vect3d_sub(quad.pos, ray.pos), quad.dir) / d);
	return (-1);
	CAM.DX--;
}

double	collide_cylinder(t_obj ray, t_obj quad, t_scene scene)
{
	double	a;
	double	b;
	double	c;
	double	d;

	ray = mod_cam(ray, quad, scene);
	a = ray.DX * ray.DX + ray.DY * ray.DY;
	b = 2 * ray.DX * ray.PX + 2 * ray.DY * ray.PY;
	c = ray.PX * ray.PX + ray.PY * ray.PY - quad.size * quad.size;
	d = b * b - 4 * a * c;
	if (d < 0)
		return (-1);
	c = (- b - sqrt(d)) / (2 * a);
	d = (- b + sqrt(d)) / (2 * a);
//	printf("c : %f\nd : %f\n", c, d);
	return (c > 0.00001 ? c : d);
	CAM.DX = CAM.DX + 1 - 1;
}

double	collide_cone(t_obj ray, t_obj quad, t_scene scene)
{
	double	a;
	double	b;
	double	c;
	double	d;

	ray = mod_cam(ray, quad, scene);
	a = ray.DX * ray.DX + ray.DY * ray.DY - ray.DZ * ray.DZ
		* tan(quad.size * RAD);
	b = 2 * ray.DX * ray.PX + 2 * ray.DY * ray.PY -
		2 * ray.DZ * ray.PZ * tan(quad.size * RAD);
	c = ray.PX * ray.PX + ray.PY * ray.PY -
		ray.PZ * ray.PZ * tan(quad.size * RAD);
	d = b * b - 4 * a * c;
	if (d < 0)
		return (-1);
	c = (- b - sqrt(d)) / (2 * a);
	d = (- b + sqrt(d)) / (2 * a);
	return (c > 0.00001 ? c : d);
}
