/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboudrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 16:30:29 by gboudrie          #+#    #+#             */
/*   Updated: 2017/03/08 17:30:26 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//unsigned int	getpixel(SDL_Surface *surface, int x, int y)
#include <rtv1.h>

static int		texture_sphere(t_obj obj)
{
	int		color;

	color = getpixel(obj.texture,
					 arccos(obj.intersec_point[2] / obj.size) % obj.texture->w,
					 arctan(obj.intersec_point[0] / obj.intersec_point[1])
					 % obj.texture->w);
	return (color);
}

static int		texture_cylinder(t_obj obj)
{
	int		color;

	color = getpixel(obj->texture,
					 arctan(obj.intersec_point[1] / obj.intersec_point[0])
					 % obj.texture->w,
					 obj.intersec_point[2] % obj.texture->h);
	return (color);
}

static int		texture_plane(t_obj obj)
{
	int		color;

	color = getpixel(obj.texture,
					 obj.intersec_point[0] % obj.texture->w,
					 obj.intersec_point[1] % obj.texture->h);
	return (color);
}

int				*texture(t_obj obj)
{
	int		i;
	int		color;
	int		color_tab[3];
	char	*ptr;

	color = obj->texturing(obj);
	i = 1;
	ptr = (char *)(&color);
	while (i < 3)
	{
		color_tab[i - 1] = ptr[i];
		i++;
	}
	return (color_tab);
}
