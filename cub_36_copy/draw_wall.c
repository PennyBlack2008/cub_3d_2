#include "cub_21.h"

double				get_which_wall(int i, t_ray *r, t_win *w)
{
	double			x;
	double			ray_ang;

	ray_ang = normalize_angle(w->player.ang + r[i].ang);
	if (ray_ang >= M_PI/4 * 7 || ray_ang < M_PI/4)
	{
		r[i].wall_NSEW = EAST;
		x = r[i].hit.y - r[i].wall.y;
	}
	if (ray_ang >= M_PI/4 && ray_ang < M_PI/4 * 3)
	{
		r[i].wall_NSEW = SOUTH;
		x = r[i].hit.x - r[i].wall.x;
	}
	if (ray_ang >= M_PI/4 * 3 && ray_ang < M_PI/4 * 5)
	{
		r[i].wall_NSEW = WEST;
		x = r[i].hit.y - r[i].wall.y;
	}
	if (ray_ang >= M_PI/4 * 5 && ray_ang < M_PI/4 * 7)
	{
		r[i].wall_NSEW = NORTH;
		x = r[i].hit.x - r[i].wall.x;
	}
	return (x);
}

int					get_color_tex(int i, int j, double scale_h, t_ray *r, t_win *w)
{
	int				color;
	double			x;
	double			px, py;
	double			scale_w;

	x = get_which_wall(i, r, w); // 100의 크기로 환산, 여기서 x 에 넣어줄 값을 정한다.
	scale_w = w->wall.length / 64; // 여기가 문제이다. 미리 옆의 길이를 구하고 할 수 있으면 좋은데... 그게 안된다. 이건
	px = floor(x / scale_w); // x 에서 받는 scale 은 100 -> 64이다.
	py = floor(j / scale_h);
	color = w->map.curr_tex[(int)(64 * py + px)];
	if (r[i].wall_NSEW == NORTH)
		return (0xF1F740);
	if (r[i].wall_NSEW == SOUTH)
		return (0x40F759);
	if (r[i].wall_NSEW == EAST)
		return (0x40F7D5);
	if (r[i].wall_NSEW == WEST)
		return (0xDB40F7);
	return (color);
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
	double		scale_h;
	int			color;

	dist_to_wall = hypot(r[i].hit.x - w->player.x, r[i].hit.y - w->player.y) * fabs(cos(r[i].ang - w->player.ang));
	pjtd_height = w->wall.height * w->player.projected_plane / dist_to_wall;
	scale_h = pjtd_height / 64; // <--- segfault 날 수도.. 스케일은 해상도를 넘어가는 벽 높이를 해상도에 맞게 조정하기 전에 랜더링을 해야하기 때문에 이 상태에서 스케일 값을 저장.
	if (pjtd_height > w->R_height)
		pjtd_height = w->R_height;

	int j;		j = 0;		int k;		k = (pjtd_height / 2) - 1;

	r[i].ceiling = w->player.height - k;
	while (j < pjtd_height) // 벽을 아래로 내리기
	{
		color = get_color_tex(i, j, scale_h, r, w);
		my_mlx_pixel_put(&w->img, i, r[i].ceiling + j, color);
		j++;
	}
	r[i].floor = pjtd_height + r[i].ceiling;
}

void		draw_ceiling(int i, t_ray *r, t_win *w)
{
	int		j;

	j = r->ceiling;
	while (j >= 0)
	{
		my_mlx_pixel_put(&w->img, i, j, 0xff0000);
		j--;
	}
}

void		draw_floor(int i, t_ray *r, t_win *w)
{
	int		j;

	j = r->floor;
	while (j <= w->R_height)
	{
		my_mlx_pixel_put(&w->img, i, j, 0x0000ff);
		j++;
	}
}
