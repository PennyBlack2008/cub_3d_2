/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:09:17 by jikang            #+#    #+#             */
/*   Updated: 2020/11/12 19:27:14 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int					get_color_spr(double x, double y, t_sprite_var *var,
		t_win *w)
{
	int				color;
	double			px;
	double			py;

	px = floor(x / var->scale_w);
	py = floor(y / var->scale_h);
	color = w->map.curr_tex[4][(int)(w->tex[4].width * py + px)];
	return (color);
}

static void			draw_part_down(int i, int l, t_sprite_var *var, t_win *w)
{
	int				color;
	int				j;

	j = 0;
	while (j < var->pjtd_height / 2 && i + l > 0)
	{
		color = get_color_spr(var->o_pjtd_width / 2 + l, var->o_pjtd_height / 2
				+ j, var, w);
		if (color != 0 && i + l < w->r_width)
			my_mlx_pixel_put(&w->img, i + l, w->player.height + j, color);
		j++;
	}
}

static void			draw_part_up(int i, int l, t_sprite_var *var, t_win *w)
{
	int				color;
	int				k;

	k = var->pjtd_height / 2 - 1;
	while (k > 0)
	{
		color = get_color_spr(var->o_pjtd_width / 2 + l, var->o_pjtd_height / 2
			- k, var, w);
		if (color != 0)
			my_mlx_pixel_put(&w->img, i + l, w->player.height - k, color);
		k--;
	}
}

void				draw_sprite_pixels(int i, t_sprite_var *var, t_ray *r,
		t_win *w)
{
	int				l;

	l = -1 * var->pjtd_width / 2;
	while (l < var->pjtd_width / 2)
	{
		if (i + l > w->r_width)
			break ;
		if (i + l >= 0 && (hypot(r[i + l].hit.x - w->player.plot.x,
		r[i + l].hit.y - w->player.plot.y) > hypot(r[i].spr_hit.x -
		w->player.plot.x, r[i].spr_hit.y - w->player.plot.y)))
		{
			draw_part_down(i, l, var, w);
			draw_part_up(i, l, var, w);
		}
		l++;
	}
}

void				draw_a_sprite(int i, t_ray *r, t_win *w)
{
	t_sprite_var	var;
	int				color;

	var.dist_to_spr = hypot(r[i].spr_hit.x - w->player.plot.x, r[i].spr_hit.y
			- w->player.plot.y) * fabs(cos(r[i].ang - w->player.ang));
	if (var.dist_to_spr < 30)
		var.dist_to_spr = 30;
	var.pjtd_height = w->wall.height * w->player.projected_plane /
		var.dist_to_spr;
	var.o_pjtd_height = var.pjtd_height;
	var.pjtd_width = 300 * w->player.projected_plane / var.dist_to_spr;
	var.o_pjtd_width = var.pjtd_width;
	var.scale_h = var.o_pjtd_height / w->tex[4].height;
	var.scale_w = var.o_pjtd_width / w->tex[4].width;
	if (var.pjtd_height > w->r_height)
		var.pjtd_height = w->r_height;
	if (var.pjtd_width > w->r_width)
		var.pjtd_width = w->r_width;
	draw_sprite_pixels(i, &var, r, w);
}
