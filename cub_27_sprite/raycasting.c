#include "cub_21.h"

/*
**	함수 cast_a_ray
**	우측 작대기 함수를 약간 변형해서 cast_a_rays 의 각도를 받아 WIN_WIDTH 의 길이만큼의 광선을 출력하는 함수입니다.
**	plot은 (0, 0) 의 픽셀에서 각도를 변환하며 계산한 좌표이고, plot_player는 플레이어의 현재위치를 더한 좌표 값입니다.
*/

int					cast_a_ray(t_ray *r, t_win *w)
{
	int x, y;
	t_plot plot;
	t_plot plot_player;
	t_plot player;

	player.x = w->player.x;
	player.y = w->player.y;
	x = 0;
	while (x < w->R_width * 2)
	{
		y = 0;
		plot.x = x * cos(r->ang);
		plot.y = x * sin(r->ang);
		plot_player.x = plot.x + w->player.x;
		plot_player.y = plot.y + w->player.y;
		if (plot_player.x >= 0 && plot_player.y >= 0)
		{
			// my_mlx_pixel_put(&w->img, plot_player.x, plot_player.y, 0xFF0000);
			// 여기에 sprite 인지 확인하는 함수를 넣어야한다.
			if (is_wall(plot_player.x, plot_player.y, w) == WALL)
				break ;
			else if (is_wall(plot_player.x, plot_player.y, w) == SPRITE)
			{
				// 여기에 sprite 인지 확인하는 함수를 넣어야한다.
				is_sprite(plot_player, r, w);
				if (r->sprite.x != 0 && r->sprite.y != 0)
				{
					draw_line(player, r->sprite, 0x0000ff, w);
					// printf("x: %f, y: %f\n", r->sprite.x, r->sprite.y);
				}
			}
		}
		x++;
	}
	return (0);
}

int					cast_rays(t_win *w)
{
	t_ray		r[w->R_width];
	int			i;				i = 0;
	double		ray_ang;		ray_ang = -1 * M_PI / 6;

	while (ray_ang < M_PI / 6)
	{
		r[i].ang = normalize_angle(w->player.ang + ray_ang);
		cast_a_ray(&(r[i]), w);
		ray_ang += M_PI / 3 / 999;
		i++;
	}
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);
	return (0);
}
