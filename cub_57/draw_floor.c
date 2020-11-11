/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:28:29 by jikang            #+#    #+#             */
/*   Updated: 2020/11/11 22:22:55 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		draw_floor(int i, t_ray *r, t_win *w)
{
	int		j;
	int		color;

	color = color_rgb(w->map.info.fl_rgb.trgb.r, w->map.info.fl_rgb.trgb.g,
			w->map.info.fl_rgb.trgb.b);
	j = w->r_height / 2;
	while (j < w->r_height)
	{
		my_mlx_pixel_put(&w->img, i, j, color);
		j++;
	}
}
