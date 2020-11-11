/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceiling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 16:04:40 by jikang            #+#    #+#             */
/*   Updated: 2020/11/11 22:22:53 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		draw_ceiling(int i, t_ray *r, t_win *w)
{
	int		j;
	int		color;

	color = color_rgb(w->map.info.cl_rgb.trgb.r, w->map.info.cl_rgb.trgb.g,
			w->map.info.cl_rgb.trgb.b);
	j = w->r_height / 2;
	while (j >= 0)
	{
		my_mlx_pixel_put(&w->img, i, j, color);
		j--;
	}
}
