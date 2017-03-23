/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 16:30:29 by gboudrie          #+#    #+#             */
/*   Updated: 2017/03/22 16:14:40 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <math.h>
#include <stdlib.h>

int		texture_sphere(t_obj obj)
{
	unsigned int	color;
	double			p;
	double			t;
	int				x;
	int				y;

	p = PI + acos(obj.intersec_point[2] / obj.size);
	t = PI + atan(obj.intersec_point[0] / obj.intersec_point[1]);
	x = (int)((obj.texture->w * p * 6) / 2 * PI);
	y = (int)((obj.texture->h * t * 6) / 2 * PI);
	color = getpixel(obj.texture, \
		abs(x % (int)obj.texture->w), abs(y % (int)obj.texture->h));
	return ((int)color);
}

int		texture_cylinder(t_obj obj)
{
	unsigned int	color;
	double			t;
	double			z;
	int				x;

	t = PI + atan(obj.intersec_point[1] / obj.intersec_point[0]);
	z = obj.intersec_point[2];
	x = (int)((obj.texture->h * t * 6) / 2 * PI);
	color = getpixel(obj.texture, \
		abs(x % (int)obj.texture->w), abs((int)z % (int)obj.texture->h));
	return ((int)color);
}

int		texture_plane(t_obj obj)
{
	unsigned int	color;
	int				x;
	int				y;

	x = abs((int)(obj.intersec_point[0] * 16));
	y = abs((int)(obj.intersec_point[1] * 16));
	color = getpixel(obj.texture, \
		x % (int)obj.texture->w, y % (int)obj.texture->h);
	return ((int)color);
}

void	texture(t_obj obj, int color_tab[3])
{
	int				i;
	int				color;
	unsigned char	tmp;
	unsigned char	*ptr;

	color = obj.texturing(obj);
	i = 0;
	ptr = (unsigned char *)(&color);
	while (i < 3)
	{
		tmp = ptr[3 - i];
		color_tab[i] = (int)tmp;
		i++;
	}
}
