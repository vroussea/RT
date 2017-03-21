/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboudrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 16:30:29 by gboudrie          #+#    #+#             */
/*   Updated: 2017/03/21 19:10:03 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//unsigned int	getpixel(SDL_Surface *surface, int x, int y)
//SDL_Surface* SDL_LoadBMP(const char* file)
#include <rtv1.h>
#include <math.h>
#include <stdlib.h>

int		texture_sphere(t_obj obj)
{
	unsigned int	color;
	double			p;
	double			t;
	int	x;
	int	y;

	p = PI + acos(obj.intersec_point[2] / obj.size);
	t = PI + atan(obj.intersec_point[0] / obj.intersec_point[1]);
	x = (int)((obj.texture->w * p) / 2 * PI);
	y = (int)((obj.texture->h * t) / 2 * PI);
	printf("x : %lf, y : %lf\n", p, t);
	color = getpixel(obj.texture,
					 abs(x % (int)obj.texture->w),
					 abs(y % (int)obj.texture->h));
	return ((int)color);
}

int		texture_cylinder(t_obj obj)
{
	unsigned int	color;

	color = getpixel(obj.texture,
					 abs((int)atan(obj.intersec_point[1] / obj.intersec_point[0])
						 % (int)obj.texture->w),
					 abs((int)obj.intersec_point[2] % (int)obj.texture->h));
	return ((int)color);
}

int		texture_plane(t_obj obj)
{
	unsigned int	color;
	int	x;
	int	y;

	x = abs((int)(obj.intersec_point[0] * 8));
	y = abs((int)(obj.intersec_point[1] * 8));
	color = getpixel(obj.texture,
					 x % (int)obj.texture->w,
					 y % (int)obj.texture->h);
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
