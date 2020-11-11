/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:28:29 by jikang            #+#    #+#             */
/*   Updated: 2020/11/11 21:28:45 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		draw_floor(int i, t_ray *r, t_win *w)
{
	int		j;
	int		color;

	color = color_rgb(w->map.info.FL_RGB.trgb.r, w->map.info.FL_RGB.trgb.g,
			w->map.info.FL_RGB.trgb.b);
	j = w->R_height / 2;
	while (j < w->R_height)
	{
		my_mlx_pixel_put(&w->img, i, j, color);
		j++;
	}
}
