/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 18:59:08 by eduwer            #+#    #+#             */
/*   Updated: 2017/02/16 16:31:27 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

double	radians(double degree)
{
	double rad;

	rad = degree * (M_PI / 180.0);
	return (rad);
}

void	rotation_x(double vec[3], double degree)
{
	double b;
	double c;
	double rad;

	rad = radians(degree);
	b = vec[1];
	c = vec[2];
	vec[1] = b * cos(rad) + c * sin(rad);
	vec[2] = b * -sin(rad) + c * cos(rad);
}

void	rotation_y(double vec[3], double degree)
{
	double a;
	double c;
	double rad;

	rad = radians(degree);
	a = vec[0];
	c = vec[2];
	vec[0] = a * cos(rad) - c * sin(rad);
	vec[2] = a * sin(rad) + c * cos(rad);
}

void	rotation_z(double vec[3], double degree)
{
	double a;
	double b;
	double rad;

	rad = radians(degree);
	a = vec[0];
	b = vec[1];
	vec[0] = a * cos(rad) + b * sin(rad);
	vec[1] = a * (-sin(rad)) + b * cos(rad);
}

void	make_rotation(double vec[3], double rotation[3])
{
	if (rotation != NULL)
	{
		if (rotation[2] != 0)
			rotation_z(vec, rotation[2]);
		if (rotation[0] != 0)
			rotation_x(vec, rotation[0]);
		if (rotation[1] != 0)
			rotation_y(vec, rotation[1]);
	}
}
