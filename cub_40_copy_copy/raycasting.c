#include "cub_21.h"

int					find_cardinal_dir_wall(t_ray *r, t_win *w)
{
	double ray_ang;
	int		a, c;
	int		b, d;
	a = (fabs(r->hit.x - r->wall.x) < 1);
	c = (fabs(r->hit.y - r->wall.y) < 1);
	b = (fabs(r->hit.x - r->wall.x - w->wall.length) < 1);
	d = (fabs(r->hit.y - r->wall.y - w->wall.length) < 1);
	ray_ang = normalize_angle(r->ang);
	r->wall_NSEW = 5;

	if (a)
		return (EAST); // 민트색 <- 정상
	else if (b)
		return (WEST); // 분홍색
	else if (c)
		return (SOUTH); // 초록색 <- 정상
	else if (d)
		return (NORTH); // 노란색
	// printf("r->hit.x: %f r->wall.x: %f r->hit.y: %f r->wall.y: %f r->wall_NSEW: %d\n", r->hit.x, r->wall.x, r->hit.y, r->wall.y, r->wall_NSEW);
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
	while (i < w->R_width * 2)
	{
		plot.x = i * cos(r->ang);
		plot.y = i * sin(r->ang);
		plot_player.x = plot.x + w->player.x; // player 좌표를 더한 광선의 값
		plot_player.y = plot.y + w->player.y; // player 좌표를 더한 광선의 값
		if (plot_player.x >= 0 && plot_player.y >= 0)
		{
			if (is_wall(plot_player.x, plot_player.y, w) == WALL)
				break ;
			if (is_wall(plot_player.x, plot_player.y, w) == SPRITE)
			{
				r->spr_hit.x = plot_player.x;
				r->spr_hit.y = plot_player.y;
				printf("여기\n");
			}
		}
		i++;
	}
	r->hit.x = plot_player.x;
	r->hit.y = plot_player.y;
	r->wall.x = (int)(r->hit.x / w->wall.length) * w->wall.length;
	r->wall.y = (int)(r->hit.y / w->wall.length) * w->wall.length;
	r->wall_NSEW = find_cardinal_dir_wall(r, w);
	return (0);
}

int					cast_rays(t_win *w)
{
	t_ray			r[w->R_width];
	int				i;
	double			ray_ang;

	ray_ang = -1 * w->fov_ang / 2;
	i = 0;
	while (ray_ang < w->fov_ang / 2)
	{
		r[i].ang = normalize_angle(w->player.ang + ray_ang);
		cast_a_ray(&(r[i]), w);
		draw_a_wall(i, r, w);
		draw_ceiling(i, &(r[i]), w);
		draw_floor(i, &(r[i]), w);
		ray_ang += w->fov_ang / (w->R_width - 1);
		i++;
	}
	i = 0;
	while (i < w->R_width)
	{
		r[i].spr_hit.x = 0;
		r[i].spr_hit.y = 0;
		if (r[i].spr_hit.x != 0 || r[i].spr_hit.y != 0)
			draw_a_sprite(i, r, w);
		i++;
	}
	draw_minimap(r, w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);
	return (0);
}
