#include "cub_21.h"

double				normalize_angle(double ang)
{
	while (ang >= 2 * M_PI)
		ang -= 2 * M_PI;
	while (ang < 0)
		ang += 2 * M_PI;
	return (ang);
}

/*
**	함수 draw_a_ray
**	우측 작대기 함수를 약간 변형해서 draw_a_rays 의 각도를 받아 WIN_WIDTH 의 길이만큼의 광선을 출력하는 함수입니다.
**	plot은 (0, 0) 의 픽셀에서 각도를 변환하며 계산한 좌표이고, plot_player는 플레이어의 현재위치를 더한 좌표 값입니다.
*/

int					draw_a_ray(t_ray *r, t_win *w)
{
	int x, y;
	t_plot plot;
	t_plot plot_player;
	t_plot player;

	player.x = w->player.x;
	player.y = w->player.y;
	x = 0;
	while (x < WIN_WIDTH * 2)
	{
		y = 0;
		plot.x = x * cos(r->ang);
		plot.y = x * sin(r->ang);
		plot_player.x = plot.x + w->player.x;
		plot_player.y = plot.y + w->player.y;
		if (plot_player.x >= 0 && plot_player.y >= 0)
		{
			my_mlx_pixel_put(&w->img, plot_player.x, plot_player.y, 0xFF0000);
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

int					draw_rays(t_win *w)
{
	t_ray		r[w->R_width];
	int			i;				i = 0;
	double		ray_ang;		ray_ang = -1 * M_PI / 6;

	while (ray_ang < M_PI / 6)
	{
		r[i].ang = normalize_angle(w->player.ang + ray_ang);
		draw_a_ray(&(r[i]), w);
		ray_ang += M_PI / 3 / 999;
		i++;
	}
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);
	return (0);
}

/*
** draw_background 함수는 검정화면을 출력하기 위한 함수입니다. 이 함수가 있어서 플레이어가 움직일 때, 움직이기 전의 위치의 픽셀을 까맣게 지워줍니다.
*/

int					draw_background(t_win *w)
{
	int				x,y;

	x = 0;
	while (x < w->R_width)
	{
		x++;
		y = 0;
		while (y < w->R_height)
		{
			my_mlx_pixel_put(&w->img, x, y, 0x000000);
			y++;
		}
	}
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);
	return (0);
}

void				draw_a_sprite(t_plot sprite, t_win *w)
{
	t_plot			sprite_plot;

	w->player.ang = normalize_angle(w->player.ang);
	int	k;		k = 0;
	while (k < 50)
	{
		sprite_plot.x = sprite.x - k * sin(w->player.ang);
		sprite_plot.y = sprite.y + k * cos(w->player.ang);
		my_mlx_pixel_put(&w->img, sprite_plot.x, sprite_plot.y, 0x00ff00);
		k++;
	}
	k = 0;
	while (k >= -50)
	{
		sprite_plot.x = sprite.x - k * sin(w->player.ang);
		sprite_plot.y = sprite.y + k * cos(w->player.ang);
		my_mlx_pixel_put(&w->img, sprite_plot.x, sprite_plot.y, 0x00ff00);
		k--;
	}
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);
}

int					is_sprite(t_plot plot, t_ray *r, t_win *w)
{
	t_plot			sprite_plot;

	r->sprite.x = 0;
	r->sprite.y = 0;
	// printf("x: %f, y: %f\n", plot.x, plot.y);
	// sprite group(군)의 대표 좌표 구하기 (왼쪽 위쪽 끝 좌표)
	r->spr_group.x = (int)(plot.x / w->wall.length) * w->wall.length;
	r->spr_group.y = (int)(plot.y / w->wall.length) * w->wall.length;

	// printf("r->spr_group.x : %f, r->spr_group.y : %f\n", r->spr_group.x, r->spr_group.y);
	int	k;	k = 0;
	while (k < 50)
	{
		sprite_plot.x = (int)(r->spr_group.x - k * sin(w->player.ang));
		sprite_plot.y = (int)(r->spr_group.y + k * cos(w->player.ang));
		// && !(sprite_plot.x < 0 || sprite_plot.y < 0)
		if ((fabs(sprite_plot.x - plot.x) < 0.5) && (fabs(sprite_plot.y - plot.y) < 0.5))
		{
			r->sprite.x = plot.x;
			r->sprite.y = plot.y;
			// printf("x: %f, y: %f\n", r->sprite.x, r->sprite.y);
			return (1);
		}
		k++;
	}
	k = 0;
	while (k >= -50)
	{
		sprite_plot.x = (int)(r->spr_group.x - k * sin(w->player.ang));
		sprite_plot.y = (int)(r->spr_group.y + k * cos(w->player.ang));
		if ((fabs(sprite_plot.x - plot.x) < 0.5) && (fabs(sprite_plot.y - plot.y) < 0.5))
		{
			r->sprite.x = plot.x;
			r->sprite.y = plot.y;
			// printf("x: %f, y: %f\n", r->sprite.x, r->sprite.y);
			return (1);
		}
		k--;
	}
	return (0);
}

int					draw_player(t_win *w)
{
	int width, height;
	int	x, y;
	t_plot	plot;
	t_plot	plot_player;
	
	width = w->player.width;
	height = w->player.height;

	// 돌리는 건 성공했는 데, 애초에 사각형의 끝점을 중심으로 그렸기 때문에 내가 원하는 공식을 쓸 수가 없다.
	x = width / 2 * -1;
	while (x < width/2)
	{
		y = width / 2 * -1;
		while (y < width / 2)
		{
			plot.x = x * cos(w->player.ang * -1) + y * sin(w->player.ang * -1);
			plot.y = x * sin(w->player.ang * -1) * -1 + y * cos(w->player.ang * -1);
			plot_player.x = plot.x + w->player.x;
			plot_player.y = plot.y + w->player.y;
			if (plot_player.x >= 0 && plot_player.y >= 0)
			{
				my_mlx_pixel_put(&w->img, plot_player.x, plot_player.y, 0xbbccff);
				// printf("%d %d\n", round_num_AND_int(plot_player.x), round_num_AND_int(plot_player.y));
			}
			y++;
		}
		x++;
	}
	// 정면 작대기
	x = 0;
	while (x < width / 2 + 30)
	{
		y = 0;
		plot.x = x * cos(w->player.ang * -1) + y * sin(w->player.ang * -1);
		plot.y = x * sin(w->player.ang * -1) * -1 + y * cos(w->player.ang * -1);
		plot_player.x = plot.x + w->player.x;
		plot_player.y = plot.y + w->player.y;
		if (plot_player.x >= 0 && plot_player.y >= 0)
		{
			my_mlx_pixel_put(&w->img, plot_player.x, plot_player.y, 0xFF0000);
			// printf("%d %d\n", round_num_AND_int(plot_player.x), round_num_AND_int(plot_player.y));
		}
		x++;
	}

	// 우측 작대기
	y = 0;
	while (y < height / 2 + 30)
	{
		x = 0;
		plot.x = -1 * y * sin(w->player.ang);
		plot.y = y * cos(w->player.ang);
		plot_player.x = plot.x + w->player.x;
		plot_player.y = plot.y + w->player.y;
		if (plot_player.x >= 0 && plot_player.y >= 0)
		{
			my_mlx_pixel_put(&w->img, plot_player.x, plot_player.y, 0x0000FF);
			// printf("%d %d\n", round_num_AND_int(plot_player.x), round_num_AND_int(plot_player.y));
		}
		y++;
	}

	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);

	return (0);
}

/*
** draw_grid 는 디버깅할 때 편하려고 해상도의 가로길이와 세로길이의 반을 통과하는 선을 그리는 함수입니다.
*/

int					draw_grid(t_win *w)
{
	int x, y;

	x = 0;	y = w->R_height / 2;
	while (x < w->R_width)
	{
		my_mlx_pixel_put(&w->img, x, y, 0x00ccff);
		x++;
	}

	y = 0;	x = w->R_width / 2;
	while (y < w->R_height)
	{
		my_mlx_pixel_put(&w->img, x, y, 0x00ccff);
		y++;
	}
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);

	return (0);
}