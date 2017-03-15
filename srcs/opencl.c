/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 11:22:55 by vroussea          #+#    #+#             */
/*   Updated: 2017/03/15 17:30:01 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static int	*enqueue_task(cl_command_queue queue, cl_kernel kern, int xy2[2],
		cl_mem col_buff)
{
	int		*col;
	size_t	global_wi[1];
	cl_int	errcode;

	*global_wi  = (size_t)(xy2[0] * xy2[1]);
	col = (int *)malloc(sizeof(int) * *global_wi);
	errcode = clEnqueueNDRangeKernel (queue, kern, 1,
			NULL, global_wi, NULL, 0, NULL, NULL);
	if (errcode != CL_SUCCESS)
		ft_error("Error while enqueing task", NULL);
	if (clEnqueueReadBuffer(queue, col_buff, CL_TRUE, 0,
				global_wi[0], col, 0, NULL, NULL) != CL_SUCCESS)
		ft_error("Error while reading buffer", NULL);
	return (col);
}

static cl_mem	*create_buffers(int *col, int xy2[2], t_obj *list,
		t_opencl ocl)
{
	cl_mem	*buff;
	cl_int	errcode;

	buff = (cl_mem *)malloc(sizeof(cl_mem) * 3);
	buff[0] = clCreateBuffer(ocl.ctxt, CL_MEM_READ_ONLY,
			sizeof(int), &(xy2[0]), &errcode);
	if (errcode != CL_SUCCESS)
		ft_error("Error while creating buffer 0", NULL);
	buff[1] = clCreateBuffer(ocl.ctxt, CL_MEM_READ_ONLY,
			sizeof(t_obj), list, &errcode);
	if (errcode != CL_SUCCESS)
		ft_error("Error while creating buffer 1", NULL);
	buff[2] = clCreateBuffer(ocl.ctxt, CL_MEM_WRITE_ONLY,
			sizeof(int) * (size_t)(xy2[0] * xy2[1]), col, &errcode);
	if (errcode != CL_SUCCESS)
		ft_error("Error while creating buffer 2", NULL);
	return (buff);
}

static cl_mem		set_args(int *col, int xy2[2], t_obj *list,
		t_opencl ocl)
{
	cl_mem	*buff;
	cl_mem	col_buff;

	buff = create_buffers(col, xy2, list, ocl);
	if (clSetKernelArg(ocl.kernel, 0, sizeof(int),
				(void *)&(xy2[0])) != CL_SUCCESS ||
		clSetKernelArg(ocl.kernel, 1, sizeof(cl_mem),
				(void *)&(buff[1])) != CL_SUCCESS ||
		clSetKernelArg(ocl.kernel, 2, sizeof(cl_mem),
				(void *)&(buff[2])) != CL_SUCCESS)
		ft_error("Error while setting a kernel argument", NULL);
	col_buff = buff[2];
	free((void **)&buff);
	return (col_buff);
}

static t_opencl		init_opencl(char *kernel_path)
{
	char			*src;
	t_opencl		ocl;

	ocl.kernel = NULL;
	if (!(src = load_source_code(kernel_path)) ||
			!(ocl.ctxt = get_context(&(ocl.dvic))) ||
			!(ocl.prog = build_program(src, ocl.ctxt, ocl.dvic)) ||
			!(ocl.queue = init_queue(ocl.ctxt, ocl.dvic)) ||
			!(ocl.kernel = init_kernel(ocl.prog)))
		ft_error("Program abort", NULL);
	return (ocl);
}

int					*opencl(char *kernel_path, t_obj *list, int	xy2[2])
{
	t_opencl	ocl;
	int			*col;
	cl_mem		col_buff;

	col = (int *)malloc(sizeof(int) * (size_t)(xy2[0] * xy2[1]));
	ocl = init_opencl(kernel_path);
	col_buff = set_args(col, xy2, list, ocl);
	free((void **)&col);
	col = enqueue_task(ocl.queue, ocl.kernel, xy2, col_buff);
	return (col);
}
