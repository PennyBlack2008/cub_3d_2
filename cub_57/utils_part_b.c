/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_part_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:27:29 by jikang            #+#    #+#             */
/*   Updated: 2020/11/12 13:48:33 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				save_plot(t_plot *dst_plot, t_plot *src_plot)
{
	dst_plot->x = src_plot->x;
	dst_plot->y = src_plot->y;
}

int					color_rgb(int r, int g, int b)
{
	int				color;

	color = 0;
	color += r << 16;
	color += g << 8;
	color += b;
	return (color);
}

int					safer_free_pp(void **pp)
{
	if (pp != NULL && *pp != NULL)
	{
		free(*pp);
		*pp = NULL;
	}
	return (1);
}

int					safer_free_p(void *p)
{
	if (p != NULL)
	{
		free(p);
		p = NULL;
	}
	return (1);
}

void				error_handler(char *s, int num)
{
	ft_putendl_fd("ERROR", 2);
	errno = num;
	if (errno)
		ft_putendl_fd(strerror(errno), 2);
	else
		ft_putendl_fd(s, 2);
	exit(1);
}
