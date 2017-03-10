/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboudrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 16:30:29 by gboudrie          #+#    #+#             */
/*   Updated: 2017/03/10 16:00:04 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//unsigned int	getpixel(SDL_Surface *surface, int x, int y)
//SDL_Surface* SDL_LoadBMP(const char* file)
#include <rtv1.h>
#include <math.h>

int		texture_sphere(t_obj obj)
{
	unsigned int	color;

	color = getpixel(obj.texture,
					 (int)acos(obj.intersec_point[2] / obj.size)
					 % (int)obj.texture->w,
					 (int)atan(obj.intersec_point[0] / obj.intersec_point[1])
					 % (int)obj.texture->w);
	return ((int)color);
}

int		texture_cylinder(t_obj obj)
{
	unsigned int	color;

	color = getpixel(obj.texture,
					 (int)atan(obj.intersec_point[1] / obj.intersec_point[0])
					 % (int)obj.texture->w,
					 (int)obj.intersec_point[2] % (int)obj.texture->h);
	return ((int)color);
}

int		texture_plane(t_obj obj)
{
	unsigned int	color;

	color = getpixel(obj.texture,
					 (int)obj.intersec_point[0] % (int)obj.texture->w,
					 (int)obj.intersec_point[1] % (int)obj.texture->h);
	return ((int)color);
}

void	texture(t_obj obj, int *color_tab[3])
{
	int		i;
	int		color;
	char	*ptr;

	color = obj.texturing(obj);
	i = 1;
	ptr = (char *)(&color);
	while (i < 3)
	{
		(*color_tab)[i - 1] = ptr[i];
		i++;
	}
}
