#include "cub3d.h"

double				get_render_spot(int i, t_ray *r, t_win *w)
{
	double			x;

	x = 0;
	if (r[i].wall_NSEW == EAST)
		x = r[i].hit.y - r[i].wall.y;
	else if (r[i].wall_NSEW == SOUTH)
		x = r[i].hit.x - r[i].wall.x;
	else if (r[i].wall_NSEW == WEST)
		x = r[i].hit.y - r[i].wall.y;
	else if (r[i].wall_NSEW == NORTH)
		x = r[i].hit.x - r[i].wall.x;
	return (x);
}

int					get_color_tex(int i, int j, double scale_h, t_ray *r, t_win *w, int k)
{
	int				color;
	double			x;
	double			px, py;
	double			scale_w;

	x = get_render_spot(i, r, w);
	scale_w = w->wall.length / (double)w->tex[k].width;
	px = floor(x / scale_w);
	py = floor(j / scale_h);
	color = w->map.curr_tex[k][(int)(w->tex[k].height * py + px)];

	return (color);
}

static void			draw_part_down(int i, double o_pjtd_height, double pjtd_height, double scale_h, t_ray *r, t_win *w)
{
	int			j;
	int			color;

	j = 0;
	while (j < pjtd_height / 2)
	{
		if (r[i].wall_NSEW != 5)
			color = get_color_tex(i, o_pjtd_height / 2 + j, scale_h, r, w, r[i].wall_NSEW);
		else
			color = 0;
		my_mlx_pixel_put(&w->img, i, w->player.height + j, color);
		j++;
	}
}

static void			draw_part_up(int i, double o_pjtd_height, double pjtd_height, double scale_h, t_ray *r, t_win *w)
{
	int			k;
	int			color;
	
	k = pjtd_height / 2;
	while (k > 0) // 위 쪽
	{
		if (r[i].wall_NSEW != 5)
			color = get_color_tex(i, o_pjtd_height / 2 - k, scale_h, r, w, r[i].wall_NSEW);
		else
			color = 0;
		my_mlx_pixel_put(&w->img, i, w->player.height - k, color);
		k--;
	}
}

/*
** draw_wall
** https://permadi.com/1996/05/ray-casting-tutorial-9/
**
** projected wall height / distance of player to projected plane = actual wall height / distance of player to the wall
**
** projected wall height = actual wall height * distance of player to projected plane / distance of player to the wall
** 1. actual wall height 는 cub_21.c 의 w->wall.height = 800; 에서 정의됨
** 2. distance of player to projected plane 은 cub_21.c 에서 화면의 해상도 크기 / 2 * atan(fov) 로 정의됨. w->player.projected_plane = w->R_width / 2 * atan(M_PI_2 / 3);
** 3. distance of player to the wall 은 ray 에서 벽에 부딛힌 좌표를 찾고 그 좌표와 플레이어의 좌표를 빗변계산하여 정의됨
** 4. 위의 세가지 요소와 공식을 통해 projected wall height 를 구하고 그 크기만큼 순서대로 직선을 그림
**
*/

void			draw_a_wall(int i, t_ray *r, t_win *w)
{
	double		dist_to_wall;
	double		pjtd_height;
	double		o_pjtd_height;
	double		scale_h;
	int			color;

	dist_to_wall = hypot(r[i].hit.x - w->player.x, r[i].hit.y - w->player.y) * fabs(cos(r[i].ang - w->player.ang));
	pjtd_height = w->wall.height * w->player.projected_plane / dist_to_wall;
	o_pjtd_height = pjtd_height;
	scale_h = o_pjtd_height / w->tex[r[i].wall_NSEW].height;
	if (pjtd_height > w->R_height)
		pjtd_height = w->R_height;
	r[i].ceiling = (w->R_height - o_pjtd_height) / 2.0;
	draw_part_down(i, o_pjtd_height, pjtd_height, scale_h, r, w);
	draw_part_up(i ,o_pjtd_height, pjtd_height, scale_h, r, w);
	r[i].floor = o_pjtd_height + r[i].ceiling;
}
