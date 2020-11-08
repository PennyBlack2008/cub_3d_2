#include "cub3d.h"

/*
** 함수 my_mlx_pixel_put: 이 함수를 통해서 기존의 일차원 배열에 위치를 계산해서 color를 넣는 불편함을 덜어
**						 준다.
*/

void					my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char				*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
	// printf("%0#x", color);
}

unsigned int			my_mlx_pixel_get(t_img *img, int x, int y)
{
	char				*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

/*
** 함수 normalize_angle: 이 함수를 통해 angle 이 음수이거나 360도를 넘어갈 때 생기는 문제점을 해결
**						해줍니다.
*/
double					normalize_angle(double ang)
{
	while (ang >= 2 * M_PI)
		ang -= 2 * M_PI;
	while (ang < 0)
		ang += 2 * M_PI;
	return (ang);
}

/*
** 함수 set_plot: 이 함수는 double x, double y를 t_plot(double x, double y)의 형식에 맞춰준다.
*/

void					set_plot(t_plot *plot, double x, double y)
{
	plot->x = x;
	plot->y = y;
}

/*
** 함수 draw_background: 이 함수가 있어서 플레이어가 움직일 때, 움직이기 전의 랜더링을 까맣게 지워줍니다.
*/

int						draw_background(t_win *w)
{
	int					x,y;

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

void				save_plot(t_plot *dst_plot, t_plot *src_plot)
{
	dst_plot->x = src_plot->x;
	dst_plot->y = src_plot->y;
}

int					color_rgb(int r, int g, int b)
{
	int				color;

	color = 0;
	color += r << 16;
	color += g << 8;
	color += b;
	return (color);
}