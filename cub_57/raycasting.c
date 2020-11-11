/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:46:28 by jikang            #+#    #+#             */
/*   Updated: 2020/11/11 21:55:26 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int					find_cardinal_dir_wall(t_ray *r, t_win *w)
{
	double ray_ang;

	r->wall_NSEW = 5;
	if (fabs(r->hit.x - r->wall.x) < 1.5)
		return (EAST);
	if (fabs(r->hit.x - r->wall.x - w->wall.length) < 1.5)
		return (WEST);
	if (fabs(r->hit.y - r->wall.y) < 1.5)
		return (SOUTH);
	if (fabs(r->hit.y - r->wall.y - w->wall.length) < 1.5)
		return (NORTH);
	return (5);
}

/*
**	함수 cast_a_ray
**	우측 작대기 함수를 약간 변형해서 draw_rays 의 각도를 받아 WIN_WIDTH 의 길이만큼의 광선을 출력하는 함수입니다.
**	plot은 (0, 0) 의 픽셀에서 각도를 변환하며 계산한 좌표이고, plot_player는 플레이어의 현재위치를 더한 좌표 값입니다.
*/

int					cast_a_ray(t_ray *r, t_win *w)
{
	int				i;
	t_plot			plot;
	t_plot			plot_player;

	i = 0;
	while (1)
	{
		plot.x = i * cos(r->ang);
		plot.y = i * sin(r->ang);
		plot_player.x = plot.x + w->player.plot.x;
		plot_player.y = plot.y + w->player.plot.y;
		if (plot_player.x >= 0 && plot_player.y >= 0)
		{
			if (is_wall(plot_player.x, plot_player.y, w) == WALL)
				break ;
			if (is_wall(plot_player.x, plot_player.y, w) == SPRITE)
				save_plot(&r->spr_hit, &plot_player);
		}
		i++;
	}
	save_plot(&r->hit, &plot_player);
	r->wall.x = (int)(r->hit.x / w->wall.length) * w->wall.length;
	r->wall.y = (int)(r->hit.y / w->wall.length) * w->wall.length;
	r->wall_NSEW = find_cardinal_dir_wall(r, w);
	return (0);
}

void				init_sprite_arr(t_sprite *sprite, t_win *w)
{
	int				j;

	j = 0;
	while (j < w->num_sprite)
	{
		sprite[j].i = 0;
		sprite[j].dist = 0;
		j++;
	}
}

void				sprites_calculator(t_sprite *sprite, t_ray *r, t_win *w)
{
	int				i;
	int				j;

	init_sprite_arr(sprite, w);
	i = 0;
	j = 0;
	while (i < w->R_width - 1)
	{
		if (r[i].spr_hit.x != 0 && r[i].spr_hit.y != 0 &&
		hypot(r[i].spr_hit.x - r[i + 1].spr_hit.x, r[i].spr_hit.y -
		r[i + 1].spr_hit.y) > w->wall.length * 0.5)
		{
			sprite[j].i = i;
			sprite[j].dist = hypot(r[i].spr_hit.x - w->player.plot.x,
					r[i].spr_hit.y - w->player.plot.y) * fabs(cos(r[i].ang -
							w->player.ang));
			j++;
		}
		i++;
	}
	draw_sprites(sprite, r, w);
}

int					cast_rays(t_win *w)
{
	t_ray			r[w->R_width];
	int				i;
	double			ray_ang;
	t_sprite		sprite[w->num_sprite];
	int				j;

	ray_ang = -1 * w->fov_ang / 2;
	i = 0;
	while (ray_ang < w->fov_ang / 2 && i < w->R_width)
	{
		r[i].spr_hit.x = 0;
		r[i].spr_hit.y = 0;
		r[i].ang = normalize_angle(w->player.ang + ray_ang);
		draw_ceiling(i, r, w);
		draw_floor(i, r, w);
		cast_a_ray(&(r[i]), w);
		draw_a_wall(i, r, w);
		ray_ang += w->fov_ang / w->R_width;
		i++;
	}
	sprites_calculator(sprite, r, w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);
	return (0);
}
