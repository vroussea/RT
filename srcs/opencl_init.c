/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 17:52:40 by vroussea          #+#    #+#             */
/*   Updated: 2017/03/13 15:19:50 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"
#include <fcntl.h>

#if WIN32
# include <stdint.h>
#else
# include <unistd.h>
#endif
#include <stdlib.h>

#define SOURCE_SIZE 500000

char				*load_source_code(char *kernel)
{
	char	*source;
	int		fd;

	if ((fd = open(kernel, O_RDONLY)) == -1)
		ft_error("Error with file", NULL);
	if (!(source = (char *)malloc(SOURCE_SIZE)))
		ft_error("Error while allocating to source string", NULL);
	if ((read(fd, source, SOURCE_SIZE)) == -1)
		ft_error("Error while reading .cl source code", NULL);
	ft_putstr(source);
	close(fd);
	return (source);
}

cl_context			get_context(cl_device_id *dvic)
{
	cl_platform_id	platform;
	cl_context		context;
	cl_int			err_code;

	platform = NULL;
	context = NULL;
	if ((clGetPlatformIDs(1, &platform, NULL)) != CL_SUCCESS)
		ft_error("Error while retrieving platform informations", NULL);
	if (clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, dvic, NULL)
			!= CL_SUCCESS)
		ft_error("Error while retrieving device informations", NULL);
	context = clCreateContext(NULL, 1, &(*dvic), NULL, NULL, &err_code);
	if (err_code != CL_SUCCESS)
		ft_error("Error while creating context", NULL);
	return (context);
}

cl_program			build_program(char *src, cl_context ctxt, cl_device_id dvic)
{
	cl_program		prog;
	cl_int			err_code;
	size_t			size;
	char			*log;

	prog = NULL;
	prog = clCreateProgramWithSource(ctxt, 1, (const char **)&src,
			NULL, &err_code);
	if (err_code != CL_SUCCESS)
		ft_error("Error while creating program with source", NULL);
	err_code = clBuildProgram(prog, 1, &dvic, "-I ./includes/", NULL, NULL);
	if (err_code != CL_SUCCESS)
	{
		clGetProgramBuildInfo(prog, dvic, CL_PROGRAM_BUILD_LOG, 0, NULL, &size);
		log = ft_strnew(size);
		clGetProgramBuildInfo(prog, dvic,
				CL_PROGRAM_BUILD_LOG, size + 1, log, NULL);
		ft_error(log, NULL);
		free((void **)&log);
	}
	free((void **)&src);
	return (prog);
}

cl_kernel			init_kernel(cl_program prog)
{
	cl_kernel	kernel;
	cl_int		errcode;

	kernel = NULL;
	kernel = clCreateKernel(prog, "rt", &errcode);
	if (errcode != CL_SUCCESS)
		ft_error("Error while creating Kernel", NULL);
	return (kernel);
}

cl_command_queue	init_queue(cl_context ctxt, cl_device_id dvic)
{
	cl_command_queue	queue;
	cl_int				errcode;

	queue = NULL;
	queue = clCreateCommandQueue(ctxt, dvic, 0, &errcode);
	if (errcode != CL_SUCCESS)
		ft_error("Error while creating command queue", NULL);
	return (queue);
}
