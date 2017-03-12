/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 11:22:55 by vroussea          #+#    #+#             */
/*   Updated: 2017/03/11 17:17:38 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static int	enqueue_task(cl_command_queue queue, cl_kernel kern, int xy2[2],
		cl_mem col_buff)
{
	int		*col;
	size_t	*global_wi;
	cl_int	errcode;

	errcode = clEnqueueNDRangeKernel (queue, kern, 1,
			NULL, xy2[0] * xy2[1], NULL, 0, NULL, NULL);
	if (errcode != CL_SUCCESS)
		ft_error(NULL, "Error while enqueing task");
	if (clEnqueueReadBuffer(queue, col_buff, CL_TRUE, 0,
				xy2[0] * xy2[1], col, 0, NULL, NULL) != CL_SUCCESS)
		ft_error(NULL, "Error while reading buffer");
	ft_memdel((void **)&global_wi);
	return (col);
}

static cl_mem	*create_buffers(int *col, int xy2[2], t_obj *list,
		t_opencl ocl)
{
	cl_mem	buff[3];
	cl_int	errcode[3];
	int		nb_obj;
	t_obj	*tmp;

	nb_obj = 0;
	tmp = list;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		nb_obj++;
	}
	buff[0] = clCreateBuffer(ocl.ctxt, CL_MEM_READ_ONLY,
			sizeof(int), &(xy2[0]), &errcode);
	if (errcode != CL_SUCCESS)
		ft_error(NULL, "Error while creating buffer 0");
	buff[1] = clCreateBuffer(ocl.ctxt, CL_MEM_READ_ONLY,
			sizeof(t_obj) * nb_obj, list, &errcode);
	if (errcode != CL_SUCCESS)
		ft_error(NULL, "Error while creating buffer 1");
	buff[2] = clCreateBuffer(ocl.ctxt, CL_MEM_WRITE_ONLY,
			sizeof(int) * xy2[0] * xy2[1], col, &errcode);
	if (errcode != CL_SUCCESS)
		ft_error(NULL, "Error while creating buffer 2");
	return (buff);
}

static void			set_args(int *col, int xy2[2], t_obj *list,
		t_opencl ocl)
{
	cl_mem	*buff;
	cl_int	errcode[3];

	buff = create_buffers(col, xy2, list, ocl);
	if (clSetKernelArg(ocl.kernel, 0, sizeof(cl_mem),
				(void *)&(buff[0])) != CL_SUCCESS ||
		clSetKernelArg(ocl.kernel, 1, sizeof(cl_mem),
				(void *)&(buff[1])) != CL_SUCCESS ||
		clSetKernelArg(ocl.kernel, 2, sizeof(cl_mem),
				(void *)&(buff[2])) != CL_SUCCESS)
		ft_error(NULL, "Error while setting a kernel argument");
	return (buff[2]);
}

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

int					*opencl(char *kernel_path, t_obj *list, int	xy2[2])
{
	t_opencl	ocl;
	int			*col;
	cl_mem		col_buff;

	col = (int *)malloc(sizeof(int) * xy2[0] * xy2[1]);
	ocl = init_opencl(kernel_path);
	set_args(col, xy2, list, ocl);
	col = enqueue_task(ocl.queue, ocl.kernel, xy2, col_buff);
	return (col);
}
