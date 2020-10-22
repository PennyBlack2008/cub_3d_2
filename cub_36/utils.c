#include "cub_21.h"

void					my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char				*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

double				normalize_angle(double ang)
{
	while (ang >= 2 * M_PI)
		ang -= 2 * M_PI;
	while (ang < 0)
		ang += 2 * M_PI;
	return (ang);
}

void				set_plot_int(t_plot *plot, int x, int y)
{
	plot->x = x;
	plot->y = y;
}

void				set_plot(t_plot *plot, double x, double y)
{
	plot->x = x;
	plot->y = y;
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
