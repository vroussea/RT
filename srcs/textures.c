/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 16:30:29 by gboudrie          #+#    #+#             */
/*   Updated: 2017/04/12 16:52:47 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <math.h>
#include <stdlib.h>

Uint32		texture_sphere(t_obj *obj)
{
	Uint32			color;
	double			p;
	double			t;
	int				x;
	int				y;

	p = PI + acos(obj->intersec_point[2] / obj->size);
	t = PI + atan(obj->intersec_point[0] / obj->intersec_point[1]);
	x = (int)((obj->texture->w * t * 1) / 2 * PI);
	y = (int)((obj->texture->h * p * 1) / 2 * PI);
	color = getpixel(obj->texture, \
		abs(x % (int)obj->texture->w), abs(y % (int)obj->texture->h));
	return (color);
}

Uint32		texture_cylinder(t_obj *obj)
{
	Uint32			color;
	double			t;
	double			z;
	int				x;
	int				y;
	int	valeur;

	valeur = 100;
	t = PI + atan(obj->intersec_point[1] / obj->intersec_point[0]);
	z = obj->intersec_point[2];
	y = abs((int)(z * valeur) % (int)obj->texture->h);
	x = abs(((int)((obj->texture->h * t) / 2 * PI)) % obj->texture->w);
	color = getpixel(obj->texture, obj->texture->w - x, obj->texture->h - y);
	return (color);
}

Uint32		texture_plane(t_obj *obj)
{
	Uint32			color;
	int				x;
	int				y;

	x = ((int)(obj->intersec_point[0] * 16)) % obj->texture->w;
	y = ((int)(obj->intersec_point[1] * 16)) % obj->texture->h;
	if (x < 0)
		x += obj->texture->w;
	if (y < 0)
		y += obj->texture->h;
	color = getpixel(obj->texture, x, y);
	return (color);
}

void		texture(t_obj *obj, int color_tab[3])
{
	int				i;
	Uint32			color;
	unsigned char	tmp;
	unsigned char	*ptr;

	color = obj->texturing(obj);
	i = 0;
	ptr = (unsigned char *)(&color);
	while (i < 3)
	{
		tmp = ptr[3 - i];
		color_tab[i] = tmp;
		i++;
	}
}
