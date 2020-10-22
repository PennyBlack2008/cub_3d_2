#include "cub_21.h"

int					get_which_wall(t_ray *r, t_win *w)
{
	int				x;
	double			ray_ang;

	ray_ang = normalize_angle(w->player.ang + r->ang);
	if (ray_ang > M_PI_4 * 7 || ray_ang < M_PI_4)
	{
		r->wall_NSEW = EAST;
		x = r->hit.y - r->wall.y;
		// printf("east x location: %f\n", x);
		// printf("ray_ang: %f\n", ray_ang * 180 / M_PI);
		// printf("EAST: %f\n", x);
		if (x < 0)
		{
			printf("EAST: %f r->hit.y : %f r->wall.y: %f\n", x, r->hit.y, r->wall.y); // -로 튕기는 경우가 있다.
			printf("%d\n", (int)(x / w->wall.length) * w->wall.length);
		}
	}
	else if (ray_ang > M_PI_4 && ray_ang < M_PI_4 * 3)
	{
		r->wall_NSEW = SOUTH;
		
		x = r->hit.x - r->wall.x;
		// printf("south x location: %f\n", x);
		// if (x < 0)
		// {
		// 	printf("South: %f r->hit.x : %f r->wall.x: %f\n", x, r->hit.x, r->wall.x); // -로 튕기는 경우가 있다.
		// 	printf("%d\n", (int)(x / w->wall.length) * w->wall.length);
		// }
	}
	else if (ray_ang > M_PI_4 * 3 && ray_ang < M_PI_4 * 5)
	{
		r->wall_NSEW = WEST;
		x = r->hit.y - r->wall.y;
		// printf("West: %f\n", x);
		if (x < 0)
		{
			printf("WEST: %f r->hit.y : %f r->wall.y: %f\n", x, r->hit.y, r->wall.y); // -로 튕기는 경우가 있다.
			printf("%d\n", (int)(x / w->wall.length) * w->wall.length);
		}
	}
	else if (ray_ang > M_PI_4 * 5 && ray_ang < M_PI_4 * 7)
	{
		r->wall_NSEW = NORTH;
		x = r->hit.x - r->wall.x;
		// printf("North: %f\n", x);
		if (x < 0)
		{
			printf("North: %f r->hit.x : %f r->wall.x: %f\n", x, r->hit.x, r->wall.x); // -로 튕기는 경우가 있다.
			printf("%d\n", (int)(x / w->wall.length) * w->wall.length);
		}
	}
	return (x);
}

int					get_color_tex(double y, double scale, t_ray *r, t_win *w)
{
	int				color;
	double				x;
	double			px, py;

	x = get_which_wall(r, w); // 여기서 x 에 넣어줄 값을 정한다.
	if (x == 1000)
	{
		return (0xff0000);
	}
	px = floor(x / (w->wall.length / 64)); // x 에서 받는 scale 은 100 -> 64이다.
	py = floor(y / scale);
	color = w->map.curr_tex[(int)(64 * py + px)];
	if (x == 0)
	{
		return (0x00ff00);
	}
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
	double		scale;
	int			color;

	dist_to_wall = hypot(r->hit.x - w->player.x, r->hit.y - w->player.y) * fabs(cos(r->ang - w->player.ang));
	pjtd_height = w->wall.height * w->player.projected_plane / dist_to_wall;
	scale = pjtd_height / 64; // <--- segfault 날 수도.. 스케일은 해상도를 넘어가는 벽 높이를 해상도에 맞게 조정하기 전에 랜더링을 해야하기 때문에 이 상태에서 스케일 값을 저장.
	if (pjtd_height > w->R_height)
		pjtd_height = w->R_height;

	int j;		j = 0;		int k;		k = (pjtd_height / 2) - 1;

	r->ceiling = w->player.height - k;
	while (j < pjtd_height) // 벽을 아래로 내리기
	{
		color = get_color_tex(j, scale, r, w);
		my_mlx_pixel_put(&w->img, i, r->ceiling + j - 1, color);
		j++;
	}
	r->floor = pjtd_height + r->ceiling;
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
