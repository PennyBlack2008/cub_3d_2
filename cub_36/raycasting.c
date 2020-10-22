#include "cub_21.h"

/*
**	함수 draw_a_ray
**	우측 작대기 함수를 약간 변형해서 draw_rays 의 각도를 받아 WIN_WIDTH 의 길이만큼의 광선을 출력하는 함수입니다.
**	plot은 (0, 0) 의 픽셀에서 각도를 변환하며 계산한 좌표이고, plot_player는 플레이어의 현재위치를 더한 좌표 값입니다.
*/

int					draw_a_ray(t_ray *r, t_win *w)
{
	int x, y;
	t_plot plot;
	t_plot plot_player;

	x = 0;
	while (x < w->R_width * 2)
	{
		y = 0;
		plot.x = x * cos(r->ang * -1) + y * sin(r->ang * -1);
		plot.y = x * sin(r->ang * -1) * -1 + y * cos(r->ang * -1);
		plot_player.x = plot.x + w->player.x; // player 좌표를 더한 광선의 값
		plot_player.y = plot.y + w->player.y; // player 좌표를 더한 광선의 값
		if (plot_player.x >= 0 && plot_player.y >= 0)
		{
			if (is_wall(plot_player.x, plot_player.y, w) == WALL)
				break ;
		}
		x++;
	}
	r->hit.x = plot_player.x;
	r->hit.y = plot_player.y;
	r->wall.x = (int)(r->hit.x / w->wall.length) * w->wall.length;
	r->wall.y = (int)(r->hit.y / w->wall.length) * w->wall.length;
	
	return (0);
}

int					draw_rays(t_win *w)
{
	t_ray		r[w->R_width];
	int			i;				i = 0;
	double		ray_ang;		ray_ang = -1 * w->fov_ang / 2;

	while (ray_ang < w->fov_ang / 2)
	{
		r[i].ang = normalize_angle(w->player.ang + ray_ang);
		draw_a_ray(&(r[i]), w);
		draw_a_wall(i, &(r[i]), w);
		draw_ceiling(i, &(r[i]), w);
		draw_floor(i, &(r[i]), w);
		ray_ang += w->fov_ang / (w->R_width - 1);
		i++;
	}
	draw_minimap(r, w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);
	return (0);
}
