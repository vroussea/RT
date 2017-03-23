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

Uint32 		convert(Uint32 color)
{
	Uint8 a;
	Uint8 r;
	Uint8 g;
	Uint8 b;

	a = 255;
	b = (color >> 16 & 0xff);
	g = (color >> 8 & 0xff);
	r = (color >> 0 & 0xff);
	return ( (b << 24) + (g << 16) + (r << 8));
}

Uint32		texture_sphere(t_obj obj)
{
	Uint32			color;
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
	return (color);
}

Uint32		texture_cylinder(t_obj obj)
{
	Uint32			color;
	double			t;
	double			z;
	int				x;

	t = PI + atan(obj.intersec_point[1] / obj.intersec_point[0]);
	z = obj.intersec_point[2];
	x = (int)((obj.texture->h * t * 6) / 2 * PI);
	color = getpixel(obj.texture, \
		abs(x % obj.texture->w), abs((int)z % (int)obj.texture->h));
	return (color);
}

Uint32	texture_plane(t_obj obj)
{
	Uint32			color;
	int				x;
	int				y;

	x = abs((int)(obj.intersec_point[0] * 16));
	y = abs((int)(obj.intersec_point[1] * 16));
	color = convert(getpixel(obj.texture, \
		x % obj.texture->w, y % obj.texture->h));
	//printf("0x%08x\n", color);  // gives 0x000007
	return (color);
}

void	texture(t_obj obj, int color_tab[3])
{
	int				i;
	Uint32			color;
	unsigned char	tmp;
	unsigned char	*ptr;

	color = obj.texturing(obj);
	i = 0;
	ptr = (unsigned char *)(&color);
	while (i < 3)
	{
		tmp = ptr[3 - i];
		color_tab[i] = tmp;
		i++;
	}
}
