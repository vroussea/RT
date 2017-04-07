/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection_refraction.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 17:33:54 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/29 17:34:16 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	reflection(double base_vec[3], double normal[3], \
		double reflected_ray[3])
{
	int		i;
	double	d_product;
	double	new_base_vec[3];

	normalize_vec(base_vec);
	normalize_vec(normal);
	new_base_vec[0] = -base_vec[0];
	new_base_vec[1] = -base_vec[1];
	new_base_vec[2] = -base_vec[2];
	d_product = dot_product(normal, new_base_vec);
	i = 0;
	while (i < 3)
	{
		reflected_ray[i] = base_vec[i] + ((2 * d_product) * normal[i]);
		i++;
	}
}

void	refraction(double base_vec[3], double normal[3], \
		double refracted_ray[3], t_obj *obj)
{
	double	angle;
	double	angle2;
	double	n;
	double	c1;
	double	c2;
	double	id1;
	double	id2;

	c1 = dot_product(base_vec, normal);
	if (c1 < 0)
	{
		c1 = c1 * (-1.0);
		id1 = obj->original_refraction;
		id2 = obj->new_refraction;
	}
	else
	{
		normal[0] = normal[0] * (-1.0);
		normal[1] = normal[1] * (-1.0);
		normal[2] = normal[2] * (-1.0);
		id2 = obj->original_refraction;
		id1 = obj->new_refraction;
	}
	angle = cos(c1 / (sqrt(dot_product(base_vec, base_vec) * dot_product(normal, normal))));
	angle2 = asin(id1 / id2 * sin(angle));
	//printf("%f %f\n", angle, angle2);
	n = id1 / id2;
	c2 = 1 - ((n * n) * (1 - (c1 * c1)));
//	printf("%f | %f | %f | %f\n", c1, c2, angle, n);
//	refracted_ray[0] = n * base_vec[0] + (n * c1 - c2 ) * normal[0];
 //  	refracted_ray[1] = n * base_vec[1] + (n * c1 - c2 ) * normal[1];
   //	refracted_ray[2] = n * base_vec[2] + (n * c1 - c2 ) * normal[2];
		refracted_ray[0] = n * (base_vec[0] + c1 * normal[0]) - normal[0] * cos(angle2);
		refracted_ray[1] = n * (base_vec[1] + c1 * normal[1]) - normal[1] * cos(angle2);
		refracted_ray[2] = n * (base_vec[2] + c1 * normal[2]) - normal[2] * cos(angle2);
	/*if (c2 < 0)
	{
		refracted_ray[0] = 0;//n * base_vec[0] + n * c1 * normal[0];
		refracted_ray[1] = 0;//n * base_vec[1] + n * c1 * normal[1];
		refracted_ray[2] = 0;//n * base_vec[2] + n * c1 * normal[2];
	}
	else
	{
		c2 = sqrt(c2);
		refracted_ray[0] = n * base_vec[0] + (n * c1 - c2) * normal[0];
		refracted_ray[1] = n * base_vec[1] + (n * c1 - c2) * normal[1];
		refracted_ray[2] = n * base_vec[2] + (n * c1 - c2) * normal[2];
	}*/
/*	double  original_angle;
	double  new_angle;
	double	orth[3];

	original_angle = cos(dot_product(base_vec, normal) /
       (sqrt(dot_product(base_vec, base_vec)) * sqrt(dot_product(normal, normal))));
	new_angle = asin(obj->original_refraction / obj->new_refraction *
                    sin(original_angle));
//	if (sin(original_angle) > obj->original_refraction / obj->new_refraction)
//		reflection(base_vec, normal, refracted_ray);
//	else
//	{
		//printf("nrmal :\nx : %f\ny : %f\nz : %f\n", normal[0], normal[1], normal[2]);
		//printf("vector dot product : %f\nsqrt : %f\n", dot_product(base_vec, base_vec), sqrt(dot_product(base_vec, base_vec)));
		//printf("original angle : %f\nnew angle : %f\n", original_angle * 57, new_angle * 57);
   		vect_prod(base_vec, normal, orth);
   	//	refracted_ray[0] = -normal[0];
  // 		refracted_ray[1] = -normal[1];
//   		refracted_ray[2] = -normal[2];
   		refracted_ray[0] = base_vec[0];
   		refracted_ray[1] = base_vec[1];
   		refracted_ray[2] = base_vec[2];
   		rotation(refracted_ray, orth, -original_angle);
   		rotation(refracted_ray, orth, new_angle);
   		//printf("ray :\nx : %f\ny : %f\nz : %f\n", base_vec[0], base_vec[1], base_vec[2]);
   		//printf("refr :\nx : %f\ny : %f\nz : %f\n", refracted_ray[0], refracted_ray[1], refracted_ray[2]);
  // 	}*/
}