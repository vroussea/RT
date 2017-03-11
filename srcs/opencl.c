/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 11:22:55 by vroussea          #+#    #+#             */
/*   Updated: 2017/03/08 18:54:11 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

/*static int	enqueue_tasks(cl_command_queue queue, cl_kernel kern)
{
	int		*col;
	size_t	*global_wi;
	cl_int	errcode;

	global_wi = (size_t *)ft_memalloc(sizeof(size_t) * 2);
	global_wi[0] = sizeof(int) * SIZE_X * SIZE_Y;
	global_wi[1] = sizeof(scene);
	errcode = clEnqueueNDRangeKernel (queue, kern, 2,
			NULL, global_wi, NULL, 0, NULL, NULL);
	if (errcode != CL_SUCCESS)
		ft_error(NULL, "Error while enqueing task");
	if (clEnqueueReadBuffer(queue, buff, CL_TRUE, 0,
				sizeof(int) * SIZE_X * SIZE_Y, &col,
				0, NULL, NULL) != CL_SUCCESS)
		ft_error(NULL, "Error while reading buffer");
	ft_memdel((void **)&global_wi);
	return (col);
}*/

static t_opencl		init_opencl(char *kernel_path)
{
	char			*src;
	int				col;
	t_opencl		ocl;

	if (!(src = load_source_code(kernel_path)) ||
			!(ocl.ctxt = get_context(&(ocl.dvic))) ||
			!(ocl.prog = build_program(src, ocl.ctxt, ocl.dvic)) ||
			!(ocl.queue = init_queue(ocl.ctxt, ocl.dvic)) ||
			!(ocl.kernel = init_kernel(ocl.prog)))
		ft_error(NULL, "Program abort");
	return (ocl);
}

int					*opencl(char *kernel_path)
{
	t_opencl	ocl;

	ocl = init_opencl(kernel_path);
}
