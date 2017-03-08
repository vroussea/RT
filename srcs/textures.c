/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboudrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 16:30:29 by gboudrie          #+#    #+#             */
/*   Updated: 2017/03/08 12:37:06 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//unsigned int	getpixel(SDL_Surface *surface, int x, int y)
#include <rtv1.h>

int		*texture(t_obj obj)
{
	int		color;

	color = getpixel(obj.texture.surface,
					 obj.intersec_point[0] % obj.texture.surface->w,
					 obj.intersec_point[1] % obj.texture.size[1]);
}
