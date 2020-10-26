#include "cub_21.h"

double				get_which_spr(int i, t_ray *r, t_win *w)
{
	double			x;
	
	x = 0;
	if (r[i].spr_NSEW == EAST)
	{
		x = r[i].spr.y - r[i].spr_arr.y; // spr.y 도 처리해주어야함 wall.y 처럼
	}
	else if (r[i].spr_NSEW == SOUTH)
	{
		x = r[i].spr.x - r[i].spr_arr.x;
	}
	else if (r[i].spr_NSEW == WEST)
	{
		x = r[i].spr.y - r[i].spr_arr.y;
	}
	else if (r[i].spr_NSEW == NORTH)
	{
		x = r[i].spr.x - r[i].spr_arr.x;
	}
	return (x);
}

int					get_color_sprite(int i, int j, double scale_h, t_ray *r, t_win *w)
{
	int				color;
	double			x;
	double			px, py;
	double			scale_w;

	x = 0;
	x = get_which_spr(i, r, w);
	scale_w = w->sprite.width / 64.0; // 여기가 문제이다. 미리 옆의 길이를 구하고 할 수 있으면 좋은데... 그게 안된다. 이건
	px = floor(x / scale_w); // x 에서 받는 scale 은 100 -> 64이다.
	py = floor(j / scale_h);
	color = w->map.curr_spr[(int)(64.0 * py + px)];
	
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

void		draw_a_wall(int i, t_ray *r, t_win *w)
{
	double dist_to_wall;
	double pjtd_height;

	dist_to_wall = hypot(r->hit.x - w->player.x, r->hit.y - w->player.y) * fabs(cos(r->ang - w->player.ang));
	pjtd_height = w->wall.height * w->player.projected_plane / dist_to_wall;
	if (pjtd_height > w->R_height)
		pjtd_height = w->R_height;
	int j;		j = 0;		int k;		k = (pjtd_height / 2) - 1;

	r->ceiling = w->player.height - k;
	// 중간인 500 은 위쪽 while 에서 처리
	while (j < pjtd_height / 2)
	{
		my_mlx_pixel_put(&w->img, i, w->player.height + j, 0x00ff00);
		j++;
	}
	while (k > 0)
	{
		my_mlx_pixel_put(&w->img, i, w->player.height - k, 0x00ff00);
		k--;
	}
	r->floor = w->player.height + j;
}

void		draw_a_sprite(int i, t_ray *r, t_win *w)
{
	double dist_to_sprite;
	double orjn_pjtd_height;
	double pjtd_height;
	double scale_h;
	int color;

	if (r->spr.x == 0 && r->spr.y == 0)
		return ;
	dist_to_sprite = hypot(r->spr.x - w->player.x, r->spr.y - w->player.y) * fabs(cos(r->ang - w->player.ang));
	pjtd_height = w->sprite.height * w->player.projected_plane / dist_to_sprite;
	orjn_pjtd_height = pjtd_height;
	scale_h = orjn_pjtd_height / 64;
	if (pjtd_height > w->R_height)
		pjtd_height = w->R_height;
	int j;		j = 0;		int k;		k = (pjtd_height / 2) - 1;

	// 중간인 500 은 위쪽 while 에서 처리
	while (j < pjtd_height / 2)
	{
		color = get_color_sprite(i, orjn_pjtd_height / 2 + j, scale_h, r, w);orjn_pjtd_height = pjtd_height;
		my_mlx_pixel_put(&w->img, i, w->player.height + j, color);
		// my_mlx_pixel_put(&w->img, i, w->player.height + j, 0x58D68D);
		j++;
	}
	while (k > 0)
	{
		color = get_color_sprite(i, orjn_pjtd_height / 2 - k, scale_h, r, w);
		my_mlx_pixel_put(&w->img, i, w->player.height - k, color);
		// my_mlx_pixel_put(&w->img, i, w->player.height - k, 0x58D68D);
		k--;
	}
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
